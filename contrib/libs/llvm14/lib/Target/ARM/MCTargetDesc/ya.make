# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/BinaryFormat
    contrib/libs/llvm14/lib/MC
    contrib/libs/llvm14/lib/MC/MCDisassembler
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Target/ARM/TargetInfo
    contrib/libs/llvm14/lib/Target/ARM/Utils
)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/llvm14/lib/Target/ARM
    contrib/libs/llvm14/lib/Target/ARM
    contrib/libs/llvm14/lib/Target/ARM/MCTargetDesc
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    ARMAsmBackend.cpp
    ARMELFObjectWriter.cpp
    ARMELFStreamer.cpp
    ARMInstPrinter.cpp
    ARMMCAsmInfo.cpp
    ARMMCCodeEmitter.cpp
    ARMMCExpr.cpp
    ARMMCTargetDesc.cpp
    ARMMachORelocationInfo.cpp
    ARMMachObjectWriter.cpp
    ARMTargetStreamer.cpp
    ARMUnwindOpAsm.cpp
    ARMWinCOFFObjectWriter.cpp
    ARMWinCOFFStreamer.cpp
)

END()
