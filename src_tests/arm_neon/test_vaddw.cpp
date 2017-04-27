#include <cassert>
#include <iris.h>
using namespace iris;

template<typename R, typename T>
void test_vaddw(R(*func)(R,T)) {
    R v1;
    T v2;
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename R::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    R result = func(v1,v2);
    for(int i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == 2*i + 1);
    }
    for(int i = 0; i < T::length; i++) {
        v1.template at<typename R::elementType>(i) = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max());
        if(std::is_signed<typename T::elementType>::value) {
            v2.template at<typename T::elementType>(i) = i - 1;
        } else {
            v2.template at<typename T::elementType>(i) = i;
        }
    }
    result = func(v1,v2);
    for(int i = 0; i < R::length; i++) {
        typename R::elementType value;
        if(std::is_signed<typename T::elementType>::value) {
            value = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max()) + i - 1;
        } else {
            value = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max()) + i;
        }
        assert(result.template at<typename R::elementType>(i) ==  value);
    }
}

int main() {
    test_vaddw(vaddw_s8);
    test_vaddw(vaddw_s16);
    test_vaddw(vaddw_s32);
    test_vaddw(vaddw_u8);
    test_vaddw(vaddw_u16);
    test_vaddw(vaddw_u32);
}
