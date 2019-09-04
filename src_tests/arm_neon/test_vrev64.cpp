#include <iris/iris.h>
#include <cassert>

using namespace iris;

template <typename T>
void test_vrev64(T(*func)(T)) {
    T v;
    for(size_t i = 0; i < T::length; i++) {
        v.template at<typename T::elementType>(i) = i;
    }
    T result = func(v);
    const size_t packs = (T::length * sizeof(typename T::elementType))/8;
    const size_t elementsPerPack = T::length/packs;
    for(size_t j = 0; j < packs; j++) {
        for(size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j+1) ; i++, k++) {
            assert(result.template at<typename T::elementType>(i) == v.template at<typename T::elementType>((elementsPerPack * (j+1)) - (k + 1)));
        }
    }
}

int main() {
    test_vrev64(vrev64_s8);
    test_vrev64(vrev64_s16);
    test_vrev64(vrev64_s32);

    test_vrev64(vrev64_u8);
    test_vrev64(vrev64_u16);
    test_vrev64(vrev64_u32);

    test_vrev64(vrev64_f32);

    test_vrev64(vrev64q_s8);
    test_vrev64(vrev64q_s16);
    test_vrev64(vrev64q_s32);

    test_vrev64(vrev64q_u8);
    test_vrev64(vrev64q_u16);
    test_vrev64(vrev64q_u32);

    test_vrev64(vrev64q_f32);
}
