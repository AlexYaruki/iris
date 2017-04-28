#include <iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vabs(T(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    T result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i));
    }

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
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i));
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
