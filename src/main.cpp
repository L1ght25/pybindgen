#include "clang/AST/DeclCXX.h"
#include "clang/AST/NestedNameSpecifier.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <iostream>
#include <unordered_set>

#include "generator.h"
#include "util.h"


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;


struct ClassFinder : public MatchFinder::MatchCallback {
    ClassFinder(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager)
    : generator_(CreateDefaultGenerator(outputPath, moduleName, headerManager))
    {}

    virtual void run(const MatchFinder::MatchResult& result) override {
        if (AlreadyHandled(result.Nodes.getNodeAs<Decl>("id"))) {
            return;
        }

        const CXXRecordDecl* record = result.Nodes.getNodeAs<CXXRecordDecl>("id");
        if (record) {
            is_public = record->isStruct();
            if (!record->hasDefinition()) {
                generator_->FoundRecord(record);
                record->dump();
            }
            return;
        }

        const AccessSpecDecl* access = result.Nodes.getNodeAs<AccessSpecDecl>("id");
        if (access) {
            access->dump();
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
            if (is_public) {
                generator_->FoundMethod(method);
                method->dump();
            }
            return;
        }

        const FieldDecl* field = result.Nodes.getNodeAs<FieldDecl>("id");
        if (field && is_public) {
            generator_->FoundField(field);
            field->dump();
            return;
        }

        const FunctionDecl* function = result.Nodes.getNodeAs<FunctionDecl>("id");
        if (function && (!function->isCXXClassMember() || is_public)) {
            generator_->FoundFunction(function);
            function->dump();
            return;
        }
    }

    private:

    bool AlreadyHandled(const Decl* decl) {
        if (matches_.contains(decl)) {
            return true;
        }
        matches_.insert(decl);
        return false;
    }

    std::unordered_set<const Decl*> matches_;
    std::unique_ptr<IGenerator> generator_;
    bool is_public{false};

};

static llvm::cl::OptionCategory MyToolCategory("My tool options");
static llvm::cl::opt<std::string> PythonLibName("l", llvm::cl::desc("Specify name of python lib"), llvm::cl::value_desc("name of python library"));
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);


int main(int argc, const char **argv) {

    PythonLibName.addCategory(MyToolCategory);

    auto op = CommonOptionsParser::create(argc, argv, MyToolCategory);

    HeaderManager manager(op->getSourcePathList());

    ClassFinder classFinder("./generated.cpp", "example", manager);
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

    GenerateLib(manager, "example");

    return 0;
}
