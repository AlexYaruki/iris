#include <iostream>
#include <cstdint>
#include "nexus.h"

using namespace nexus;

int main() {
    auto a = vdup_n_s32(1);
    auto b = vdup_n_s32(2);
    auto c = vmul_s32(vadd_s32(a,b),b);
    for(int i = 0; i < 2; i++) {
        std::cout << "[" << i << "]: " << vget_lane_s32(c,i) << std::endl;
    }
}
