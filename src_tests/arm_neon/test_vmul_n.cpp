#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmul_n(T(*func)(T,typename T::elementType)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    T result = func(v,10);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i * 10));
    }
}

int main() {
    test_vmul_n(vmul_n_s16);
    test_vmul_n(vmul_n_s32);

    test_vmul_n(vmul_n_u16);
    test_vmul_n(vmul_n_u32);

    test_vmul_n(vmul_n_f32);

    test_vmul_n(vmulq_n_s16);
    test_vmul_n(vmulq_n_s32);

    test_vmul_n(vmulq_n_u16);
    test_vmul_n(vmulq_n_u32);

    test_vmul_n(vmulq_n_f32);
}
