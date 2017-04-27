#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vhadd(T(*func)(T,T)) {
    T v1, v2;
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i;
    }
    T result = func(v1,v2);
    for(int i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == i);
    }
}

int main() {
    test_vhadd(vhadd_s8);
    test_vhadd(vhadd_s16);
    test_vhadd(vhadd_s32);

    test_vhadd(vhadd_u8);
    test_vhadd(vhadd_u16);
    test_vhadd(vhadd_u32);

    test_vhadd(vhaddq_s8);
    test_vhadd(vhaddq_s16);
    test_vhadd(vhaddq_s32);

    test_vhadd(vhaddq_u8);
    test_vhadd(vhaddq_u16);
    test_vhadd(vhaddq_u32);
}
