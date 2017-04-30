#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vbic(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + T::length;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        typename T::elementType x = ~(v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i));
        typename T::elementType y = result.template at<typename T::elementType>(i);
        assert(x == y);
    }
}

int main() {
    test_vbic(vbic_s8);
    test_vbic(vbic_s16);
    test_vbic(vbic_s32);
    test_vbic(vbic_s64);

    test_vbic(vbic_u8);
    test_vbic(vbic_u16);
    test_vbic(vbic_u32);
    test_vbic(vbic_u64);

    test_vbic(vbicq_s8);
    test_vbic(vbicq_s16);
    test_vbic(vbicq_s32);
    test_vbic(vbicq_s64);

    test_vbic(vbicq_u8);
    test_vbic(vbicq_u16);
    test_vbic(vbicq_u32);
    test_vbic(vbicq_u64);
}
