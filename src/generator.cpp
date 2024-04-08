#include "generator.h"
#include "util.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"

#include <format>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>


void IGenerator::OnStart(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager) {
    outputFile_.open(outputPath, std::ios::out | std::ios::trunc);

    outputFile_ << "#include <pybind11/pybind11.h>\n\n";

    outputFile_ << headerManager.GetIncludes() << "\n\n";

    outputFile_ << "namespace py = pybind11;\n\n";

    outputFile_ << std::format(
        "PYBIND11_MODULE({}, m) ",
        moduleName
    ) << "{\n";
}

void IGenerator::OnEnd() {
    for (auto& [_, decl] : classes_) {
        if (!decl.has_ctor) {
            decl.generated_code += "\n\t\t.def(py::init<>())";
        }
        outputFile_ << decl.generated_code << ";";
    }

    outputFile_ << std::endl;

    for (auto&& decl : functions_) {
        outputFile_ << std::move(decl) << ";";
    }

    outputFile_ << "\n}\n";

    outputFile_.close();
}

class TDefaultGenerator : public IGenerator {
public:

    TDefaultGenerator(const std::string outputPath, const std::string& moduleName, const HeaderManager& headerManager)
    : IGenerator(outputPath, moduleName, headerManager)
    {}

    void FoundRecord(const CXXRecordDecl* record) override {
        auto recordName = record->getDeclName().getAsString();
        classes_[recordName].generated_code += std::format(
            "\n\tpy::class_<{}>(m, \"{}\")", recordName, recordName
        );
    }

    void FoundConstructor(const CXXConstructorDecl* ctor) override {
        auto& classCtx = classes_[ctor->getParent()->getDeclName().getAsString()];
        classCtx.has_ctor = true;
        auto& classDecl = classCtx.generated_code;

        classDecl += "\n\t\t.def(py::init<";

        auto templateArgs = std::accumulate(ctor->param_begin(), ctor->param_end(), std::string(),
            [](std::string accString, const ParmVarDecl* param) {
                std::string typeStr = param->getType().getAsString();
                return accString.empty() ? typeStr : accString + ", " + typeStr;
            }
        );

        classDecl += templateArgs + ">())";
    }

    void FoundField(const FieldDecl* field) override {
        auto recordName = field->getParent()->getDeclName().getAsString();
        auto& classDecl = classes_[recordName].generated_code;

        classDecl += std::format(
            "\n\t\t.def_readwrite(\"{}\", &{}::{})",
            field->getNameAsString(),
            recordName,
            field->getNameAsString()
        );
    }

    void FoundMethod(const CXXMethodDecl* method) override {
        auto recordName = method->getParent()->getDeclName().getAsString();
        auto& classDecl = classes_[recordName].generated_code;

        classDecl += std::format(
            "\n\t\t.def(\"{}\", &{}::{})",
            method->getNameAsString(),
            recordName,
            method->getNameAsString()
        );
    }

    void FoundFunction(const FunctionDecl* function) override {
        auto functionDecl = std::format(
            "\n\tm.def(\"{}\", &{})",
            function->getNameAsString(),
            function->getNameAsString()
        );
        functions_.emplace_back(std::move(functionDecl));
    }
};

std::unique_ptr<IGenerator> CreateDefaultGenerator(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager) {
    return std::make_unique<TDefaultGenerator>(outputPath, moduleName, headerManager);
}
