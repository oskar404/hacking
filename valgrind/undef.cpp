
#include <iostream>

enum TestEnum {
    FIRST,
    SECOND,
    THIRD = 30
};


int main(int argc, char** argv)
{
    int i;
    TestEnum e;
    std::cout << "int i (undefined behaviour): " << i << std::endl;
    std::cout << "TestEnum e (undefined behaviour): " << e << std::endl;
    std::cout << "TestEnum::FIRST: " << TestEnum::FIRST << std::endl;
    return 0;
}
