#include "matcher.h"

#include "clang/AST/NestedNameSpecifier.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;


ClassFinder::ClassFinder(const std::string& outputPath, const std::string& moduleName, const HeaderManager& headerManager)
: generator_(CreateDefaultGenerator(outputPath, moduleName, headerManager))
{}

void ClassFinder::run(const MatchFinder::MatchResult& result) {
    if (const clang::Decl* decl = result.Nodes.getNodeAs<Decl>("id");
        AlreadyHandled(decl) || IsExternMatch(decl)
    ) {
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

bool ClassFinder::IsExternMatch(const Decl* decl) {
    return !decl->getASTContext().getSourceManager().isWrittenInMainFile(decl->getLocation());
}


void RunGen(TGenContext ctx) {
    HeaderManager manager(ctx.sourceDirs);
    manager.PrintHeaders();

    ClassFinder classFinder(ctx.generatedFilePath, ctx.moduleName, manager);
    MatchFinder finder;

    DeclarationMatcher classMatcher = cxxRecordDecl(decl().bind("id"));
    DeclarationMatcher funcMatcher = functionDecl(decl().bind("id"));

    finder.addMatcher(classMatcher, &classFinder);
    finder.addMatcher(funcMatcher, &classFinder);

    ClangTool tool(ctx.compilations, manager.GetHeaders());

    tool.run(newFrontendActionFactory(&finder).get());
}
