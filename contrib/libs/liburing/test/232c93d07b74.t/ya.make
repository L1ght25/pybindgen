# Generated by devtools/yamaker.

PROGRAM()

WITHOUT_LICENSE_TEXTS()

LICENSE(MIT)

PEERDIR(
    contrib/libs/liburing
)

ADDINCL(
    contrib/libs/liburing/src/include
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

CFLAGS(
    -DLIBURING_BUILD_TEST
    -D__SANE_USERSPACE_TYPES__
)

SRCDIR(contrib/libs/liburing/test)

SRCS(
    232c93d07b74.c
    helpers.c
)

END()
