#include <iris/iris.h>
#include <iostream>
#include <bitset>
#include <cassert>

using namespace iris;

template<typename T, typename R>
void test_vraddhn(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(1) << ((sizeof(typename T::elementType) * 8) / 2 ) ;
        v2.template at<typename T::elementType>(i) = static_cast<typename T::elementType>(1) << ((sizeof(typename T::elementType) * 8) / 2 + 1) ;
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == static_cast<typename R::elementType>(3));
    }
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
        v2.template at<typename T::elementType>(i) = std::numeric_limits<typename R::elementType>::is_signed ? -1 : 0;
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::min());
    }
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        v2.template at<typename T::elementType>(i) = 1;
    }
    result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename R::elementType>(i) == std::numeric_limits<typename R::elementType>::max());
    }
}

int main() {
    test_vraddhn(vraddhn_s16);
    test_vraddhn(vraddhn_s32);
    test_vraddhn(vraddhn_s64);
    test_vraddhn(vraddhn_u16);
    test_vraddhn(vraddhn_u32);
    test_vraddhn(vraddhn_u64);
}
