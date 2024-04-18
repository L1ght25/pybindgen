# Generated by devtools/yamaker (pypi).

PY2_LIBRARY()

VERSION(4.5)

LICENSE(Apache-2.0)

PEERDIR(
    contrib/python/pyasn1
)

NO_LINT()

PY_SRCS(
    TOP_LEVEL
    rsa/__init__.py
    rsa/_compat.py
    rsa/asn1.py
    rsa/cli.py
    rsa/common.py
    rsa/core.py
    rsa/key.py
    rsa/machine_size.py
    rsa/parallel.py
    rsa/pem.py
    rsa/pkcs1.py
    rsa/pkcs1_v2.py
    rsa/prime.py
    rsa/randnum.py
    rsa/transform.py
    rsa/util.py
)

RESOURCE_FILES(
    PREFIX contrib/python/rsa/py2/
    .dist-info/METADATA
    .dist-info/entry_points.txt
    .dist-info/top_level.txt
)

END()

RECURSE_FOR_TESTS(
    tests
)
