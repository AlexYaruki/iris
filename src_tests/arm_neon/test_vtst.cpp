#include <iris/iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vtst(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = 1;
        v2.template at<typename T::elementType>(i) = 2;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == 0);
    }
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = 46;
        v2.template at<typename T::elementType>(i) = 47;
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == 1);
    }
}

int main() {
    test_vtst(vtst_u8);
    test_vtst(vtst_u16);
    test_vtst(vtst_u32);

    test_vtst(vtst_s8);
    test_vtst(vtst_s16);
    test_vtst(vtst_s32);

    test_vtst(vtstq_u8);
    test_vtst(vtstq_u16);
    test_vtst(vtstq_u32);

    test_vtst(vtstq_s8);
    test_vtst(vtstq_s16);
    test_vtst(vtstq_s32);
}
