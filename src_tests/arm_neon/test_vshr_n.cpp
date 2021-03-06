#include <iris/iris.h>
#include <iostream>
#include <numeric>
#include <cassert>

using namespace iris;


template<typename T, size_t VectorLength = T::length, typename ElementType = typename T::elementType, size_t ElementSize = T::elementSize>
void test_vshr_n(T(*func)(T,uint32_t)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<ElementType>(i) = std::numeric_limits<ElementType>::max();
    }
    for(size_t i = 0; i < ElementSize; i++) {
        T result = func(v,i);
        for(size_t j = 0; j < T::length; j++) {
            std::cout << "Actual: " << std::to_string(result.template at<ElementType>(j)) << std::endl;
            ElementType expected = std::numeric_limits<ElementType>::max() >> i;
            std::cout << "Expected: " << std::to_string(expected) << std::endl;
            assert(result.template at<ElementType>(j) == expected);
        }
    }
    
    std::cout << std::endl;
}


int main() {
    test_vshr_n(vshr_n_s8);
    test_vshr_n(vshr_n_s16);
    test_vshr_n(vshr_n_s32);
    test_vshr_n(vshr_n_s64);

    test_vshr_n(vshr_n_u8);
    test_vshr_n(vshr_n_u16);
    test_vshr_n(vshr_n_u32);
    test_vshr_n(vshr_n_u64);

    test_vshr_n(vshrq_n_s8);
    test_vshr_n(vshrq_n_s16);
    test_vshr_n(vshrq_n_s32);
    test_vshr_n(vshrq_n_s64);

    test_vshr_n(vshrq_n_u8);
    test_vshr_n(vshrq_n_u16);
    test_vshr_n(vshrq_n_u32);
    test_vshr_n(vshrq_n_u64);
}
