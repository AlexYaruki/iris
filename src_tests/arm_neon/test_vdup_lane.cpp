#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vdup_lane(T(*func)(T,size_t)) {
	T data;
	for (int i = 0; i < T::length; i++) {
		data.template at<typename T::elementType>(i) = (typename T::elementType) i;
	}
	for (int i = 0; i < T::length; i++) {
		T output = func(data, i);
		for (size_t j = 0; j < T::length; j++) {
			assert(output.template at<typename T::elementType>(j) == (typename T::elementType) i);
		}
	}
}


int main() {
	test_vdup_lane<int8x8_t>(vdup_lane_s8);
	test_vdup_lane<int16x4_t>(vdup_lane_s16);
	test_vdup_lane<int32x2_t>(vdup_lane_s32);
	test_vdup_lane<int64x1_t>(vdup_lane_s64);

	test_vdup_lane<uint8x8_t>(vdup_lane_u8);
	test_vdup_lane<uint16x4_t>(vdup_lane_u16);
	test_vdup_lane<uint32x2_t>(vdup_lane_u32);
	test_vdup_lane<uint64x1_t>(vdup_lane_u64);

	test_vdup_lane<float32x2_t>(vdup_lane_f32);


	test_vdup_lane<int8x16_t>(vdupq_lane_s8);
	test_vdup_lane<int16x8_t>(vdupq_lane_s16);
	test_vdup_lane<int32x4_t>(vdupq_lane_s32);
	test_vdup_lane<int64x2_t>(vdupq_lane_s64);

	test_vdup_lane<uint8x16_t>(vdupq_lane_u8);
	test_vdup_lane<uint16x8_t>(vdupq_lane_u16);
	test_vdup_lane<uint32x4_t>(vdupq_lane_u32);
	test_vdup_lane<uint64x2_t>(vdupq_lane_u64);

	test_vdup_lane<float32x4_t>(vdupq_lane_f32);
}
