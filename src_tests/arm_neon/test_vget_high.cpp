#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T, typename R>
void test_vget_high(R(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    R result = func(v);
    for(size_t i = 0, j = T::length/2; i < R::length; i++, j++) {
        assert(result.template at<typename R::elementType>(i) == static_cast<typename R::elementType>(j));
    }
}

int main() {
    test_vget_high(vget_high_s8);
    test_vget_high(vget_high_s16);
    test_vget_high(vget_high_s32);
    test_vget_high(vget_high_s64);

    test_vget_high(vget_high_u8);
    test_vget_high(vget_high_u16);
    test_vget_high(vget_high_u32);
    test_vget_high(vget_high_u64);

    test_vget_high(vget_high_f32);
}
