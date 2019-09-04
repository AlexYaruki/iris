#include "common.h"
#include "multiplication_addition.h"
#ifndef IRIS_ARM_FMA
#define IRIS_ARM_FMA

namespace iris::arm::fma
{
// ARM_NEON - vfma - 64-bit vector
const auto &vfma_f32 = vmla_f32;
//

// ARM_NEON - vfma - 128-bit vector
const auto &vfmaq_f32 = vmlaq_f32;
} // namespace iris::arm::fma

using namespace iris::arm::fma;

#endif