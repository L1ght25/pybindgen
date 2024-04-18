# Generated by devtools/yamaker (pypi).

PY2_LIBRARY()

VERSION(0.5)

LICENSE(MIT)

PEERDIR(
    library/python/symbols/win_unicode_console
)

NO_LINT()

NO_CHECK_IMPORTS(
    win_unicode_console.runner
)

PY_SRCS(
    TOP_LEVEL
    win_unicode_console/__init__.py
    win_unicode_console/buffer.py
    win_unicode_console/console.py
    win_unicode_console/file_object.py
    win_unicode_console/info.py
    win_unicode_console/raw_input.py
    win_unicode_console/readline_hook.py
    win_unicode_console/runner.py
    win_unicode_console/streams.py
    win_unicode_console/tokenize_open.py
    win_unicode_console/unicode_argv.py
)

RESOURCE_FILES(
    PREFIX contrib/deprecated/python/win-unicode-console/
    .dist-info/METADATA
    .dist-info/top_level.txt
)

END()
