#include "test.h"

void A::pubbar() {
    std::cout << "Invoked pubbar()" << std::endl;
}

B::B(std::string first, std::string second)
: first_(std::move(first)), second_(std::move(second))
{}

std::string B::GetFirst() {
    return first_;
}

const std::string& B::GetSecond() {
    return second_;
}

std::vector<std::string> B::GetBoth() {
    return {first_, second_};
}

std::string test_string() {
    return "Got string!";
}
