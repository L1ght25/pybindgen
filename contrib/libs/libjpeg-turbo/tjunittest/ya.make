# Generated by devtools/yamaker.

PROGRAM()

WITHOUT_LICENSE_TEXTS()

PEERDIR(
    contrib/libs/libjpeg-turbo
)

ADDINCL(
    contrib/libs/libjpeg-turbo
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

SRCDIR(contrib/libs/libjpeg-turbo)

SRCS(
    md5/md5.c
    md5/md5hl.c
    tjunittest.c
    tjutil.c
)

END()
