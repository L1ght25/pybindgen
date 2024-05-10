#pragma once

#include "generator.h"
#include "util.h"

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include "clang/AST/DeclCXX.h"
#include <clang/Tooling/Tooling.h>

#include <string>
#include <unordered_set>

using namespace clang;
using namespace clang::ast_matchers;

class ClassFinder : public MatchFinder::MatchCallback {
public:
    ClassFinder(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager);

    virtual void run(const MatchFinder::MatchResult& result) override;

private:
    template <typename Type, typename TCallback>
    bool HandledMatch(const MatchFinder::MatchResult& result, TCallback callback) {
        const Type* record = result.Nodes.getNodeAs<Type>("id");
        if (record) {
            record->dump();
            callback(record);
            return true;
        }
        return false;
    }

    bool AlreadyHandled(const Decl* decl);
    bool IsExternMatch(const Decl* decl);  // check if match is not in requested headers
    bool NeedsToBeIgnored(const Decl* decl);  // check for "no_python" attribute

private:
    std::unordered_set<const Decl*> matches_;
    std::unique_ptr<IGenerator> generator_;
};

struct TGenContext {
    const tooling::CompilationDatabase& compilations;
    const std::vector<std::string> & sourceDirs;
    const std::string& generatedFilePath;
    const std::string& moduleName;
};

void RunGen(TGenContext ctx);
