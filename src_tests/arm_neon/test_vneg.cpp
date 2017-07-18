#include <iris.h>
#include <string>
#include <cassert>

using namespace iris;

template <typename T>
void test_vneg(T(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    T result = func(v);
    for(size_t i = 0; i < T::length; i++) {
        typename T::elementType x = v.template at<typename T::elementType>(i) * (typename T::elementType)-1 ;
        typename T::elementType y = result.template at<typename T::elementType>(i);
        std::cout << "Original: " << std::to_string(v.template at<typename T::elementType>(i)) << std::endl;
        std::cout << "X: " << std::to_string(x) << std::endl;
        std::cout << "Y: " << std::to_string(y) << std::endl;
        assert(x == y);
    }
}

int main() {
    test_vneg(vneg_s8);
    test_vneg(vneg_s16);
    test_vneg(vneg_s32);
    test_vneg(vneg_f32);

    test_vneg(vnegq_s8);
    test_vneg(vnegq_s16);
    test_vneg(vnegq_s32);
    test_vneg(vnegq_f32);
}
