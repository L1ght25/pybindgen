# Generated by devtools/yamaker.

PROGRAM()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm16
    contrib/libs/llvm16/include
    contrib/libs/llvm16/lib/AsmParser
    contrib/libs/llvm16/lib/BinaryFormat
    contrib/libs/llvm16/lib/Bitcode/Reader
    contrib/libs/llvm16/lib/Bitstream/Reader
    contrib/libs/llvm16/lib/DebugInfo/CodeView
    contrib/libs/llvm16/lib/DebugInfo/DWARF
    contrib/libs/llvm16/lib/DebugInfo/MSF
    contrib/libs/llvm16/lib/DebugInfo/PDB
    contrib/libs/llvm16/lib/DebugInfo/Symbolize
    contrib/libs/llvm16/lib/Demangle
    contrib/libs/llvm16/lib/IR
    contrib/libs/llvm16/lib/IRReader
    contrib/libs/llvm16/lib/MC
    contrib/libs/llvm16/lib/MC/MCParser
    contrib/libs/llvm16/lib/Object
    contrib/libs/llvm16/lib/Remarks
    contrib/libs/llvm16/lib/Support
    contrib/libs/llvm16/lib/TargetParser
    contrib/libs/llvm16/lib/TextAPI
)

ADDINCL(
    contrib/libs/llvm16/tools/sanstats
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    sanstats.cpp
)

END()
