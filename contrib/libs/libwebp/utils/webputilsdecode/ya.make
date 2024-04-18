# Generated by devtools/yamaker.

LIBRARY()

WITHOUT_LICENSE_TEXTS()

LICENSE(BSD-3-Clause)

ADDINCL(
    contrib/libs/libwebp/utils
    contrib/libs/libwebp/webp
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

CFLAGS(
    -DHAVE_CONFIG_H
)

SRCDIR(contrib/libs/libwebp/utils)

SRCS(
    bit_reader_utils.c
    color_cache_utils.c
    filters_utils.c
    huffman_utils.c
    quant_levels_dec_utils.c
    random_utils.c
    rescaler_utils.c
    thread_utils.c
    utils.c
)

END()
