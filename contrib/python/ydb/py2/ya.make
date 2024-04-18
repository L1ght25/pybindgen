# Generated by devtools/yamaker (pypi).

PY2_LIBRARY()

VERSION(2.15.1)

LICENSE(Apache-2.0)

PEERDIR(
    contrib/deprecated/python/enum34
    contrib/python/grpcio
    contrib/python/packaging
    contrib/python/protobuf
    contrib/python/pytest
    contrib/python/six
)

NO_LINT()

NO_CHECK_IMPORTS(
    ydb.public.api.grpc
    ydb.public.api.grpc.*
)

PY_SRCS(
    TOP_LEVEL
    ydb/__init__.py
    ydb/_apis.py
    ydb/_errors.py
    ydb/_session_impl.py
    ydb/_sp_impl.py
    ydb/_tx_ctx_impl.py
    ydb/_utilities.py
    ydb/auth_helpers.py
    ydb/connection.py
    ydb/convert.py
    ydb/credentials.py
    ydb/dbapi/__init__.py
    ydb/dbapi/connection.py
    ydb/dbapi/cursor.py
    ydb/dbapi/errors.py
    ydb/default_pem.py
    ydb/driver.py
    ydb/export.py
    ydb/global_settings.py
    ydb/iam/__init__.py
    ydb/iam/auth.py
    ydb/import_client.py
    ydb/interceptor.py
    ydb/issues.py
    ydb/operation.py
    ydb/pool.py
    ydb/resolver.py
    ydb/scheme.py
    ydb/scripting.py
    ydb/settings.py
    ydb/sqlalchemy/__init__.py
    ydb/sqlalchemy/types.py
    ydb/table.py
    ydb/tracing.py
    ydb/types.py
    ydb/ydb_version.py
)

RESOURCE_FILES(
    PREFIX contrib/python/ydb/py2/
    .dist-info/METADATA
    .dist-info/top_level.txt
)

END()
