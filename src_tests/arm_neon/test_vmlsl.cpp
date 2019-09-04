#include <iris/iris.h>
#include <cassert>

using namespace iris;

template<typename T, typename R>
void test_vmlsl(R(*func)(T,T,T)){
    T v1, v2, v3;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        v2.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        v3.template at<typename T::elementType>(i) = i;
    }
    R result = func(v1,v2,v3);
    for(size_t i = 0; i < R::length; i++) {
        typename R::elementType x = static_cast<typename R::elementType>(std::numeric_limits<typename T::elementType>::max());
        assert(result.template at<typename R::elementType>(i) = x * (1 + i));
    }

}

int main() {
    test_vmlsl(vmlsl_s8);
    test_vmlsl(vmlsl_s16);
    test_vmlsl(vmlsl_s32);

    test_vmlsl(vmlsl_u8);
    test_vmlsl(vmlsl_u16);
    test_vmlsl(vmlsl_u32);
}
