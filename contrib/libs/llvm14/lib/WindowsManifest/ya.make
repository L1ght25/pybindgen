# Generated by devtools/yamaker.

LIBRARY()

LICENSE(Apache-2.0 WITH LLVM-exception)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/llvm14
    contrib/libs/llvm14/lib/Support
)

ADDINCL(
    contrib/libs/llvm14/lib/WindowsManifest
)

NO_COMPILER_WARNINGS()

NO_UTIL()

SRCS(
    WindowsManifestMerger.cpp
)

END()
