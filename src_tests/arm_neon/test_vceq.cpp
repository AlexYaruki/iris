#include <iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vceq(R(*func)(T,T)) {
    T v1, v2;
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i;
    }
    R result = func(v1,v2);
    for(int i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }

    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i+1;
    }
    result = func(v1,v2);
    for(int i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }

    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i+1;
        v2.template at<typename T::elementType>(i) = i;
    }
    result = func(v1,v2);
    for(int i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }
}

int main() {
    test_vceq(vceq_u8);
    test_vceq(vceq_u16);
    test_vceq(vceq_u32);

    test_vceq(vceq_s8);
    test_vceq(vceq_s16);
    test_vceq(vceq_s32);

    test_vceq(vceq_f32);

    test_vceq(vceqq_u8);
    test_vceq(vceqq_u16);
    test_vceq(vceqq_u32);

    test_vceq(vceqq_s8);
    test_vceq(vceqq_s16);
    test_vceq(vceqq_s32);

    test_vceq(vceqq_f32);
}
