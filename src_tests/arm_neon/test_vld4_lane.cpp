#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vld4_lane(T(*func)(typename T::vectorType::elementType*,T,int32_t)){
    typename T::vectorType::elementType data[T::lanes];
    for(size_t i = 0; i < T::lanes; i++) {
        data[i] = static_cast<typename T::vectorType::elementType>(100 + i);
    }
    T v;
    for(size_t i = 0; i < T::lanes; i++) {
        for(size_t j = 0; j < T::vectorType::length; j++) {
            v.val[i].template at<typename T::vectorType::elementType>(j) = static_cast<typename T::vectorType::elementType>(i * T::vectorType::length + j);
        }
    }
    for(size_t i = 0; i < T::vectorType::length; i++) {
        T result = func(data,v,i);
        for(size_t k = 0; k < T::lanes; k++) {
            for(size_t j = 0; j < T::vectorType::length; j++) {
                if(i == j) {
                    assert(result.val[k].template at<typename T::vectorType::elementType>(j) == data[k]);
                } else {
                    assert(result.val[k].template at<typename T::vectorType::elementType>(j) == v.val[k].template at<typename T::vectorType::elementType>(j));
                }
            }
        }
    }
}


int main() {
    test_vld4_lane(vld4_lane_u8);
    test_vld4_lane(vld4_lane_u16);
    test_vld4_lane(vld4_lane_u32);

    test_vld4_lane(vld4_lane_s8);
    test_vld4_lane(vld4_lane_s16);
    test_vld4_lane(vld4_lane_s32);

    test_vld4_lane(vld4_lane_f32);

    test_vld4_lane(vld4q_lane_u8);
    test_vld4_lane(vld4q_lane_u16);
    test_vld4_lane(vld4q_lane_u32);

    test_vld4_lane(vld4q_lane_s8);
    test_vld4_lane(vld4q_lane_s16);
    test_vld4_lane(vld4q_lane_s32);

    test_vld4_lane(vld4q_lane_f32);
}
