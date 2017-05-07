#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vld4_dup(T(*func)(typename T::vectorType::elementType*)) {
    typename T::vectorType::elementType data[T::lanes];
    for(size_t i = 0; i < T::lanes; i++) {
        data[i] = 47 + i;
    }
    T result = func(data);
    for(size_t i = 0; i < T::lanes; i++) {
        for(size_t j = 0; j < T::vectorType::length; j++) {
            assert(result.val[i].template at<typename T::vectorType::elementType>(j) == data[i]);
        }
    }
}

int main() {
    test_vld4_dup(vld4_dup_s8);
    test_vld4_dup(vld4_dup_s16);
    test_vld4_dup(vld4_dup_s32);
    test_vld4_dup(vld4_dup_s64);

    test_vld4_dup(vld4_dup_u8);
    test_vld4_dup(vld4_dup_u16);
    test_vld4_dup(vld4_dup_u32);
    test_vld4_dup(vld4_dup_u64);

    test_vld4_dup(vld4_dup_f32);

    test_vld4_dup(vld4q_dup_s8);
    test_vld4_dup(vld4q_dup_s16);
    test_vld4_dup(vld4q_dup_s32);
    test_vld4_dup(vld4q_dup_s64);

    test_vld4_dup(vld4q_dup_u8);
    test_vld4_dup(vld4q_dup_u16);
    test_vld4_dup(vld4q_dup_u32);
    test_vld4_dup(vld4q_dup_u64);

    test_vld4_dup(vld4q_dup_f32);
}
