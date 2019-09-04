#include <iris/iris.h>
#include <cassert>
#include <bitset>

using namespace iris;

template <typename T, typename R>
void test_vcage(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i);
        v2.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(i);
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(i);
        v2.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i+1);
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }

    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = -static_cast<typename T::elementType>(i+1);
        v2.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(i);
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }
}

int main() {
    test_vcage(vcage_f32);
    test_vcage(vcageq_f32);
}
