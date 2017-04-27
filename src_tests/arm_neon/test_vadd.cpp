#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vadd(T(*func)(T,T)) {
    T v1, v2;
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    T result = func(v1,v2);
    for(int i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == 2*i+1);
    }
}


int main() {
    test_vadd(vadd_s8);
    test_vadd(vadd_s16);
    test_vadd(vadd_s32);
    test_vadd(vadd_s64);
    
    test_vadd(vadd_u8);
    test_vadd(vadd_u16);
    test_vadd(vadd_u32);
    test_vadd(vadd_u64);
    
    test_vadd(vadd_f32);
    
    test_vadd(vaddq_s8);
    test_vadd(vaddq_s16);
    test_vadd(vaddq_s32);
    test_vadd(vaddq_s64);
    
    test_vadd(vaddq_u8);
    test_vadd(vaddq_u16);
    test_vadd(vaddq_u32);
    test_vadd(vaddq_u64);
    
    test_vadd(vaddq_f32);
}
