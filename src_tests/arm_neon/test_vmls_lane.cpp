#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmls_lane(T(*func)(T,T,T,int32_t)){
    T v1, v2, v3;
    for(size_t j = 0; j < T::length; j++) {
        for(size_t i = 0; i < T::length; i++) {
            v1.template at<typename T::elementType>(i) = 2*i;
            v2.template at<typename T::elementType>(i) = i + 1;
            v3.template at<typename T::elementType>(i) = T::length - i + 1;
        }
        T result = func(v1,v2,v3,j);
        for(size_t i = 0; i < T::length; i++) {
            assert(result.template at<typename T::elementType>(i) = (i+1) * (T::length - j + 1) - (2*i));
        }
    }
}

int main() {
    test_vmls_lane(vmls_lane_s16);
    test_vmls_lane(vmls_lane_s32);

    test_vmls_lane(vmls_lane_u16);
    test_vmls_lane(vmls_lane_u32);

    test_vmls_lane(vmls_lane_f32);

    test_vmls_lane(vmlsq_lane_s16);
    test_vmls_lane(vmlsq_lane_s32);

    test_vmls_lane(vmlsq_lane_u16);
    test_vmls_lane(vmlsq_lane_u32);

    test_vmls_lane(vmlsq_lane_f32);
}
