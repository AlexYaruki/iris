#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vand(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + T::length;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == (v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i)));
    }
}

int main() {
    test_vand(vand_s8);
    test_vand(vand_s16);
    test_vand(vand_s32);
    test_vand(vand_s64);

    test_vand(vand_u8);
    test_vand(vand_u16);
    test_vand(vand_u32);
    test_vand(vand_u64);

    test_vand(vandq_s8);
    test_vand(vandq_s16);
    test_vand(vandq_s32);
    test_vand(vandq_s64);

    test_vand(vandq_u8);
    test_vand(vandq_u16);
    test_vand(vandq_u32);
    test_vand(vandq_u64);
}
