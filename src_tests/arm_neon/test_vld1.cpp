#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vld1(T(*func)(typename T::elementType*)) {
	typename T::elementType data[T::length];
	for (int i = 0; i < T::length; i++) {
		data[i] = i;
	}
	T output = func(data);
	for (int i = 0; i < T::length; i++) {
		bool cmp = output.template at<typename T::elementType>(i) == data[i];
		assert(cmp);
	}
}

int main() {
	test_vld1<int8x8_t>(vld1_s8);
	test_vld1<int16x4_t>(vld1_s16);
	test_vld1<int32x2_t>(vld1_s32);
	test_vld1<int64x1_t>(vld1_s64);

	test_vld1<uint8x8_t>(vld1_u8);
	test_vld1<uint16x4_t>(vld1_u16);
	test_vld1<uint32x2_t>(vld1_u32);
	test_vld1<uint64x1_t>(vld1_u64);

	test_vld1<float32x2_t>(vld1_f32);

	test_vld1<int8x16_t>(vld1q_s8);
	test_vld1<int16x8_t>(vld1q_s16);
	test_vld1<int32x4_t>(vld1q_s32);
	test_vld1<int64x2_t>(vld1q_s64);

	test_vld1<uint8x16_t>(vld1q_u8);
	test_vld1<uint16x8_t>(vld1q_u16);
	test_vld1<uint32x4_t>(vld1q_u32);
	test_vld1<uint64x2_t>(vld1q_u64);

	test_vld1<float32x4_t>(vld1q_f32);
}
