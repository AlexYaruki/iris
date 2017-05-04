#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vfms(T(*func)(T,T,T)){
    T v1, v2, v3;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = 2*i;
        v2.template at<typename T::elementType>(i) = i + 1;
        v3.template at<typename T::elementType>(i) = T::length - i + 1;
    }
    T result = func(v1,v2,v3);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) = (i+1) * (T::length - i + 1) - (2*i));
    }

}

int main() {
    test_vfms(vfms_f32);
    test_vfms(vfmsq_f32);
}
