#include <iostream>
#include <cstdint>

#define NEXUS_X86_MMX
#define NEXUS_ARM_NEON

#include "nexus.h"

using namespace nexus;

int main() {
    auto a = vdup_n_s32(INT32_MAX - 10);
    auto b = vdup_n_s32(11);
    
    auto c = vaddl_s32(a,b);
    for(int i = 0; i < 2; i++) {
        std::cout << "[" << i << "]: " << vgetq_lane_s64(c,i) << std::endl;
    }
    
    auto x = _mm_set_pi32(1,2);
    
}
