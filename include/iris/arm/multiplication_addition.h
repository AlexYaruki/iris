#include "common.h"

#ifndef IRIS_ARM_MULTIPLICATION_ADDITION
#define IRIS_ARM_MULTIPLICATION_ADDITION

namespace iris::arm::multiplication_addition
{

template <typename T>
T __vmla(T v1, T v2, T v3)
{
    return __vadd(v3, __vmul(v1, v2));
}

const auto &vmla_s8 = __vmla<int8x8_t>;
const auto &vmla_s16 = __vmla<int16x4_t>;
const auto &vmla_s32 = __vmla<int32x2_t>;

const auto &vmla_u8 = __vmla<uint8x8_t>;
const auto &vmla_u16 = __vmla<uint16x4_t>;
const auto &vmla_u32 = __vmla<uint32x2_t>;

const auto &vmla_f32 = __vmla<float32x2_t>;

const auto &vmlaq_s8 = __vmla<int8x16_t>;
const auto &vmlaq_s16 = __vmla<int16x8_t>;
const auto &vmlaq_s32 = __vmla<int32x4_t>;

const auto &vmlaq_u8 = __vmla<uint8x16_t>;
const auto &vmlaq_u16 = __vmla<uint16x8_t>;
const auto &vmlaq_u32 = __vmla<uint32x4_t>;

const auto &vmlaq_f32 = __vmla<float32x4_t>;

template <typename T, typename R>
R __vmlal(T v1, T v2, T v3)
{
    R result = __vmull<T, R>(v1, v2);
    return __vaddw(result, v3);
}

const auto &vmlal_s8 = __vmlal<int8x8_t, int16x8_t>;
const auto &vmlal_s16 = __vmlal<int16x4_t, int32x4_t>;
const auto &vmlal_s32 = __vmlal<int32x2_t, int64x2_t>;

const auto &vmlal_u8 = __vmlal<uint8x8_t, uint16x8_t>;
const auto &vmlal_u16 = __vmlal<uint16x4_t, uint32x4_t>;
const auto &vmlal_u32 = __vmlal<uint32x2_t, uint64x2_t>;

template <typename T>
T __vmla_n(T v1, T v2, typename T::elementType x)
{
    auto p = __vdup<T, typename T::elementType>(x);
    return __vadd(v1, __vmul(v2, p));
}

const auto &vmla_n_s16 = __vmla_n<int16x4_t>;
const auto &vmla_n_s32 = __vmla_n<int32x2_t>;

const auto &vmla_n_u16 = __vmla_n<uint16x4_t>;
const auto &vmla_n_u32 = __vmla_n<uint32x2_t>;

const auto &vmla_n_f32 = __vmla_n<float32x2_t>;

const auto &vmlaq_n_s16 = __vmla_n<int16x8_t>;
const auto &vmlaq_n_s32 = __vmla_n<int32x4_t>;

const auto &vmlaq_n_u16 = __vmla_n<uint16x8_t>;
const auto &vmlaq_n_u32 = __vmla_n<uint32x4_t>;

const auto &vmlaq_n_f32 = __vmla_n<float32x4_t>;

template <typename T>
T __vmla_lane(T v1, T v2, T v3, int32_t x)
{
    auto p = __vdup_lane<T, typename T::elementType>(v3, x);
    return __vadd(v1, __vmul(v2, p));
}

const auto &vmla_lane_s16 = __vmla_lane<int16x4_t>;
const auto &vmla_lane_s32 = __vmla_lane<int32x2_t>;

const auto &vmla_lane_u16 = __vmla_lane<uint16x4_t>;
const auto &vmla_lane_u32 = __vmla_lane<uint32x2_t>;

const auto &vmla_lane_f32 = __vmla_lane<float32x2_t>;

const auto &vmlaq_lane_s16 = __vmla_lane<int16x8_t>;
const auto &vmlaq_lane_s32 = __vmla_lane<int32x4_t>;

const auto &vmlaq_lane_u16 = __vmla_lane<uint16x8_t>;
const auto &vmlaq_lane_u32 = __vmla_lane<uint32x4_t>;

const auto &vmlaq_lane_f32 = __vmla_lane<float32x4_t>;

} // namespace iris::arm::multiplication_addition

using namespace iris::arm::multiplication_addition;

#endif