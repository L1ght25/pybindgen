PY23_LIBRARY()

SET(LIBNAME lib_example)

PY_REGISTER(py_${LIBNAME})

PEERDIR(
    contrib/libs/pybind11
)

DECLARE_IN_DIRS(ALL_HEADERS *.h DIRS . RECURSIVE SRCDIR ${ARCADIA_ROOT}/lib_example)

RUN_PROGRAM(
    src --python-lib-name=py_${LIBNAME} --generated-file-path=${ARCADIA_BUILD_ROOT}/py_build/generated.cpp -p ${ARCADIA_ROOT}/py_build ${ARCADIA_ROOT}/lib_example ${ARCADIA_ROOT}/lib_example/include
    CWD ${ARCADIA_BUILD_ROOT}/py_build
    OUT ${ARCADIA_BUILD_ROOT}/py_build/generated.cpp
    IN ${ALL_HEADERS_FILES}
    IN ${CURDIR}/compile_commands.json
)

ADDINCL(
    lib_example
    lib_example/include
)


END()
