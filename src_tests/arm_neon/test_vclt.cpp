#include <iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vclt(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i;
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
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
    test_vclt(vclt_u8);
    test_vclt(vclt_u16);
    test_vclt(vclt_u32);

    test_vclt(vclt_s8);
    test_vclt(vclt_s16);
    test_vclt(vclt_s32);

    test_vclt(vclt_f32);

    test_vclt(vcltq_u8);
    test_vclt(vcltq_u16);
    test_vclt(vcltq_u32);

    test_vclt(vcltq_s8);
    test_vclt(vcltq_s16);
    test_vclt(vcltq_s32);

    test_vclt(vcltq_f32);
}
