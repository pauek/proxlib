
#include <iostream>
#include "bigint.hh"
using namespace pro2;

int main() {
    bigint a = 2147483647;
    bigint b = 2147483647;
    bigint c = "10000000000000000000000000000000";

    a = a + b;
    a = a + b;
    a = a + b;
    a = a + b;

    std::cout << a << std::endl;
    std::cout << c - 1 << std::endl;
}
