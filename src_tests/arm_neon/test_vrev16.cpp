#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vrev16(T(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    T result = func(v);
    const size_t packs = (T::length * sizeof(typename T::elementType))/2;
    const size_t elementsPerPack = T::length/packs;
    for(size_t j = 0; j < packs; j++) {
        for(size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j+1) ; i++, k++) {
            assert(result.template at<typename T::elementType>(i) == v.template at<typename T::elementType>((elementsPerPack * (j+1)) - (k + 1)));
        }
    }
}

int main() {
    test_vrev16(vrev16_s8);
    test_vrev16(vrev16_u8);

    test_vrev16(vrev16q_s8);
    test_vrev16(vrev16q_u8);
}
