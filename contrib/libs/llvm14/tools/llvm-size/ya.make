# Generated by devtools/yamaker.

PROGRAM()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/BinaryFormat
    contrib/libs/llvm14/lib/Bitcode/Reader
    contrib/libs/llvm14/lib/Bitstream/Reader
    contrib/libs/llvm14/lib/Demangle
    contrib/libs/llvm14/lib/IR
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/MC/MCParser
    contrib/libs/llvm14/lib/Object
    contrib/libs/llvm14/lib/Option
    contrib/libs/llvm14/lib/Remarks
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/TextAPI
)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/llvm14/tools/llvm-size
    contrib/libs/llvm14/tools/llvm-size
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    llvm-size.cpp
)

END()