import pytest
import sys

import py_main_lib as test_lib  # type: ignore


def test_simple_class():
    a = test_lib.A()
    assert a.third == 0

def test_simple_method():
    a = test_lib.A()
    a.pubbar()

def test_simple_function():
    test_lib.foo()

def test_simple_function_with_return():
    string = test_lib.test_string()
    assert string == "Got string!"

def test_class_with_ctor():
    b = test_lib.B('first', 'second')

    assert b.GetFirst() == 'first'
    assert b.GetSecond() == 'second'
    assert b.GetBoth() == ['first', 'second']

