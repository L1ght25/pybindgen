PY23_LIBRARY()

PY_SRCS(
    prctl.pyx
)

BUILD_ONLY_IF(WARNING LINUX)

END()
