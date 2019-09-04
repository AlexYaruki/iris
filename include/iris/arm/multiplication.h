#include "common.h"
#ifndef IRIS_ARM_MULTIPLICATION
#define IRIS_ARM_MULTIPLICATION

namespace iris::arm::multiplication {

template <typename T>
T __vmul(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) * v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vmul_u8 = __vmul<uint8x8_t>;
const auto &vmul_u16 = __vmul<uint16x4_t>;
const auto &vmul_u32 = __vmul<uint32x2_t>;

const auto &vmul_s8 = __vmul<int8x8_t>;
const auto &vmul_s16 = __vmul<int16x4_t>;
const auto &vmul_s32 = __vmul<int32x2_t>;

const auto &vmul_f32 = __vmul<float32x2_t>;

const auto &vmulq_u8 = __vmul<uint8x16_t>;
const auto &vmulq_u16 = __vmul<uint16x8_t>;
const auto &vmulq_u32 = __vmul<uint32x4_t>;

const auto &vmulq_s8 = __vmul<int8x16_t>;
const auto &vmulq_s16 = __vmul<int16x8_t>;
const auto &vmulq_s32 = __vmul<int32x4_t>;

const auto &vmulq_f32 = __vmul<float32x4_t>;

template <typename T, typename R>
R __vmull(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename R::elementType>(i) = (typename R::elementType)v1.template at<typename T::elementType>(i) * v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vmull_s8 = __vmull<int8x8_t, int16x8_t>;
const auto &vmull_s16 = __vmull<int16x4_t, int32x4_t>;
const auto &vmull_s32 = __vmull<int32x2_t, int64x2_t>;

const auto &vmull_u8 = __vmull<uint8x8_t, uint16x8_t>;
const auto &vmull_u16 = __vmull<uint16x4_t, uint32x4_t>;
const auto &vmull_u32 = __vmull<uint32x2_t, uint64x2_t>;

template <typename T>
T __vmul_lane(T v1, T v2, int32_t x)
{
    T p = __vdup_lane<T, typename T::elementType>(v2, x);
    return __vmul(v1, p);
}

const auto &vmul_lane_s16 = __vmul_lane<int16x4_t>;
const auto &vmul_lane_s32 = __vmul_lane<int32x2_t>;

const auto &vmul_lane_u16 = __vmul_lane<uint16x4_t>;
const auto &vmul_lane_u32 = __vmul_lane<uint32x2_t>;

const auto &vmul_lane_f32 = __vmul_lane<float32x2_t>;

const auto &vmulq_lane_s16 = __vmul_lane<int16x8_t>;
const auto &vmulq_lane_s32 = __vmul_lane<int32x4_t>;

const auto &vmulq_lane_u16 = __vmul_lane<uint16x8_t>;
const auto &vmulq_lane_u32 = __vmul_lane<uint32x4_t>;

const auto &vmulq_lane_f32 = __vmul_lane<float32x4_t>;



template <typename T>
T __vmul_n(T v, typename T::elementType x)
{
    return __vmul(v, __vdup<T, typename T::elementType>(x));
}
const auto &vmul_n_s16 = __vmul_n<int16x4_t>;
const auto &vmul_n_s32 = __vmul_n<int32x2_t>;

const auto &vmul_n_u16 = __vmul_n<uint16x4_t>;
const auto &vmul_n_u32 = __vmul_n<uint32x2_t>;

const auto &vmul_n_f32 = __vmul_n<float32x2_t>;

const auto &vmulq_n_s16 = __vmul_n<int16x8_t>;
const auto &vmulq_n_s32 = __vmul_n<int32x4_t>;

const auto &vmulq_n_u16 = __vmul_n<uint16x8_t>;
const auto &vmulq_n_u32 = __vmul_n<uint32x4_t>;

const auto &vmulq_n_f32 = __vmul_n<float32x4_t>;

}

using namespace iris::arm::multiplication;

#endif