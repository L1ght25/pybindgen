#include "generator.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"

#include <format>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>


void IGenerator::OnStart(const std::string& outputPath, const std::string& moduleName) {
    outputFile_.open(outputPath, std::ios::out | std::ios::app);

    outputFile_ << "#include <pybind11/pybind11.h>\n\n\n";

    outputFile_ << std::format(
        "PYBIND11_MODULE({}, m) ",
        moduleName
    ) << "{\n";
}

void IGenerator::OnEnd() {
    for (auto&& [_, decl] : classes_) {
        outputFile_ << std::move(decl) << ";";
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

    TDefaultGenerator(const std::string outputPath, const std::string& moduleName)
    : IGenerator(outputPath, moduleName)
    {}

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
};

std::unique_ptr<IGenerator> CreateDefaultGenerator(const std::string& outputPath, const std::string& moduleName) {
    return std::make_unique<TDefaultGenerator>(outputPath, moduleName);
}
