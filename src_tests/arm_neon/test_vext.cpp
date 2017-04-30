#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vext(T(*func)(T,T,int32_t)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + T::length;
    }
    for(size_t i = 0; i < T::length; i++) {
        T result = func(v1,v2,i);
        for(size_t j = 0; j < T::length; j++) {
            if(j < i + 1) {
                assert(result.template at<typename T::elementType>(j) == v2.template at<typename T::elementType>(j));
            } else {
                assert(result.template at<typename T::elementType>(j) == v1.template at<typename T::elementType>(T::length - (j - i)));
            }
        }
    }
}

int main() {
    test_vext(vext_s8);
    test_vext(vext_s16);
    test_vext(vext_s32);
    test_vext(vext_s64);

    test_vext(vext_u8);
    test_vext(vext_u16);
    test_vext(vext_u32);
    test_vext(vext_u64);

    test_vext(vextq_s8);
    test_vext(vextq_s16);
    test_vext(vextq_s32);
    test_vext(vextq_s64);

    test_vext(vextq_u8);
    test_vext(vextq_u16);
    test_vext(vextq_u32);
    test_vext(vextq_u64);
}
