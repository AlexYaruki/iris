#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vmov_n(T(*func)(typename T::elementType)) {
	T output = func((typename T::elementType)47);
	for (size_t i = 0; i < T::length; i++) {
		bool cmp = output.template at<typename T::elementType>(i) == (typename T::elementType)47;
		assert(cmp);
	}
}

int main() {
	test_vmov_n<int8x8_t>(vmov_n_s8);
	test_vmov_n<int16x4_t>(vmov_n_s16);
	test_vmov_n<int32x2_t>(vmov_n_s32);
	test_vmov_n<int64x1_t>(vmov_n_s64);

	test_vmov_n<uint8x8_t>(vmov_n_u8);
	test_vmov_n<uint16x4_t>(vmov_n_u16);
	test_vmov_n<uint32x2_t>(vmov_n_u32);
	test_vmov_n<uint64x1_t>(vmov_n_u64);

	test_vmov_n<float32x2_t>(vmov_n_f32);

	test_vmov_n<int8x16_t>(vmovq_n_s8);
	test_vmov_n<int16x8_t>(vmovq_n_s16);
	test_vmov_n<int32x4_t>(vmovq_n_s32);
	test_vmov_n<int64x2_t>(vmovq_n_s64);

	test_vmov_n<uint8x16_t>(vmovq_n_u8);
	test_vmov_n<uint16x8_t>(vmovq_n_u16);
	test_vmov_n<uint32x4_t>(vmovq_n_u32);
	test_vmov_n<uint64x2_t>(vmovq_n_u64);

	test_vmov_n<float32x4_t>(vmovq_n_f32);
}
