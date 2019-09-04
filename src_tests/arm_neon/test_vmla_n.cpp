#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmla_n(T(*func)(T,T,typename T::elementType)){
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = 2*i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    T result = func(v1,v2,3);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) = (i+1) * static_cast<typename T::elementType>(3) + (2*i));
    }
}

int main() {
    test_vmla_n(vmla_n_s16);
    test_vmla_n(vmla_n_s32);

    test_vmla_n(vmla_n_u16);
    test_vmla_n(vmla_n_u32);

    test_vmla_n(vmla_n_f32);

    test_vmla_n(vmlaq_n_s16);
    test_vmla_n(vmlaq_n_s32);

    test_vmla_n(vmlaq_n_u16);
    test_vmla_n(vmlaq_n_u32);

    test_vmla_n(vmlaq_n_f32);
}
