#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vld1_lane(T(*func)(typename T::elementType*,T,int32_t)){
    typename T::elementType x = 47;
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    for(size_t i = 0; i < T::length; i++) {
        T result = func(&x,v,i);
        for(size_t j = 0; j < T::length; j++) {
            if(i == j) {
                assert(result.template at<typename T::elementType>(i) == x);
            } else {
                assert(result.template at<typename T::elementType>(j) == v.template at<typename T::elementType>(j));
            }
        }
    }
}


int main() {
    test_vld1_lane(vld1_lane_u8);
    test_vld1_lane(vld1_lane_u16);
    test_vld1_lane(vld1_lane_u32);
    test_vld1_lane(vld1_lane_u64);

    test_vld1_lane(vld1_lane_s8);
    test_vld1_lane(vld1_lane_s16);
    test_vld1_lane(vld1_lane_s32);
    test_vld1_lane(vld1_lane_s64);

    test_vld1_lane(vld1_lane_f32);

    test_vld1_lane(vld1q_lane_u8);
    test_vld1_lane(vld1q_lane_u16);
    test_vld1_lane(vld1q_lane_u32);
    test_vld1_lane(vld1q_lane_u64);

    test_vld1_lane(vld1q_lane_s8);
    test_vld1_lane(vld1q_lane_s16);
    test_vld1_lane(vld1q_lane_s32);
    test_vld1_lane(vld1q_lane_s64);

    test_vld1_lane(vld1q_lane_f32);
}
