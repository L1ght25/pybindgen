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

def test_static_method():
    assert test_lib.C.GetStatic() == 42

def test_with_namespace():
    assert test_lib.D.GetStatic() == 42

def test_simple_inheritance():
    child = test_lib.Child()
    assert child.child_method() == 43
    assert child.base_method() == 42

def test_multiple_inheritance():
    child = test_lib.Child2()
    assert child.child_method() == 43
    assert child.base_method() == 42
    assert child.base2_method() == 41

def test_overload():
    overloaded = test_lib.Overloaded()
    overloaded.Foo(3) == "with int"
    overloaded.Foo(4.2) == "with float"

def test_const_overload():
    overloaded = test_lib.ConstOverloaded()
    overloaded.Foo(3) == "with int const"
    overloaded.Foo(3) == "with int"

def test_internal_class():
    ctx = test_lib.ExternalContext()
    ctx.first = 1
    ctx.second = 2
    external = test_lib.External(ctx)
    assert external.GetFirst() == 1
    assert external.GetSecond() == 2