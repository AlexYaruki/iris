#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_veor(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + T::length;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == (v1.template at<typename T::elementType>(i) ^ v2.template at<typename T::elementType>(i)));
    }
}

int main() {
    test_veor(veor_s8);
    test_veor(veor_s16);
    test_veor(veor_s32);
    test_veor(veor_s64);

    test_veor(veor_u8);
    test_veor(veor_u16);
    test_veor(veor_u32);
    test_veor(veor_u64);

    test_veor(veorq_s8);
    test_veor(veorq_s16);
    test_veor(veorq_s32);
    test_veor(veorq_s64);

    test_veor(veorq_u8);
    test_veor(veorq_u16);
    test_veor(veorq_u32);
    test_veor(veorq_u64);
}
