#pragma once

#include "util.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include <memory>
#include <string>
#include <fstream>
#include <unordered_map>


using namespace clang;


class IGenerator {
public:
    IGenerator(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager) {}

    virtual void FoundRecord(const CXXRecordDecl* record) = 0;
    virtual void FoundConstructor(const CXXConstructorDecl* ctor) = 0;
    virtual void SetDefaultConstructor(const CXXRecordDecl* record) = 0;
    virtual void FoundField(const FieldDecl* field) = 0;
    virtual void FoundMethod(const CXXMethodDecl* method) = 0;

    virtual void FoundFunction(const FunctionDecl* function) = 0;

    virtual ~IGenerator() = default;

protected:
    struct TClassCtx {
        std::string Declaration;
        std::vector<std::string> Bases;
        std::unordered_map<std::string, std::vector<const CXXMethodDecl*>> Methods;
        bool WasHandled{false};
    };

    std::unordered_map<std::string, TClassCtx> classes_;
    std::vector<std::string> functions_;
    std::ofstream outputFile_;
};


std::unique_ptr<IGenerator> CreateDefaultGenerator(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager);
