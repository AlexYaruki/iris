#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vmin(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v1.template at<typename T::elementType>(i) = T::length - i;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length/2; i++) {
        assert(result.template at<typename T::elementType>(i) <= v1.template at<typename T::elementType>(i));
        assert(result.template at<typename T::elementType>(i) <= v1.template at<typename T::elementType>(i));
    }
}

int main() {
    test_vmin(vmin_s8);
    test_vmin(vmin_s16);
    test_vmin(vmin_s32);

    test_vmin(vmin_u8);
    test_vmin(vmin_u16);
    test_vmin(vmin_u32);

    test_vmin(vmin_f32);
}
