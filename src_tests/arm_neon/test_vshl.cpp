#include <iris.h>
#include <iostream>
#include <numeric>
#include <cassert>

using namespace iris;


template<typename T, size_t VectorLength = T::length, typename ElementType = typename T::elementType, size_t ElementSize = T::elementSize>
void test_vshl(T(*func)(T,T)) {
    T v1,v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<ElementType>(i) = 1;
        v2.template at<ElementType>(i) = i % ElementSize;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        std::cout << "Actual: " << std::to_string(result.template at<ElementType>(i)) << std::endl;
        ElementType expected = ((ElementType)1) << i % ElementSize;
        std::cout << "Expected: " << std::to_string(expected) << std::endl;
        assert(result.template at<ElementType>(i) == expected);
    }
    if(std::numeric_limits<ElementType>::is_signed) {
        for(size_t i = 0; i < T::length; i++) {
            v1.template at<ElementType>(i) = std::numeric_limits<ElementType>::max();
            v2.template at<ElementType>(i) = -(i % ElementSize);
        }
        result = func(v1,v2);
        for(size_t i = 0; i < T::length; i++) {
            std::cout << "Actual: " << std::to_string(result.template at<ElementType>(i)) << std::endl;
            ElementType expected = std::numeric_limits<ElementType>::max() >> (i % ElementSize);
            std::cout << "Expected: " << std::to_string(expected) << std::endl;
            assert(result.template at<ElementType>(i) == expected);
        }
    }
    
    std::cout << std::endl;
}


int main() {
    test_vshl(vshl_s8);
    test_vshl(vshl_s16);
    test_vshl(vshl_s32);
    test_vshl(vshl_s64);

    test_vshl(vshl_u8);
    test_vshl(vshl_u16);
    test_vshl(vshl_u32);
    test_vshl(vshl_u64);

    test_vshl(vshlq_s8);
    test_vshl(vshlq_s16);
    test_vshl(vshlq_s32);
    test_vshl(vshlq_s64);

    test_vshl(vshlq_u8);
    test_vshl(vshlq_u16);
    test_vshl(vshlq_u32);
    test_vshl(vshlq_u64);
}
