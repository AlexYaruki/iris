#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmls(T(*func)(T,T,T)){
    T v1, v2, v3;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = 2*i;
        v2.template at<typename T::elementType>(i) = i + 1;
        v3.template at<typename T::elementType>(i) = T::length - i + 1;
    }
    T result = func(v1,v2,v3);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) = (i+1) * (T::length - i + 1) - (2*i));
    }

}

int main() {
    test_vmls(vmls_s8);
    test_vmls(vmls_s16);
    test_vmls(vmls_s32);

    test_vmls(vmls_u8);
    test_vmls(vmls_u16);
    test_vmls(vmls_u32);

    test_vmls(vmls_f32);

    test_vmls(vmlsq_s8);
    test_vmls(vmlsq_s16);
    test_vmls(vmlsq_s32);

    test_vmls(vmlsq_u8);
    test_vmls(vmlsq_u16);
    test_vmls(vmlsq_u32);

    test_vmls(vmlsq_f32);
}
