#include <iostream>
#include <cstdint>
#include "nexus.h"

using namespace nexus;

int main() {
    auto a = vdup_n_s32(INT32_MAX - 10);
    auto b = vdup_n_s32(11);
    auto c = vaddl_s32(a,b);
    for(int i = 0; i < 2; i++) {
        std::cout << "[" << i << "]: " << vgetq_lane_s64(c,i) << std::endl;
    }
}
