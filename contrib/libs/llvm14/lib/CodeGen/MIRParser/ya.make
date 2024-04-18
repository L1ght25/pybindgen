# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/AsmParser
    contrib/libs/llvm14/lib/BinaryFormat
    contrib/libs/llvm14/lib/CodeGen
    contrib/libs/llvm14/lib/IR
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Target
)

ADDINCL(
    contrib/libs/llvm14/lib/CodeGen/MIRParser
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    MILexer.cpp
    MIParser.cpp
    MIRParser.cpp
)

END()
