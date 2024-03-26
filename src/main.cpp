#include "clang/AST/DeclCXX.h"
#include "clang/AST/NestedNameSpecifier.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <iostream>

#include "generator.h"


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;


struct ClassFinder : public MatchFinder::MatchCallback {
    ClassFinder(const std::string& outputPath, const std::string& moduleName)
    : generator_(CreateDefaultGenerator(outputPath, moduleName))
    {}

    virtual void run(const MatchFinder::MatchResult& result) override {
        const CXXRecordDecl* record = result.Nodes.getNodeAs<CXXRecordDecl>("id");
        if (record) {
            is_public = record->isStruct();
            FoundRecord(record);
            return;
        }

        const AccessSpecDecl* access = result.Nodes.getNodeAs<AccessSpecDecl>("id");
        if (access) {
            is_public = access->getAccess() == AccessSpecifier::AS_public;
            return;
        }

        const CXXConstructorDecl* ctor = result.Nodes.getNodeAs<CXXConstructorDecl>("id");
        if (ctor) {
            generator_->FoundConstructor(ctor);
            ctor->dump();
            return;
        }

        const CXXMethodDecl* method = result.Nodes.getNodeAs<CXXMethodDecl>("id");
        if (method) {
            generator_->FoundMethod(method);
            method->dump();
            return;
        }

        const FieldDecl* field = result.Nodes.getNodeAs<FieldDecl>("id");
        if (field && is_public) {
            FoundField(field);
            return;
        }

        const FunctionDecl* function = result.Nodes.getNodeAs<FunctionDecl>("id");
        if (function && (!function->isCXXClassMember() || is_public)) {
            FoundFunction(function);
            return;
        }
    }

    void FoundRecord(const CXXRecordDecl* record) {
      if (!record->hasDefinition()) {
        generator_->FoundRecord(record);
        record->dump();
      }
    }

    void FoundField(const FieldDecl* field) {
        generator_->FoundField(field);
        field->dump();
    }

    void FoundFunction(const FunctionDecl* func) {
        generator_->FoundFunction(func);
        func->dump();
    }

    private:
    std::unique_ptr<IGenerator> generator_;
    bool is_public{false};

};

static llvm::cl::OptionCategory MyToolCategory("My tool options");
static llvm::cl::opt<std::string> PythonLibName("l", llvm::cl::desc("Specify name of python lib"), llvm::cl::value_desc("name of python library"));
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
// static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");


int main(int argc, const char **argv) {

    PythonLibName.addCategory(MyToolCategory);

    auto op = CommonOptionsParser::create(argc, argv, MyToolCategory);

    ClassFinder classFinder("./test.cpp", "example");
    MatchFinder finder;

    DeclarationMatcher classMatcher = cxxRecordDecl(decl().bind("id"));
    DeclarationMatcher accessMatcher = accessSpecDecl(decl().bind("id"));
    DeclarationMatcher ctorMatcher = cxxConstructorDecl(decl().bind("id"));
    DeclarationMatcher methodMatcher = cxxMethodDecl(decl().bind("id"));
    DeclarationMatcher fieldMatcher = fieldDecl(decl().bind("id"));
    DeclarationMatcher funcMatcher = functionDecl(decl().bind("id"));

    finder.addMatcher(classMatcher, &classFinder);
    finder.addMatcher(accessMatcher, &classFinder);
    finder.addMatcher(ctorMatcher, &classFinder);
    finder.addMatcher(methodMatcher, &classFinder);
    finder.addMatcher(fieldMatcher, &classFinder);
    finder.addMatcher(funcMatcher, &classFinder);

    ClangTool tool(op->getCompilations(), op->getSourcePathList());
  
    tool.run(newFrontendActionFactory(&finder).get());

    return 0;
}
