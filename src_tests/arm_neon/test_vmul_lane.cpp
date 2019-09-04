#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmul_lane(T(*func)(T,T,int32_t)) {
    T v1, v2;
    for(size_t j = 0; j < T::length; j++) {
        for(size_t i = 0; i < T::length; i++) {
            v1.template at<typename T::elementType>(i) = i + 1;
            v2.template at<typename T::elementType>(i) = T::length - i;
        }
        T result = func(v1,v2,j);
        for(size_t i = 0; i < T::length; i++) {
            assert(result.template at<typename T::elementType>(i) = (i + 1) * (T::length - j));
        }
    }
}


int main() {
    test_vmul_lane(vmul_lane_s16);
    test_vmul_lane(vmul_lane_s32);

    test_vmul_lane(vmul_lane_u16);
    test_vmul_lane(vmul_lane_u32);

    test_vmul_lane(vmul_lane_f32);

    test_vmul_lane(vmulq_lane_s16);
    test_vmul_lane(vmulq_lane_s32);

    test_vmul_lane(vmulq_lane_u16);
    test_vmul_lane(vmulq_lane_u32);

    test_vmul_lane(vmulq_lane_f32);
}
