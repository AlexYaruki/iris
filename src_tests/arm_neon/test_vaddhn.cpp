#include <iris/iris.h>
#include <cassert>
#include <iostream>
#include <bitset>

using namespace iris;

template <typename T>
void printBinary(T value) {
    std::bitset<sizeof(T) * 8> bin(value);
    std::cout << "\t" << bin << std::endl;
}

template<typename T, typename R>
void test_vaddhn(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(1) << ((sizeof(typename T::elementType) * 8) / 2 ) ;
        v2.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(1) << ((sizeof(typename T::elementType) * 8) / 2 + 1) ;
        printBinary(v1.template at<typename T::elementType>(i));
        printBinary(v2.template at<typename T::elementType>(i));
        std::cout << std::endl;
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        printBinary(result.template at<typename R::elementType>(i));
        assert(result.template at<typename R::elementType>(i) == static_cast<typename T::elementType>(3));
    }
}


int main() {
    test_vaddhn(vaddhn_s16);
    test_vaddhn(vaddhn_s32);
    test_vaddhn(vaddhn_s64);
}
