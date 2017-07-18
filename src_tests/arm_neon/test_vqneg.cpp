#include <iris.h>
#include <string>
#include <cassert>
#include <limits>

using namespace iris;

template <typename T>
void test_vqneg(T(*func)(T)) {
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
    for(size_t i = std::numeric_limits<typename T::elementType>::min(), x = 0; x < T::length; i++, x++) {
        v.template at<typename T::elementType>(x) = i;
    }
    result = func(v);
    typename T::elementType p = result.template at<typename T::elementType>(0);
    std::cout << "Original: " << std::to_string(v.template at<typename T::elementType>(0)) << std::endl;
    std::cout << "P: " << std::to_string(p) << std::endl;
    assert(p == -std::numeric_limits<typename T::elementType>::max());
    for(size_t i = 1; i < T::length; i++) {
        typename T::elementType x = v.template at<typename T::elementType>(i) * (typename T::elementType)-1 ;
        typename T::elementType y = result.template at<typename T::elementType>(i);
        std::cout << "Original: " << std::to_string(v.template at<typename T::elementType>(i)) << std::endl;
        std::cout << "X: " << std::to_string(x) << std::endl;
        std::cout << "Y: " << std::to_string(y) << std::endl;
        assert(x == y);
    }
}

int main() {
    test_vqneg(vqneg_s8);
    test_vqneg(vqneg_s16);
    test_vqneg(vqneg_s32);

    test_vqneg(vqnegq_s8);
    test_vqneg(vqnegq_s16);
    test_vqneg(vqnegq_s32);
}
