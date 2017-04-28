#include <cassert>

#include <numeric>
#include <iostream>

#include <iris.h>
using namespace iris;

template<typename T, typename R>
void test_vsubl(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    R result = func(v2,v1);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == 1);
    }
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        if(std::is_signed<typename T::elementType>::value) {
            v2.template at<typename T::elementType>(i) = -i;
        } else {
            v2.template at<typename T::elementType>(i) = i;
        }
    }
    result = func(v1,v2);
    for(size_t i = 0; i < R::length; i++) {
        typename R::elementType value;
        if(std::is_signed<typename T::elementType>::value) {
            value = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max()) + i;
        } else {
            value = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max()) - i;
        }
        assert(result.template at<typename R::elementType>(i) ==  value);
    }

}

int main() {
    test_vsubl(vsubl_s8);
    test_vsubl(vsubl_s16);
    test_vsubl(vsubl_s32);
    test_vsubl(vsubl_u8);
    test_vsubl(vsubl_u16);
    test_vsubl(vsubl_u32);
}
