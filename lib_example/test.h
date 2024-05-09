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

inline void foo() {
    return;
}

std::string test_string();
