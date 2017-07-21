#include <iris.h>
#include <iostream>
#include <numeric>
#include <cassert>

using namespace iris;


template<typename T, size_t VectorLength = T::length, typename ElementType = typename T::elementType, size_t ElementSize = T::elementSize>
void test_vrshr_n(T(*func)(T,uint32_t)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<ElementType>(i) = i;
    }
    for(size_t i = 0; i < ElementSize; i++) {
        T result = func(v,i);
        for(size_t j = 0; j < T::length; j++) {
            std::cout << "Actual: " << std::to_string(result.template at<ElementType>(j)) << std::endl;
            ElementType expected = (ElementType)(j + (j % 2 == 0 ? 0 : 1)) >> i;
            std::cout << "Expected: " << std::to_string(expected) << std::endl;
            assert(result.template at<ElementType>(j) == expected);
        }
    }
    std::cout << std::endl;
    if(std::numeric_limits<ElementType>::is_signed) {
        for(size_t i = 0; i < T::length; i++) {
            ElementType x = -((ElementType)i);
            std::cout << std::to_string(x) << std::endl;
            v.template at<ElementType>(i) = x;
        }
        for(size_t i = 0; i < ElementSize; i++) {
            T result = func(v,i);
            for(size_t j = 0; j < T::length; j++) {
                std::cout << "Original: " << std::to_string(v.template at<ElementType>(j)) << std::endl;
                std::cout << "Actual: " << std::to_string(result.template at<ElementType>(j)) << std::endl;
                ElementType x = -((ElementType)j);
                ElementType expected = (x + (x % 2 == 0 ? 0 : 1)) >> i;
                std::cout << "Expected: " << std::to_string(expected) << std::endl;
                assert(result.template at<ElementType>(j) == expected);
            }
        }
    }
    
    std::cout << std::endl;
}


int main() {
    test_vrshr_n(vrshr_n_s8);
    test_vrshr_n(vrshr_n_s16);
    test_vrshr_n(vrshr_n_s32);
    test_vrshr_n(vrshr_n_s64);

    test_vrshr_n(vrshr_n_u8);
    test_vrshr_n(vrshr_n_u16);
    test_vrshr_n(vrshr_n_u32);
    test_vrshr_n(vrshr_n_u64);
    std::cout << "Quads" << std::endl;
    test_vrshr_n(vrshrq_n_s8);
    test_vrshr_n(vrshrq_n_s16);
    test_vrshr_n(vrshrq_n_s32);
    test_vrshr_n(vrshrq_n_s64);

    test_vrshr_n(vrshrq_n_u8);
    test_vrshr_n(vrshrq_n_u16);
    test_vrshr_n(vrshrq_n_u32);
    test_vrshr_n(vrshrq_n_u64);
}
