#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T, typename R>
void test_vcvt(R(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    R result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == static_cast<typename R::elementType>(static_cast<typename T::elementType>(i)));
    }
}

int main() {
    test_vcvt(vcvt_f32_u32);
    test_vcvt(vcvt_f32_s32);
    test_vcvt(vcvt_u32_f32);
    test_vcvt(vcvt_s32_f32);

    test_vcvt(vcvtq_f32_u32);
    test_vcvt(vcvtq_f32_s32);
    test_vcvt(vcvtq_u32_f32);
    test_vcvt(vcvtq_s32_f32);
}
