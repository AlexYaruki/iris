#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vst1(void(*func)(typename T::elementType*,T)) {
	typename T::elementType data[T::length];
	T v;
	for (size_t i = 0; i < T::length; i++) {
		v.template at<typename T::elementType>(i) = i;
		data[i] = T::length + i;
	}
	func(data,v);
	for (size_t i = 0; i < T::length; i++) {
		assert(data[i] == static_cast<typename T::elementType>(i));
	}
}

int main() {
	test_vst1<int8x8_t>(vst1_s8);
	test_vst1<int16x4_t>(vst1_s16);
	test_vst1<int32x2_t>(vst1_s32);
	test_vst1<int64x1_t>(vst1_s64);

	test_vst1<uint8x8_t>(vst1_u8);
	test_vst1<uint16x4_t>(vst1_u16);
	test_vst1<uint32x2_t>(vst1_u32);
	test_vst1<uint64x1_t>(vst1_u64);

	test_vst1<float32x2_t>(vst1_f32);

	test_vst1<int8x16_t>(vst1q_s8);
	test_vst1<int16x8_t>(vst1q_s16);
	test_vst1<int32x4_t>(vst1q_s32);
	test_vst1<int64x2_t>(vst1q_s64);

	test_vst1<uint8x16_t>(vst1q_u8);
	test_vst1<uint16x8_t>(vst1q_u16);
	test_vst1<uint32x4_t>(vst1q_u32);
	test_vst1<uint64x2_t>(vst1q_u64);

	test_vst1<float32x4_t>(vst1q_f32);
}
