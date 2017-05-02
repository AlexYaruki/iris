#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vst1_lane(void(*func)(typename T::elementType*,T,int32_t)){
    typename T::elementType x = 47;
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    for(size_t i = 0; i < T::length; i++) {
        func(&x,v,i);
        assert(x == static_cast<typename T::elementType>(i));
        x = 47;
    }
}


int main() {
    test_vst1_lane(vst1_lane_u8);
    test_vst1_lane(vst1_lane_u16);
    test_vst1_lane(vst1_lane_u32);
    test_vst1_lane(vst1_lane_u64);

    test_vst1_lane(vst1_lane_s8);
    test_vst1_lane(vst1_lane_s16);
    test_vst1_lane(vst1_lane_s32);
    test_vst1_lane(vst1_lane_s64);

    test_vst1_lane(vst1_lane_f32);

    test_vst1_lane(vst1q_lane_u8);
    test_vst1_lane(vst1q_lane_u16);
    test_vst1_lane(vst1q_lane_u32);
    test_vst1_lane(vst1q_lane_u64);

    test_vst1_lane(vst1q_lane_s8);
    test_vst1_lane(vst1q_lane_s16);
    test_vst1_lane(vst1q_lane_s32);
    test_vst1_lane(vst1q_lane_s64);

    test_vst1_lane(vst1q_lane_f32);
}
