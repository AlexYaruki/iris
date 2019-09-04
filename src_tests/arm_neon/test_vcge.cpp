#include <iris/iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vcge(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i;
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i+1;
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i+1;
        v2.template at<typename T::elementType>(i) = i;
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }
}

int main() {
    test_vcge(vcge_u8);
    test_vcge(vcge_u16);
    test_vcge(vcge_u32);

    test_vcge(vcge_s8);
    test_vcge(vcge_s16);
    test_vcge(vcge_s32);

    test_vcge(vcge_f32);

    test_vcge(vcgeq_u8);
    test_vcge(vcgeq_u16);
    test_vcge(vcgeq_u32);

    test_vcge(vcgeq_s8);
    test_vcge(vcgeq_s16);
    test_vcge(vcgeq_s32);

    test_vcge(vcgeq_f32);
}
