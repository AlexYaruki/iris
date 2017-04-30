#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vorr(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + T::length;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == (v1.template at<typename T::elementType>(i) | v2.template at<typename T::elementType>(i)));
    }
}

int main() {
    test_vorr(vorr_s8);
    test_vorr(vorr_s16);
    test_vorr(vorr_s32);
    test_vorr(vorr_s64);

    test_vorr(vorr_u8);
    test_vorr(vorr_u16);
    test_vorr(vorr_u32);
    test_vorr(vorr_u64);

    test_vorr(vorrq_s8);
    test_vorr(vorrq_s16);
    test_vorr(vorrq_s32);
    test_vorr(vorrq_s64);

    test_vorr(vorrq_u8);
    test_vorr(vorrq_u16);
    test_vorr(vorrq_u32);
    test_vorr(vorrq_u64);
}
