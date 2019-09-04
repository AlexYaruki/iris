#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vabs(T(*func)(T)) {
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
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i));
    }

    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
    }
    result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        if(std::numeric_limits<typename T::elementType>::is_signed) {
            assert(result.template at<typename T::elementType>(i) == std::numeric_limits<typename T::elementType>::min());
        } else {
            assert(result.template at<typename T::elementType>(i) == -1);
        }
    }
}

int main() {
    test_vabs(vabs_s8);
    test_vabs(vabs_s16);
    test_vabs(vabs_s32);

    test_vabs(vabs_f32);

    test_vabs(vabsq_s8);
    test_vabs(vabsq_s16);
    test_vabs(vabsq_s32);

    test_vabs(vabsq_f32);
}
