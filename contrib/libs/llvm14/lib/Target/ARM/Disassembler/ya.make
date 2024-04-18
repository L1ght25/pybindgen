# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/MC/MCDisassembler
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Target/ARM/MCTargetDesc
    contrib/libs/llvm14/lib/Target/ARM/TargetInfo
    contrib/libs/llvm14/lib/Target/ARM/Utils
)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/llvm14/lib/Target/ARM
    contrib/libs/llvm14/lib/Target/ARM
    contrib/libs/llvm14/lib/Target/ARM/Disassembler
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    ARMDisassembler.cpp
)

END()
