#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vqabs(T(*func)(T)) {
    T v, result;

    // All positive
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i));
    }

    // All negative
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i);
    }
    result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        typename T::elementType x = result.template at<typename T::elementType>(i);
        if(std::numeric_limits<typename T::elementType>::is_integer) {
            std::cout << i << ": " << (int64_t)x << std::endl;
        } else {
            std::cout << i << ": " << x << std::endl;
        }
        assert(x == static_cast<typename T::elementType>(i));
    }

    // Overflow
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::lowest();
    }
    result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == std::numeric_limits<typename T::elementType>::max());
    }
}

int main() {
    test_vqabs(vqabs_s8);
    test_vqabs(vqabs_s16);
    test_vqabs(vqabs_s32);

    test_vqabs(vqabs_f32);

    test_vqabs(vqabsq_s8);
    test_vqabs(vqabsq_s16);
    test_vqabs(vqabsq_s32);

    test_vqabs(vqabsq_f32);
}
