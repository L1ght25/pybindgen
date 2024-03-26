#pragma once

#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include <memory>
#include <string>
#include <fstream>


using namespace clang;


class IGenerator {
public:
    IGenerator(const std::string& outputPath, const std::string& moduleName)
    {
        OnStart(outputPath, moduleName);
    }

    virtual void FoundRecord(const CXXRecordDecl* record) = 0;
    virtual void FoundConstructor(const CXXConstructorDecl* ctor) = 0;
    virtual void FoundField(const FieldDecl* field) = 0;
    virtual void FoundMethod(const CXXMethodDecl* method) = 0;

    virtual void FoundFunction(const FunctionDecl* function) = 0;

    virtual ~IGenerator() {
        OnEnd();
    }

private:
    void OnStart(const std::string& outputPath, const std::string& moduleName);
    void OnEnd();

protected:
    std::unordered_map<std::string, std::string> classes_;
    std::vector<std::string> functions_;
    std::ofstream outputFile_;
};


std::unique_ptr<IGenerator> CreateDefaultGenerator(const std::string& outputPath, const std::string& moduleName);
