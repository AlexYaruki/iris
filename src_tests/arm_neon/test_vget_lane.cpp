#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vget_lane(typename T::elementType(*func)(T,size_t)) {
	T data;
	for (size_t i = 0; i < T::length; i++) {
		data.template at<typename T::elementType>(i) = i;
	}
	for (size_t i = 0; i < T::length; i++) {
		typename T::elementType output = func(data,i);
		assert(output == (typename T::elementType)i);
	}
}

int main() {
	test_vget_lane<int8x8_t>(vget_lane_s8);
	test_vget_lane<int16x4_t>(vget_lane_s16);
	test_vget_lane<int32x2_t>(vget_lane_s32);
	test_vget_lane<int64x1_t>(vget_lane_s64);

	test_vget_lane<uint8x8_t>(vget_lane_u8);
	test_vget_lane<uint16x4_t>(vget_lane_u16);
	test_vget_lane<uint32x2_t>(vget_lane_u32);
	test_vget_lane<uint64x1_t>(vget_lane_u64);

	test_vget_lane<float32x2_t>(vget_lane_f32);


	test_vget_lane<int8x16_t>(vgetq_lane_s8);
	test_vget_lane<int16x8_t>(vgetq_lane_s16);
	test_vget_lane<int32x4_t>(vgetq_lane_s32);
	test_vget_lane<int64x2_t>(vgetq_lane_s64);

	test_vget_lane<uint8x16_t>(vgetq_lane_u8);
	test_vget_lane<uint16x8_t>(vgetq_lane_u16);
	test_vget_lane<uint32x4_t>(vgetq_lane_u32);
	test_vget_lane<uint64x2_t>(vgetq_lane_u64);

	test_vget_lane<float32x4_t>(vgetq_lane_f32);
}
