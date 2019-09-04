#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmla(T(*func)(T,T,T)){
    T v1, v2, v3;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = 2*i;
        v2.template at<typename T::elementType>(i) = i + 1;
        v3.template at<typename T::elementType>(i) = T::length - i + 1;
    }
    T result = func(v1,v2,v3);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) = (i+1) * (T::length - i + 1) + (2*i));
    }

}

int main() {
    test_vmla(vmla_s8);
    test_vmla(vmla_s16);
    test_vmla(vmla_s32);

    test_vmla(vmla_u8);
    test_vmla(vmla_u16);
    test_vmla(vmla_u32);

    test_vmla(vmla_f32);

    test_vmla(vmlaq_s8);
    test_vmla(vmlaq_s16);
    test_vmla(vmlaq_s32);

    test_vmla(vmlaq_u8);
    test_vmla(vmlaq_u16);
    test_vmla(vmlaq_u32);

    test_vmla(vmlaq_f32);
}
