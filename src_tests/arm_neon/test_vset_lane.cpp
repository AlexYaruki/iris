#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vset_lane(T(*func)(typename T::elementType,T,int32_t)) {
    T data;
    for (size_t i = 0; i < T::length; i++) {
        data = func((typename T::elementType)i,data,i);
    }
    for (size_t i = 0; i < T::length; i++) {
        assert(data.template at<typename T::elementType>(i) == (typename T::elementType)i);
    }
}


int main() {
    test_vset_lane<int8x8_t>(vset_lane_s8);
    test_vset_lane<int16x4_t>(vset_lane_s16);
    test_vset_lane<int32x2_t>(vset_lane_s32);
    test_vset_lane<int64x1_t>(vset_lane_s64);

    test_vset_lane<uint8x8_t>(vset_lane_u8);
    test_vset_lane<uint16x4_t>(vset_lane_u16);
    test_vset_lane<uint32x2_t>(vset_lane_u32);
    test_vset_lane<uint64x1_t>(vset_lane_u64);

    test_vset_lane<float32x2_t>(vset_lane_f32);


    test_vset_lane<int8x16_t>(vsetq_lane_s8);
    test_vset_lane<int16x8_t>(vsetq_lane_s16);
    test_vset_lane<int32x4_t>(vsetq_lane_s32);
    test_vset_lane<int64x2_t>(vsetq_lane_s64);

    test_vset_lane<uint8x16_t>(vsetq_lane_u8);
    test_vset_lane<uint16x8_t>(vsetq_lane_u16);
    test_vset_lane<uint32x4_t>(vsetq_lane_u32);
    test_vset_lane<uint64x2_t>(vsetq_lane_u64);

    test_vset_lane<float32x4_t>(vsetq_lane_f32);
}
