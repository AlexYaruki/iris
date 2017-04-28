#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vhsub(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = -i;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i));
    }
}

int main() {
    test_vhsub(vhsub_s8);
    test_vhsub(vhsub_s16);
    test_vhsub(vhsub_s32);

    test_vhsub(vhsub_u8);
    test_vhsub(vhsub_u16);
    test_vhsub(vhsub_u32);

    test_vhsub(vhsubq_s8);
    test_vhsub(vhsubq_s16);
    test_vhsub(vhsubq_s32);

    test_vhsub(vhsubq_u8);
    test_vhsub(vhsubq_u16);
    test_vhsub(vhsubq_u32);
}
