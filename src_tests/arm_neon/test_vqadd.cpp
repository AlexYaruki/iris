#include <iris.h>
#include <iostream>
#include <numeric>
#include <cassert>

using namespace iris;


template<typename T>
void test_vqadd(T(*func)(T,T)) {
    T v1, v2;
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max() - i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    T result = func(v1,v2);
    for(int i = 0; i < T::length; i++) {
        if(std::is_signed<typename T::elementType>::value) {
            std::cout << "Expected: " << static_cast<int64_t>(std::numeric_limits<typename T::elementType>::max())
                      << ", actual: " << static_cast<int64_t>(result.template at<typename T::elementType>(i)) << std::endl;
        } else {
            std::cout << "Expected: " << static_cast<uint64_t>(std::numeric_limits<typename T::elementType>::max())
                      << ", actual: " << static_cast<uint64_t>(result.template at<typename T::elementType>(i)) << std::endl;
        }
        assert(result.template at<typename T::elementType>(i) == std::numeric_limits<typename T::elementType>::max());
    }
}


int main() {
    test_vqadd(vqadd_s8);
    test_vqadd(vqadd_s16);
    test_vqadd(vqadd_s32);
    test_vqadd(vqadd_s64);

    test_vqadd(vqadd_u8);
    test_vqadd(vqadd_u16);
    test_vqadd(vqadd_u32);
    test_vqadd(vqadd_u64);

    test_vqadd(vqaddq_s8);
    test_vqadd(vqaddq_s16);
    test_vqadd(vqaddq_s32);
    test_vqadd(vqaddq_s64);

    test_vqadd(vqaddq_u8);
    test_vqadd(vqaddq_u16);
    test_vqadd(vqaddq_u32);
    test_vqadd(vqaddq_u64);
}
