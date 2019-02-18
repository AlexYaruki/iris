#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vld1(T(*func)(const typename T::elementType*)) {
	typename T::elementType data[T::length];
	for (size_t i = 0; i < T::length; i++) {
		data[i] = i;
	}
	T output = func(data);
	for (size_t i = 0; i < T::length; i++) {
		bool cmp = output.template at<typename T::elementType>(i) == 0;
		assert(cmp);
	}
}

int main() {
	test_vld1(vld1_s8);
	test_vld1(vld1_s16);
	test_vld1(vld1_s32);
	test_vld1(vld1_s64);

	test_vld1(vld1_u8);
	test_vld1(vld1_u16);
	test_vld1(vld1_u32);
	test_vld1(vld1_u64);

	test_vld1(vld1_f32);

	test_vld1(vld1q_s8);
	test_vld1(vld1q_s16);
	test_vld1(vld1q_s32);
	test_vld1(vld1q_s64);

	test_vld1(vld1q_u8);
	test_vld1(vld1q_u16);
	test_vld1(vld1q_u32);
	test_vld1(vld1q_u64);

	test_vld1(vld1q_f32);
}
