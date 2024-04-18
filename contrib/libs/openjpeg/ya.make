# Generated by devtools/yamaker from nixpkgs 22.11.

LIBRARY()

LICENSE(
    BSD-2-Clause AND
    BSD-3-Clause
)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(2.5.2)

ORIGINAL_SOURCE(https://github.com/uclouvain/openjpeg/archive/v2.5.2.tar.gz)

ADDINCL(
    contrib/libs/openjpeg
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

IF (OS_WINDOWS)
    CFLAGS(
        GLOBAL /DOPJ_STATIC
        /DMUTEX_win32
    )
ELSE()
    CFLAGS(
        -DMUTEX_pthread
    )
ENDIF()

SRCS(
    bio.c
    cio.c
    dwt.c
    event.c
    function_list.c
    ht_dec.c
    image.c
    invert.c
    j2k.c
    jp2.c
    mct.c
    mqc.c
    openjpeg.c
    opj_clock.c
    opj_malloc.c
    pi.c
    sparse_array.c
    t1.c
    t2.c
    tcd.c
    tgt.c
    thread.c
)

END()