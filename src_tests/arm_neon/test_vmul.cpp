#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmul(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i + 1;
        v2.template at<typename T::elementType>(i) = T::length - i;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) = (i + 1) * (T::length - 1));
    }
}


int main() {
    test_vmul(vmul_s8);
    test_vmul(vmul_s16);
    test_vmul(vmul_s32);

    test_vmul(vmul_u8);
    test_vmul(vmul_u16);
    test_vmul(vmul_u32);

    test_vmul(vmul_f32);

    test_vmul(vmulq_s8);
    test_vmul(vmulq_s16);
    test_vmul(vmulq_s32);

    test_vmul(vmulq_u8);
    test_vmul(vmulq_u16);
    test_vmul(vmulq_u32);

    test_vmul(vmulq_f32);
}
