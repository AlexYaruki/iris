#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vdup_n(T(*func)(typename T::elementType)) {
	T output = func((typename T::elementType)47);
	for (size_t i = 0; i < T::length; i++) {
		bool cmp = output.template at<typename T::elementType>(i) == (typename T::elementType)47;
		assert(cmp);
	}
}

int main() {
	test_vdup_n<int8x8_t>(vdup_n_s8);
	test_vdup_n<int16x4_t>(vdup_n_s16);
	test_vdup_n<int32x2_t>(vdup_n_s32);
	test_vdup_n<int64x1_t>(vdup_n_s64);

	test_vdup_n<uint8x8_t>(vdup_n_u8);
	test_vdup_n<uint16x4_t>(vdup_n_u16);
	test_vdup_n<uint32x2_t>(vdup_n_u32);
	test_vdup_n<uint64x1_t>(vdup_n_u64);

	test_vdup_n<float32x2_t>(vdup_n_f32);

	test_vdup_n<int8x16_t>(vdupq_n_s8);
	test_vdup_n<int16x8_t>(vdupq_n_s16);
	test_vdup_n<int32x4_t>(vdupq_n_s32);
	test_vdup_n<int64x2_t>(vdupq_n_s64);

	test_vdup_n<uint8x16_t>(vdupq_n_u8);
	test_vdup_n<uint16x8_t>(vdupq_n_u16);
	test_vdup_n<uint32x4_t>(vdupq_n_u32);
	test_vdup_n<uint64x2_t>(vdupq_n_u64);

	test_vdup_n<float32x4_t>(vdupq_n_f32);
}
