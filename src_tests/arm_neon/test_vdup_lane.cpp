#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vdup_lane(T(*func)(T,int32_t)) {
	T data;
	for (size_t i = 0; i < T::length; i++) {
		data.template at<typename T::elementType>(i) = (typename T::elementType) i;
	}
	for (size_t i = 0; i < T::length; i++) {
		T output = func(data, i);
		for (size_t j = 0; j < T::length; j++) {
			assert(output.template at<typename T::elementType>(j) == (typename T::elementType) i);
		}
	}
}


int main() {
	test_vdup_lane(vdup_lane_s8);
	test_vdup_lane(vdup_lane_s16);
	test_vdup_lane(vdup_lane_s32);
	test_vdup_lane(vdup_lane_s64);

	test_vdup_lane(vdup_lane_u8);
	test_vdup_lane(vdup_lane_u16);
	test_vdup_lane(vdup_lane_u32);
	test_vdup_lane(vdup_lane_u64);

	test_vdup_lane(vdup_lane_f32);


	test_vdup_lane(vdupq_lane_s8);
	test_vdup_lane(vdupq_lane_s16);
	test_vdup_lane(vdupq_lane_s32);
	test_vdup_lane(vdupq_lane_s64);

	test_vdup_lane(vdupq_lane_u8);
	test_vdup_lane(vdupq_lane_u16);
	test_vdup_lane(vdupq_lane_u32);
	test_vdup_lane(vdupq_lane_u64);

	test_vdup_lane(vdupq_lane_f32);
}
