#include <iris/iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vcle(R(*func)(T,T)) {
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
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i+1;
        v2.template at<typename T::elementType>(i) = i;
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }
}

int main() {
    test_vcle(vcle_u8);
    test_vcle(vcle_u16);
    test_vcle(vcle_u32);

    test_vcle(vcle_s8);
    test_vcle(vcle_s16);
    test_vcle(vcle_s32);

    test_vcle(vcle_f32);

    test_vcle(vcleq_u8);
    test_vcle(vcleq_u16);
    test_vcle(vcleq_u32);

    test_vcle(vcleq_s8);
    test_vcle(vcleq_s16);
    test_vcle(vcleq_s32);

    test_vcle(vcleq_f32);
}
