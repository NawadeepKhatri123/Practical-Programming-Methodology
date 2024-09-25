#include <iostream>

using VEC = int*;     //VEC is an alias for pointer to an int
using MATRIX = VEC*;  // MATRIX is an alias for a pointer to VEC

int main() {
    int a = 5;

    VEC v = &a;       // v points to a
    MATRIX m = &v;    // m points to v , a double pointer

    std::cout << "Value of a using v: " << *v << std::endl;
    std::cout << "Value of a using m: " << **m << std::endl;

    return 0;
}
