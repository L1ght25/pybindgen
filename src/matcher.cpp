#include "matcher.h"

#include "clang/AST/NestedNameSpecifier.h"


ClassFinder::ClassFinder(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager)
: generator_(CreateDefaultGenerator(outputPath, moduleName, headerManager))
{}

void ClassFinder::run(const MatchFinder::MatchResult& result) {
    if (AlreadyHandled(result.Nodes.getNodeAs<Decl>("id"))) {
        return;
    }

    if (HandledMatch<CXXRecordDecl>(result, [&](const CXXRecordDecl* record) {
            is_public = record->isStruct();
            if (record->hasDefinition()) {
                generator_->FoundRecord(record);
            }
        })) {
        return;
    } else if (HandledMatch<AccessSpecDecl>(result, [&](const AccessSpecDecl* access) {
            is_public = access->getAccess() == AccessSpecifier::AS_public;
        })) {
        return;
    } else if (HandledMatch<CXXConstructorDecl>(result, [&](const CXXConstructorDecl* ctor) {
            generator_->FoundConstructor(ctor);
        })) {
        return;
    } else if (HandledMatch<CXXMethodDecl>(result, [&](const CXXMethodDecl* method) {
            if (is_public) {
                generator_->FoundMethod(method);
            }
        })) {
        return;
    } else if (HandledMatch<FieldDecl>(result, [&](const FieldDecl* field) {
            if (is_public) {
                generator_->FoundField(field);
            }
        })) {
        return;
    } else if (HandledMatch<FunctionDecl>(result, [&](const FunctionDecl* function) {
            generator_->FoundFunction(function);
        })) {
        return;
    }
}

bool ClassFinder::AlreadyHandled(const Decl* decl) {
    if (matches_.contains(decl)) {
            return true;
        }
    matches_.insert(decl);
    return false;
}
