//===--- ImplementationInNamespaceCheck.h - clang-tidy ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_LLVMLIBC_IMPLEMENTATIONINNAMESPACECHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_LLVMLIBC_IMPLEMENTATIONINNAMESPACECHECK_H

#include "../ClangTidyCheck.h"

namespace clang::tidy::llvm_libc {

/// Checks all llvm-libc implementation is within the correct namespace.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/llvmlibc/implementation-in-namespace.html
class ImplementationInNamespaceCheck : public ClangTidyCheck {
public:
  ImplementationInNamespaceCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}

  bool isLanguageVersionSupported(const LangOptions &LangOpts) const override {
    return LangOpts.CPlusPlus;
  }
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace clang::tidy::llvm_libc

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_LLVMLIBC_IMPLEMENTATIONINNAMESPACECHECK_H
