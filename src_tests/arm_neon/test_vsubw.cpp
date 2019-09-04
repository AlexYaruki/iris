#include <cassert>
#include <iris/iris.h>
using namespace iris;

template<typename R, typename T>
void test_vsubw(R(*func)(R,T)) {
    R v1;
    T v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename R::elementType>(i) = i + 1;
        v2.template at<typename T::elementType>(i) = i;
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < R::length; i++) {
        assert(result.template at<typename R::elementType>(i) == 1);
    }
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename R::elementType>(i) = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max());
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
    test_vsubw(vsubw_s8);
    test_vsubw(vsubw_s16);
    test_vsubw(vsubw_s32);
    test_vsubw(vsubw_u8);
    test_vsubw(vsubw_u16);
    test_vsubw(vsubw_u32);
}
