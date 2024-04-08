#include <clang/Tooling/CommonOptionsParser.h>

#include <iostream>
#include <unordered_set>

#include "matcher.h"


static llvm::cl::OptionCategory Opts("PybindGen options");
static llvm::cl::opt<std::string> PythonLibName("python-lib-name", llvm::cl::desc("name of python library"), llvm::cl::cat(Opts));
static llvm::cl::opt<std::string> GeneratedFilePath("generated-file-path", llvm::cl::desc("path to generated.cpp file"), llvm::cl::cat(Opts));


int main(int argc, const char **argv) {
    auto op = clang::tooling::CommonOptionsParser::create(argc, argv, Opts);

    RunGen(TGenContext{
        .compilations = op->getCompilations(),
        .sourceDirs = op->getSourcePathList(),
        .generatedFilePath = GeneratedFilePath.getValue(),
        .moduleName = PythonLibName.getValue()
    });

    return 0;
}
