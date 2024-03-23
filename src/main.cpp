#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <iostream>


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;


struct ClassFinder : public MatchFinder::MatchCallback {
    virtual void run(const MatchFinder::MatchResult& result) override {
        const CXXRecordDecl* record = result.Nodes.getNodeAs<CXXRecordDecl>("id");
        if (record) {
            FoundRecord(record);
        }

        const FieldDecl* field = result.Nodes.getNodeAs<FieldDecl>("id");
        if (field) {
            FoundField(field);
        }

        const FunctionDecl* function = result.Nodes.getNodeAs<FunctionDecl>("id");
        if (function) {
            FoundFunction(function);
        }
    }

    void FoundRecord(const CXXRecordDecl* record) {
      if (!record->hasDefinition()) {
        std::cout << record->getDeclName().getAsString() << std::endl;
        record->dump();
      }
    }

    void FoundField(const FieldDecl* field) {
        field->dump();
    }

    void FoundFunction(const FunctionDecl* func) {
        func->dump();
    }
};

static llvm::cl::OptionCategory MyToolCategory("My tool options");
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");
static llvm::cl::opt<bool> YourOwnOption(...);


int main(int argc, const char **argv) {
    auto op = CommonOptionsParser::create(argc, argv, MyToolCategory);

    ClassFinder classFinder;
    MatchFinder finder;

    DeclarationMatcher classMatcher = cxxRecordDecl(decl().bind("id"));
    DeclarationMatcher fieldMatcher = fieldDecl(decl().bind("id"));
    DeclarationMatcher funcMatcher = functionDecl(decl().bind("id"));
    
    finder.addMatcher(classMatcher, &classFinder);
    finder.addMatcher(fieldMatcher, &classFinder);
    finder.addMatcher(funcMatcher, &classFinder);

    ClangTool tool(op->getCompilations(), op->getSourcePathList());
  
    tool.run(newFrontendActionFactory(&finder).get());

    return 0;
}
