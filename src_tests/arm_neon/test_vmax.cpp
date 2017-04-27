#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vmax(T(*func)(T,T)) {
    T v1, v2;
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v1.template at<typename T::elementType>(i) = T::length - i;
    }
    T result = func(v1,v2);
    for(int i = 0; i < T::length/2; i++) {
        assert(result.template at<typename T::elementType>(i) >= v1.template at<typename T::elementType>(i));
        assert(result.template at<typename T::elementType>(i) >= v1.template at<typename T::elementType>(i));
    }
}

int main() {
    test_vmax(vmax_s8);
    test_vmax(vmax_s16);
    test_vmax(vmax_s32);

    test_vmax(vmax_u8);
    test_vmax(vmax_u16);
    test_vmax(vmax_u32);

    test_vmax(vmax_f32);

    test_vmax(vmaxq_s8);
    test_vmax(vmaxq_s16);
    test_vmax(vmaxq_s32);

    test_vmax(vmaxq_u8);
    test_vmax(vmaxq_u16);
    test_vmax(vmaxq_u32);

    test_vmax(vmaxq_f32);

}
