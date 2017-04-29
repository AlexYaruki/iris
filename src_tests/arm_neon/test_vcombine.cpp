#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T, typename R>
void test_vcombine(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = T::length - (i + 1);
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < R::length/2; i++) {
        assert(result.template at<typename R::elementType>(i) == result.template at<typename R::elementType>(R::length - (i + 1)));
    }
}

int main() {
    test_vcombine(vcombine_u8);
    test_vcombine(vcombine_u16);
    test_vcombine(vcombine_u32);
    test_vcombine(vcombine_u64);

    test_vcombine(vcombine_s8);
    test_vcombine(vcombine_s16);
    test_vcombine(vcombine_s32);
    test_vcombine(vcombine_s64);

    test_vcombine(vcombine_f32);
}
