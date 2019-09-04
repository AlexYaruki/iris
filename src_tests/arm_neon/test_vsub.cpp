#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vsub(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    T result = func(v2,v1);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == 1);
    }
}


int main() {
    test_vsub(vsub_s8);
    test_vsub(vsub_s16);
    test_vsub(vsub_s32);
    test_vsub(vsub_s64);

    test_vsub(vsub_u8);
    test_vsub(vsub_u16);
    test_vsub(vsub_u32);
    test_vsub(vsub_u64);

    test_vsub(vsub_f32);

    test_vsub(vsubq_s8);
    test_vsub(vsubq_s16);
    test_vsub(vsubq_s32);
    test_vsub(vsubq_s64);

    test_vsub(vsubq_u8);
    test_vsub(vsubq_u16);
    test_vsub(vsubq_u32);
    test_vsub(vsubq_u64);

    test_vsub(vsubq_f32);
}
