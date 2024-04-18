# Generated by devtools/yamaker.

PROGRAM(clang-apply-replacements)

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/clang16
    contrib/libs/clang16/include
    contrib/libs/clang16/lib/AST
    contrib/libs/clang16/lib/ASTMatchers
    contrib/libs/clang16/lib/Analysis
    contrib/libs/clang16/lib/Basic
    contrib/libs/clang16/lib/Driver
    contrib/libs/clang16/lib/Edit
    contrib/libs/clang16/lib/Format
    contrib/libs/clang16/lib/Frontend
    contrib/libs/clang16/lib/Index
    contrib/libs/clang16/lib/Lex
    contrib/libs/clang16/lib/Parse
    contrib/libs/clang16/lib/Rewrite
    contrib/libs/clang16/lib/Sema
    contrib/libs/clang16/lib/Serialization
    contrib/libs/clang16/lib/Support
    contrib/libs/clang16/lib/Tooling/Core
    contrib/libs/clang16/lib/Tooling/Inclusions
    contrib/libs/clang16/lib/Tooling/Refactoring
    contrib/libs/clang16/tools/extra/clang-apply-replacements/lib/Tooling
    contrib/libs/llvm16
    contrib/libs/llvm16/lib/Support
)

ADDINCL(
    contrib/libs/clang16/tools/extra/clang-apply-replacements
    contrib/libs/clang16/tools/extra/clang-apply-replacements/include
    contrib/libs/clang16/tools/extra/clang-apply-replacements/tool
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    ClangApplyReplacementsMain.cpp
)

END()
