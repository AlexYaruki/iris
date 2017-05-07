#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T, typename R>
void test_vmull(R(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        v2.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
    }
    R result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        const typename R::elementType max = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max());
        assert(result.template at<typename R::elementType>(i) = max * max);
    }
}


int main() {
    test_vmull(vmull_s8);
    test_vmull(vmull_s16);
    test_vmull(vmull_s32);

    test_vmull(vmull_u8);
    test_vmull(vmull_u16);
    test_vmull(vmull_u32);
}
