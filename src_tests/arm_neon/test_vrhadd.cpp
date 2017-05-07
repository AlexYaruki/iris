#include <iris.h>
#include <cassert>

using namespace iris;

template<typename T>
void test_vrhadd(T(*func)(T,T)) {
    T v1, v2;
    for(size_t i = 0; i < T::length; i++) {
        v1.template at<typename T::elementType>(i) = i;
        v2.template at<typename T::elementType>(i) = i + 1;
    }
    T result = func(v1,v2);
    for(size_t i = 0; i < T::length; i++) {
        assert(result.template at<typename T::elementType>(i) == static_cast<typename T::elementType>(i+1));
    }
}

int main() {
    test_vrhadd(vrhadd_s8);
    test_vrhadd(vrhadd_s16);
    test_vrhadd(vrhadd_s32);

    test_vrhadd(vrhadd_u8);
    test_vrhadd(vrhadd_u16);
    test_vrhadd(vrhadd_u32);

    test_vrhadd(vrhaddq_s8);
    test_vrhadd(vrhaddq_s16);
    test_vrhadd(vrhaddq_s32);

    test_vrhadd(vrhaddq_u8);
    test_vrhadd(vrhaddq_u16);
    test_vrhadd(vrhaddq_u32);
}
