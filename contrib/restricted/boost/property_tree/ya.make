# Generated by devtools/yamaker from nixpkgs 22.11.

LIBRARY()

LICENSE(BSL-1.0)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(1.84.0)

ORIGINAL_SOURCE(https://github.com/boostorg/property_tree/archive/boost-1.84.0.tar.gz)

PEERDIR(
    contrib/restricted/boost/any
    contrib/restricted/boost/assert
    contrib/restricted/boost/bind
    contrib/restricted/boost/config
    contrib/restricted/boost/core
    contrib/restricted/boost/iterator
    contrib/restricted/boost/mpl
    contrib/restricted/boost/multi_index
    contrib/restricted/boost/optional
    contrib/restricted/boost/range
    contrib/restricted/boost/serialization
    contrib/restricted/boost/static_assert
    contrib/restricted/boost/throw_exception
    contrib/restricted/boost/type_traits
)

ADDINCL(
    GLOBAL contrib/restricted/boost/property_tree/include
)

NO_COMPILER_WARNINGS()

NO_UTIL()

END()