# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/MC
    contrib/libs/llvm16/lib/Support
    contrib/libs/llvm16/lib/Target/LoongArch/TargetInfo
    contrib/libs/llvm16/lib/TargetParser
)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/llvm16/lib/Target/LoongArch
    contrib/libs/llvm16/lib/Target/LoongArch
    contrib/libs/llvm16/lib/Target/LoongArch/MCTargetDesc
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    LoongArchAsmBackend.cpp
    LoongArchBaseInfo.cpp
    LoongArchELFObjectWriter.cpp
    LoongArchELFStreamer.cpp
    LoongArchInstPrinter.cpp
    LoongArchMCAsmInfo.cpp
    LoongArchMCCodeEmitter.cpp
    LoongArchMCExpr.cpp
    LoongArchMCTargetDesc.cpp
    LoongArchMatInt.cpp
    LoongArchTargetStreamer.cpp
)

END()
