#include "generator.h"
#include "util.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/Basic/Specifiers.h"
#include "llvm/Support/Casting.h"

#include <format>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>


class TDefaultGenerator : public IGenerator {
public:

    TDefaultGenerator(const std::string outputPath, const std::string& moduleName, const HeaderManager& headerManager)
    : IGenerator(outputPath, moduleName, headerManager)
    {
        outputFile_.open(outputPath, std::ios::out | std::ios::trunc);

        outputFile_ << "#include <pybind11/pybind11.h>\n";
        outputFile_ << "#include <pybind11/stl.h>\n\n";

        outputFile_ << headerManager.GetIncludes() << "\n\n";

        outputFile_ << "namespace py = pybind11;\n\n";

        outputFile_ << std::format(
            "PYBIND11_MODULE({}, m) ",
            moduleName
        ) << "{\n";
    }

    void FoundRecord(const CXXRecordDecl* record) override {
        auto recordName = GetFullRecordName(record);
        std::string classInit = "\n\tpy::class_<" + recordName;
        for (const auto& base : record->bases()) {
            const auto *baseClass = base.getType()->getAsCXXRecordDecl();
            if (baseClass && base.getAccessSpecifier() == clang::AS_public) {
                auto baseClassName = GetFullRecordName(baseClass);
                classes_[recordName].Bases.push_back(baseClassName);
                classInit += ", " + baseClassName;
            }
        }
        classInit += std::format(">(m,  \"{}\")", record->getDeclName().getAsString());

        classes_[recordName].Declaration = classInit;
    }

    void FoundConstructor(const CXXConstructorDecl* ctor) override {
        auto recordName = GetFullRecordName(ctor->getParent());
        auto& classDecl = classes_[recordName];
        classDecl.Declaration += std::format("\n\t\t.def(py::init<{}>())", GetFunctionParameters(ctor));
    }

    void SetDefaultConstructor(const CXXRecordDecl* record) override {
        auto recordName = GetFullRecordName(record);
        classes_[recordName].Declaration += "\n\t\t.def(py::init<>())";
    }

    void FoundField(const FieldDecl* field) override {
        auto recordName = GetFullRecordName(llvm::dyn_cast<CXXRecordDecl>(field->getParent()));
        auto& classDecl = classes_[recordName];

        classDecl.Declaration += std::format(
            "\n\t\t.def_readwrite(\"{}\", &{}::{})",
            field->getNameAsString(),
            recordName,
            field->getNameAsString()
        );
    }

    void FoundMethod(const CXXMethodDecl* method) override {
        auto recordName = GetFullRecordName(method->getParent());
        auto& classDecl = classes_[recordName];

        classDecl.Methods[method->getNameAsString()].push_back(method);
    }

    void FoundFunction(const FunctionDecl* function) override {
        auto functionDecl = std::format(
            "\n\tm.def(\"{}\", &{})",
            function->getNameAsString(),
            function->getNameAsString()
        );
        functions_.emplace_back(std::move(functionDecl));
    }

    ~TDefaultGenerator() override {
        for (auto& [recordName, decl] : classes_) {
            HandleClass(recordName, decl);
        }
        outputFile_ << std::endl;

        for (auto&& decl : functions_) {
            outputFile_ << std::move(decl) << ";\n";
        }
        outputFile_ << "\n}\n";

        outputFile_.close();
    }

private:
    // we need to declare all ancestors before class declaration
    void HandleClass(const std::string& recordName, TClassCtx& classCtx) {
        if (classCtx.WasHandled) {
            return;
        }
        for (const auto& base : classCtx.Bases) {
            HandleClass(base, classes_[base]);
        }

        outputFile_ << classCtx.Declaration;
        for (const auto& [_, methods] : classCtx.Methods) {
            HandleMethod(recordName, methods);
        }
        outputFile_ << ";\n";

        classCtx.WasHandled = true;
    }

    void HandleMethod(const std::string& recordName, const std::vector<const CXXMethodDecl*>& oneNameMethods) {
        bool needToOverload = oneNameMethods.size() > 1;
        for (const auto& method : oneNameMethods) {
            std::string methodSignature = needToOverload ?
                GetOverloadedMethod(recordName, method) :
                std::format("&{}::{}", recordName, method->getNameAsString());

            outputFile_ <<  std::format(
                "\n\t\t.{}(\"{}\", {})",
                method->isStatic() ? "def_static" : "def",
                method->getNameAsString(),
                methodSignature
            );
        }
    }

    std::string GetOverloadedMethod(const std::string& recordName, const CXXMethodDecl* method) {
        std::string result = std::format(
            "py::overload_cast<{}>(&{}::{}",
            GetFunctionParameters(method),
            recordName,
            method->getNameAsString()
        );

        return result + (method->isConst() ? ", py::const_)" : ")");
    }

    std::string GetFunctionParameters(const FunctionDecl* function) {
        return std::accumulate(function->param_begin(), function->param_end(), std::string(),
            [this](std::string accString, const ParmVarDecl* param) {
                std::string typeStr = getParamFullName(param);
                return accString.empty() ? typeStr : accString + ", " + typeStr;
            }
        );
    }

    std::string GetFullRecordName(const CXXRecordDecl* record) {
        std::string recordName;

        const auto *ctx = record->getParent();
        while (ctx) {
            if (const auto* parentRecordDecl = dyn_cast<CXXRecordDecl>(ctx)) {
                recordName = parentRecordDecl->getNameAsString() + "::" + recordName;
            } else if (const auto* namespaceDecl = dyn_cast<NamespaceDecl>(ctx)) {
                recordName = namespaceDecl->getNameAsString() + "::" + recordName;
            } else {
                break;
            }

            ctx = ctx->getParent();
        }

        recordName += record->getDeclName().getAsString();

        return recordName;
    }

    std::string getParamFullName(const ParmVarDecl *param) {
        if (!param)
            return "";

        QualType Type = param->getType().getCanonicalType();
        std::cout << "GOT TYPE: " << Type.getAsString() << std::endl;
        if (const CXXRecordDecl *recordDecl = Type->getAsCXXRecordDecl();
                recordDecl != nullptr && !recordDecl->isInStdNamespace()) {
                // we should not get full name of std:: structures as they often declared by "using" or smth
            return GetFullRecordName(recordDecl);
        }
        return Type.getAsString();
    }
};

std::unique_ptr<IGenerator> CreateDefaultGenerator(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager) {
    return std::make_unique<TDefaultGenerator>(outputPath, moduleName, headerManager);
}
