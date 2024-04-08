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
            if (record->hasDefinition()) {
                generator_->FoundRecord(record);

                //handle all c-tors
                for (auto* ctor : record->ctors()) {
                    generator_->FoundConstructor(ctor);
                }
                if (record->needsImplicitDefaultConstructor()) {
                    generator_->SetDefaultConstructor(record->getNameAsString());
                }

                //handle all methods
                for (auto* method : record->methods()) {
                    if (method->getAccess() == clang::AS_public) {
                        generator_->FoundMethod(method);
                    }
                }

                //handle all fields
                for (auto* field : record->fields()) {
                    if (field->getAccess() == clang::AS_public) {
                        generator_->FoundField(field);
                    }
                }
            }
        })) {
    } else {
        HandledMatch<FunctionDecl>(result, [&](const FunctionDecl* function) {
            if (!function->isCXXClassMember()) {
                generator_->FoundFunction(function);
            }
        });
    }
}

bool ClassFinder::AlreadyHandled(const Decl* decl) {
    if (matches_.contains(decl)) {
            return true;
        }
    matches_.insert(decl);
    return false;
}
