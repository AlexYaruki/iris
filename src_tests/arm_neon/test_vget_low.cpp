#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T, typename R>
void test_vget_low(R(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    R result = func(v);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == static_cast<typename R::elementType>(i));
    }
}

int main() {
    test_vget_low(vget_low_s8);
    test_vget_low(vget_low_s16);
    test_vget_low(vget_low_s32);
    test_vget_low(vget_low_s64);

    test_vget_low(vget_low_u8);
    test_vget_low(vget_low_u16);
    test_vget_low(vget_low_u32);
    test_vget_low(vget_low_u64);

    test_vget_low(vget_low_f32);
}
