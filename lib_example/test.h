#include <iostream>
#include <string>
#include <vector>


// simple class
class A {
    int first;
    int second;

public:
    int third;
    void pubbar();

private:
    void bar() {}
};

// custom constructor
class B {
public:
    B(std::string first, std::string second);

    std::string GetFirst();
    const std::string& GetSecond();
    std::vector<std::string> GetBoth();

private:
    std::string first_;
    std::string second_;
};

// static method
class C {
public:
    static int GetStatic() {
        return 42;
    }
};

// namespace
namespace TestNS {
class D {
public:
    static int GetStatic() {
        return 42;
    }
};
}

// simple inheritance
class Base {
public:
    int base_method() {
        return 42;
    }
};

class Child : public Base {
public:
    int child_method() {
        return 43;
    }
};

// multiple inheritance
class Base2 {
public:
    int base2_method() {
        return 41;
    }
};

class Child2 : public Base, public Base2 {
public:
    int child_method() {
        return 43;
    }
};

// ignore annotation
class [[clang::annotate("no_python")]] ShouldBeIgnored {  
public:
    int Noooo() {
        return 1337;
    }
};

// overloading method
class Overloaded {
public:
    std::string Foo(int a) {
        return "with int";
    }
    std::string Foo(float a) {
        return "with float";
    }
};

class ConstOverloaded {
public:
    std::string Foo(int a) {
        return "with int";
    }
    std::string Foo(int a) const {
        return "with int const";
    }
};

// internal class
class External {
public:
    struct ExternalContext {
        int first;
        int second;
    };

    External(ExternalContext ctx)
    : ctx_(ctx)
    {}

    int GetFirst() {
        return ctx_.first;
    }

    int GetSecond() {
        return ctx_.second;
    }

private:
    ExternalContext ctx_;
};

// test functions (nothing really interesting)
inline void foo() {
    return;
}

std::string test_string();
