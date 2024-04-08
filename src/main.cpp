#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include <iostream>
#include <unordered_set>

#include "generator.h"
#include "matcher.h"
#include "util.h"


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;


static llvm::cl::OptionCategory Opts("PybindGen options");
static llvm::cl::opt<std::string> PythonLibName("python-lib-name", llvm::cl::desc("name of python library"), llvm::cl::cat(Opts));
static llvm::cl::opt<std::string> GeneratedFilePath("generated-file-path", llvm::cl::desc("path to generated.cpp file"), llvm::cl::cat(Opts));


int main(int argc, const char **argv) {
    auto op = CommonOptionsParser::create(argc, argv, Opts);
    HeaderManager manager(op->getSourcePathList());

    for (const auto& str : manager.GetHeaders()) {
        std::cout << "found header: " << str << std::endl;
    }

    ClassFinder classFinder(GeneratedFilePath.getValue(), PythonLibName.getValue(), manager);
    MatchFinder finder;

    DeclarationMatcher classMatcher = cxxRecordDecl(decl().bind("id"));
    DeclarationMatcher funcMatcher = functionDecl(decl().bind("id"));

    finder.addMatcher(classMatcher, &classFinder);
    finder.addMatcher(funcMatcher, &classFinder);

    ClangTool tool(op->getCompilations(), manager.GetHeaders());

    tool.run(newFrontendActionFactory(&finder).get());

    return 0;
}
