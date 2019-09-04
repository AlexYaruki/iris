#include <iris/iris.h>
#include <iostream>
#include <numeric>
#include <cassert>

using namespace iris;


template<typename T>
void test_vqsub(T(*func)(T,T)) {
    T v1, v2;
    std::cout << ">>>> Underflow" << std::endl;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
        v2.template at<typename T::elementType>(i) = i;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        if(std::is_signed<typename T::elementType>::value) {
            std::cout << "(" << static_cast<int64_t>(v1.template at<typename T::elementType>(i)) << " - " << static_cast<int64_t>(v2.template at<typename T::elementType>(i)) << ")"
                      << " Expected: " << static_cast<int64_t>(std::numeric_limits<typename T::elementType>::min())
                      << ", actual: " << static_cast<int64_t>(result.template at<typename T::elementType>(i)) << std::endl;
        } else {
            std::cout << "(" << static_cast<uint64_t>(v1.template at<typename T::elementType>(i)) << " - " << static_cast<uint64_t>(v2.template at<typename T::elementType>(i)) << ")"
                      << " Expected: " << static_cast<uint64_t>(std::numeric_limits<typename T::elementType>::min())
                      << ", actual: " << static_cast<uint64_t>(result.template at<typename T::elementType>(i)) << std::endl;
        }
        assert(result.template at<typename T::elementType>(i) == std::numeric_limits<typename T::elementType>::min());
    }
    if(std::numeric_limits<typename T::elementType>::is_signed) {
        std::cout << ">>>> Overflow " << std::endl;
        for(size_t i = 0; i < T::length; i++) {
            v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
            v2.template at<typename T::elementType>(i) = -i;
        }
        result = func(v1,v2);
        for(size_t i = 0; i < T::length; i++) {
            std::cout << "(" << static_cast<int64_t>(v1.template at<typename T::elementType>(i)) << " - " << static_cast<int64_t>(v2.template at<typename T::elementType>(i)) << ")"
                          << " Expected: " << static_cast<int64_t>(std::numeric_limits<typename T::elementType>::max())
                          << ", actual: " << static_cast<int64_t>(result.template at<typename T::elementType>(i)) << std::endl;
            assert(result.template at<typename T::elementType>(i) == std::numeric_limits<typename T::elementType>::max());
        }
    }
}


int main() {
    test_vqsub(vqsub_s8);
    test_vqsub(vqsub_s16);
    test_vqsub(vqsub_s32);
    test_vqsub(vqsub_s64);

    test_vqsub(vqsub_u8);
    test_vqsub(vqsub_u16);
    test_vqsub(vqsub_u32);
    test_vqsub(vqsub_u64);

    test_vqsub(vqsubq_s8);
    test_vqsub(vqsubq_s16);
    test_vqsub(vqsubq_s32);
    test_vqsub(vqsubq_s64);

    test_vqsub(vqsubq_u8);
    test_vqsub(vqsubq_u16);
    test_vqsub(vqsubq_u32);
    test_vqsub(vqsubq_u64);
}
