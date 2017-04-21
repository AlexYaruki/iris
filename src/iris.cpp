#include <iostream>
#include <cstdint>

#define IRIS_X86_MMX
#define IRIS_ARM_NEON
#define IRIS_ARM_NEON_EXPANSION
#include "iris.h"

using namespace iris;

int main() {
    auto x = _mm_set1_pi8(3);
    auto y = _mm_set1_pi8(6);
    __m64 z = __mm_sad_pu8(x,y);
    std::cout << z.at<int16_t>(0) << std::endl;
}
