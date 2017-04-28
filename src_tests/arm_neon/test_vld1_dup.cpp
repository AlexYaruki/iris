#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vld1_dup(T(*func)(typename T::elementType*)) {
    typename T::elementType x = 47;
    T result = func(&x);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == x);
    }
}

int main() {
    test_vld1_dup(vld1_dup_s8);
    test_vld1_dup(vld1_dup_s16);
    test_vld1_dup(vld1_dup_s32);
    test_vld1_dup(vld1_dup_s64);

    test_vld1_dup(vld1_dup_u8);
    test_vld1_dup(vld1_dup_u16);
    test_vld1_dup(vld1_dup_u32);
    test_vld1_dup(vld1_dup_u64);

    test_vld1_dup(vld1_dup_f32);

    test_vld1_dup(vld1q_dup_s8);
    test_vld1_dup(vld1q_dup_s16);
    test_vld1_dup(vld1q_dup_s32);
    test_vld1_dup(vld1q_dup_s64);

    test_vld1_dup(vld1q_dup_u8);
    test_vld1_dup(vld1q_dup_u16);
    test_vld1_dup(vld1q_dup_u32);
    test_vld1_dup(vld1q_dup_u64);

    test_vld1_dup(vld1q_dup_f32);
}
