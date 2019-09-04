#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vorn(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + T::length;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        typename T::elementType x = ~(v1.template at<typename T::elementType>(i) | v2.template at<typename T::elementType>(i));
        typename T::elementType y = result.template at<typename T::elementType>(i);
        assert(x == y);
    }
}

int main() {
    test_vorn(vorn_s8);
    test_vorn(vorn_s16);
    test_vorn(vorn_s32);
    test_vorn(vorn_s64);

    test_vorn(vorn_u8);
    test_vorn(vorn_u16);
    test_vorn(vorn_u32);
    test_vorn(vorn_u64);

    test_vorn(vornq_s8);
    test_vorn(vornq_s16);
    test_vorn(vornq_s32);
    test_vorn(vornq_s64);

    test_vorn(vornq_u8);
    test_vorn(vornq_u16);
    test_vorn(vornq_u32);
    test_vorn(vornq_u64);
}
