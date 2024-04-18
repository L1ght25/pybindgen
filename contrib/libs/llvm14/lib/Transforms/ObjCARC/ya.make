# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/include
    contrib/libs/llvm14/lib/Analysis
    contrib/libs/llvm14/lib/IR
    contrib/libs/llvm14/lib/Support
    contrib/libs/llvm14/lib/Transforms/Utils
)

ADDINCL(
    contrib/libs/llvm14/lib/Transforms/ObjCARC
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    DependencyAnalysis.cpp
    ObjCARC.cpp
    ObjCARCAPElim.cpp
    ObjCARCContract.cpp
    ObjCARCExpand.cpp
    ObjCARCOpts.cpp
    ProvenanceAnalysis.cpp
    ProvenanceAnalysisEvaluator.cpp
    PtrState.cpp
)

END()