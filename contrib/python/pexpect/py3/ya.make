# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(4.9.0)

LICENSE(ISC)

PEERDIR(
    contrib/python/ptyprocess
)

NO_LINT()

NO_CHECK_IMPORTS(
    pexpect._async_pre_await
)

PY_SRCS(
    TOP_LEVEL
    pexpect/ANSI.py
    pexpect/FSM.py
    pexpect/__init__.py
    pexpect/_async.py
    pexpect/_async_pre_await.py
    pexpect/_async_w_await.py
    pexpect/exceptions.py
    pexpect/expect.py
    pexpect/fdpexpect.py
    pexpect/popen_spawn.py
    pexpect/pty_spawn.py
    pexpect/pxssh.py
    pexpect/replwrap.py
    pexpect/run.py
    pexpect/screen.py
    pexpect/socket_pexpect.py
    pexpect/spawnbase.py
    pexpect/utils.py
)

RESOURCE_FILES(
    PREFIX contrib/python/pexpect/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
    pexpect/bashrc.sh
)

END()
