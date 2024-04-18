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

CFLAGS(
    -DBMP_SUPPORTED
    -DGIF_SUPPORTED
    -DPPM_SUPPORTED
    -DTARGA_SUPPORTED
)

SRCDIR(contrib/libs/libjpeg-turbo)

SRCS(
    cdjpeg.c
    djpeg.c
    rdcolmap.c
    rdswitch.c
    wrbmp.c
    wrgif.c
    wrppm.c
    wrtarga.c
)

END()
