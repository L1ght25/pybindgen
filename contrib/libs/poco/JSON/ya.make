# Generated by devtools/yamaker.

LIBRARY()

LICENSE(BSL-1.0)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/poco/Foundation
)

ADDINCL(
    GLOBAL contrib/libs/poco/JSON/include
    contrib/libs/poco/Foundation/include
    contrib/libs/poco/JSON/src
)

NO_COMPILER_WARNINGS()

NO_UTIL()

CFLAGS(
    -DPOCO_ENABLE_CPP11
    -DPOCO_ENABLE_CPP14
    -DPOCO_NO_AUTOMATIC_LIBS
    -DPOCO_UNBUNDLED
)

IF (OS_DARWIN)
    CFLAGS(
        -DPOCO_OS_FAMILY_UNIX
        -DPOCO_NO_STAT64
    )
ELSEIF (OS_LINUX)
    CFLAGS(
        -DPOCO_OS_FAMILY_UNIX
        -DPOCO_HAVE_FD_EPOLL
    )
ELSEIF (OS_WINDOWS)
    CFLAGS(
        -DPOCO_OS_FAMILY_WINDOWS
    )
ENDIF()

SRCS(
    src/Array.cpp
    src/Handler.cpp
    src/JSONException.cpp
    src/Object.cpp
    src/ParseHandler.cpp
    src/Parser.cpp
    src/ParserImpl.cpp
    src/PrintHandler.cpp
    src/Query.cpp
    src/Stringifier.cpp
    src/Template.cpp
    src/TemplateCache.cpp
    src/pdjson.c
)

END()