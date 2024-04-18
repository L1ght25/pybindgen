# Generated by devtools/yamaker (pypi).

PY2_LIBRARY()

VERSION(3.1.1)

LICENSE(MIT)

NO_LINT()

PY_SRCS(
    TOP_LEVEL
    cachetools/__init__.py
    cachetools/abc.py
    cachetools/cache.py
    cachetools/func.py
    cachetools/keys.py
    cachetools/lfu.py
    cachetools/lru.py
    cachetools/rr.py
    cachetools/ttl.py
)

RESOURCE_FILES(
    PREFIX contrib/python/cachetools/py2/
    .dist-info/METADATA
    .dist-info/top_level.txt
)

END()
