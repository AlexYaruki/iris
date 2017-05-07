#include <iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vcalt(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i);
        v2.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(i);
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(i);
        v2.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i+1);
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i+1);
        v2.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(i);
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }
}

int main() {
    test_vcalt(vcalt_f32);
    test_vcalt(vcaltq_f32);
}
