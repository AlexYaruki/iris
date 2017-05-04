#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vld4(T(*func)(const typename T::vectorType::elementType*)) {
	constexpr size_t elementCount = T::lanes * T::vectorType::length;
	typename T::vectorType::elementType data[elementCount];
	for (size_t i = 0; i < elementCount; i++) {
		data[i] = i;
	}
	T output = func(data);
	for (size_t i = 0; i < T::lanes; i++) {
		for(size_t j = 0; j < T::vectorType::length; j++) {
			assert(output.val[i].template at<typename T::vectorType::elementType>(j) == static_cast<typename T::vectorType::elementType>(i + T::lanes * j));
		}
	}
}

int main() {
	test_vld4(vld4_s8);
	test_vld4(vld4_s16);
	test_vld4(vld4_s32);
	test_vld4(vld4_s64);

	test_vld4(vld4_u8);
	test_vld4(vld4_u16);
	test_vld4(vld4_u32);
	test_vld4(vld4_u64);

	test_vld4(vld4_f32);

	test_vld4(vld4q_s8);
	test_vld4(vld4q_s16);
	test_vld4(vld4q_s32);
	test_vld4(vld4q_s64);

	test_vld4(vld4q_u8);
	test_vld4(vld4q_u16);
	test_vld4(vld4q_u32);
	test_vld4(vld4q_u64);

	test_vld4(vld4q_f32);
}
