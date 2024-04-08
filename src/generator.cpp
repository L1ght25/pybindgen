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


class TDefaultGenerator : public IGenerator {
public:

    TDefaultGenerator(const std::string outputPath, const std::string& moduleName, const HeaderManager& headerManager)
    : IGenerator(outputPath, moduleName, headerManager)
    {
        outputFile_.open(outputPath, std::ios::out | std::ios::trunc);

        outputFile_ << "#include <pybind11/pybind11.h>\n\n";
        outputFile_ << headerManager.GetIncludes() << "\n\n";

        outputFile_ << "namespace py = pybind11;\n\n";

        outputFile_ << std::format(
            "PYBIND11_MODULE({}, m) ",
            moduleName
        ) << "{\n";
    }

    void FoundRecord(const CXXRecordDecl* record) override {
        auto recordName = record->getDeclName().getAsString();
        classes_[recordName] += std::format(
            "\n\tpy::class_<{}>(m, \"{}\")", recordName, recordName
        );
    }

    void FoundConstructor(const CXXConstructorDecl* ctor) override {
        auto& classDecl = classes_[ctor->getParent()->getDeclName().getAsString()];

        classDecl += "\n\t\t.def(py::init<";

        auto templateArgs = std::accumulate(ctor->param_begin(), ctor->param_end(), std::string(),
            [](std::string accString, const ParmVarDecl* param) {
                std::string typeStr = param->getType().getAsString();
                return accString.empty() ? typeStr : accString + ", " + typeStr;
            }
        );

        classDecl += templateArgs + ">())";
    }

    void SetDefaultConstructor(std::string className) override {
        classes_[className] += "\n\t\t.def(py::init<>())";
    }

    void FoundField(const FieldDecl* field) override {
        auto recordName = field->getParent()->getDeclName().getAsString();
        auto& classDecl = classes_[recordName];

        classDecl += std::format(
            "\n\t\t.def_readwrite(\"{}\", &{}::{})",
            field->getNameAsString(),
            recordName,
            field->getNameAsString()
        );
    }

    void FoundMethod(const CXXMethodDecl* method) override {
        auto recordName = method->getParent()->getDeclName().getAsString();
        auto& classDecl = classes_[recordName];

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

    ~TDefaultGenerator() override {
        for (auto& [_, decl] : classes_) {
            outputFile_ << decl << ";";
        }
        outputFile_ << std::endl;

        for (auto&& decl : functions_) {
            outputFile_ << std::move(decl) << ";";
        }
        outputFile_ << "\n}\n";

        outputFile_.close();
    }
};

std::unique_ptr<IGenerator> CreateDefaultGenerator(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager) {
    return std::make_unique<TDefaultGenerator>(outputPath, moduleName, headerManager);
}
