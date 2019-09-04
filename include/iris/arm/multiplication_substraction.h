#include "common.h"

#ifndef IRIS_ARM_MULTIPLICATION_SUBSTRACTION
#define IRIS_ARM_MULTIPLICATION_SUBSTRACTION

namespace iris::arm::multiplication_substraction
{

template <typename T>
T __vmls(T v1, T v2, T v3)
{
    return __vsub(v3, __vmul(v1, v2));
}

template <typename T>
T __vmls_n(T v1, T v2, typename T::elementType x)
{
    auto p = __vdup<T, typename T::elementType>(x);
    return __vsub(v1, __vmul(v2, p));
}

template <typename T>
T __vmls_lane(T v1, T v2, T v3, int32_t x)
{
    auto p = __vdup_lane<T, typename T::elementType>(v3, x);
    return __vsub(v1, __vmul(v2, p));
}

template <typename T, typename R>
R __vmlsl(T v1, T v2, T v3)
{
    R result = __vmull<T, R>(v1, v2);
    return __vsubw(result, v3);
}

const auto &vmls_s8 = __vmls<int8x8_t>;
const auto &vmls_s16 = __vmls<int16x4_t>;
const auto &vmls_s32 = __vmls<int32x2_t>;

const auto &vmls_u8 = __vmls<uint8x8_t>;
const auto &vmls_u16 = __vmls<uint16x4_t>;
const auto &vmls_u32 = __vmls<uint32x2_t>;

const auto &vmls_f32 = __vmls<float32x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vmls - 128-bit vector ///////////////////////////////////////////////////////
const auto &vmlsq_s8 = __vmls<int8x16_t>;
const auto &vmlsq_s16 = __vmls<int16x8_t>;
const auto &vmlsq_s32 = __vmls<int32x4_t>;

const auto &vmlsq_u8 = __vmls<uint8x16_t>;
const auto &vmlsq_u16 = __vmls<uint16x8_t>;
const auto &vmlsq_u32 = __vmls<uint32x4_t>;

const auto &vmlsq_f32 = __vmls<float32x4_t>;
///////////////////////////////////////////////////////////////////////////

// ARM_NEON - vfma - 64-bit vector
const auto &vfms_f32 = vmls_f32;
//

// ARM_NEON - vfma - 128-bit vector
const auto &vfmsq_f32 = vmlsq_f32;
//

// ARM NEON - vmlsl ///////////////////////////////////////////////////////
const auto &vmlsl_s8 = __vmlsl<int8x8_t, int16x8_t>;
const auto &vmlsl_s16 = __vmlsl<int16x4_t, int32x4_t>;
const auto &vmlsl_s32 = __vmlsl<int32x2_t, int64x2_t>;

const auto &vmlsl_u8 = __vmlsl<uint8x8_t, uint16x8_t>;
const auto &vmlsl_u16 = __vmlsl<uint16x4_t, uint32x4_t>;
const auto &vmlsl_u32 = __vmlsl<uint32x2_t, uint64x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vmls_lane - 64-bit vector ///////////////////////////////////////////////////////
const auto &vmls_lane_s16 = __vmls_lane<int16x4_t>;
const auto &vmls_lane_s32 = __vmls_lane<int32x2_t>;

const auto &vmls_lane_u16 = __vmls_lane<uint16x4_t>;
const auto &vmls_lane_u32 = __vmls_lane<uint32x2_t>;

const auto &vmls_lane_f32 = __vmls_lane<float32x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vmls_lane - 128-bit vector ///////////////////////////////////////////////////////
const auto &vmlsq_lane_s16 = __vmls_lane<int16x8_t>;
const auto &vmlsq_lane_s32 = __vmls_lane<int32x4_t>;

const auto &vmlsq_lane_u16 = __vmls_lane<uint16x8_t>;
const auto &vmlsq_lane_u32 = __vmls_lane<uint32x4_t>;

const auto &vmlsq_lane_f32 = __vmls_lane<float32x4_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vmls_n - 64-bit vector ///////////////////////////////////////////////////////
const auto &vmls_n_s16 = __vmls_n<int16x4_t>;
const auto &vmls_n_s32 = __vmls_n<int32x2_t>;

const auto &vmls_n_u16 = __vmls_n<uint16x4_t>;
const auto &vmls_n_u32 = __vmls_n<uint32x2_t>;

const auto &vmls_n_f32 = __vmls_n<float32x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vmls_n - 128-bit vector ///////////////////////////////////////////////////////
const auto &vmlsq_n_s16 = __vmls_n<int16x8_t>;
const auto &vmlsq_n_s32 = __vmls_n<int32x4_t>;

const auto &vmlsq_n_u16 = __vmls_n<uint16x8_t>;
const auto &vmlsq_n_u32 = __vmls_n<uint32x4_t>;

const auto &vmlsq_n_f32 = __vmls_n<float32x4_t>;

} // namespace iris::arm::multiplication_substraction

using namespace iris::arm::multiplication_substraction;

#endif