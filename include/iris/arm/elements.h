#include "common.h"
#include <cstdint>

#ifndef IRIS_ARM_ELEMENTS
#define IRIS_ARM_ELEMENTS

namespace iris::arm::elements
{
template <typename T, typename E>
T __vdup(E elem)
{
    T result;
    result.setAll(elem);
    return result;
}

const auto &vdup_n_s8 = __vdup<int8x8_t, int8_t>;
const auto &vdup_n_s16 = __vdup<int16x4_t, int16_t>;
const auto &vdup_n_s32 = __vdup<int32x2_t, int32_t>;
const auto &vdup_n_s64 = __vdup<int64x1_t, int64_t>;

const auto &vmov_n_s8 = __vdup<int8x8_t, int8_t>;
const auto &vmov_n_s16 = __vdup<int16x4_t, int16_t>;
const auto &vmov_n_s32 = __vdup<int32x2_t, int32_t>;
const auto &vmov_n_s64 = __vdup<int64x1_t, int64_t>;

const auto &vdup_n_u8 = __vdup<uint8x8_t, uint8_t>;
const auto &vdup_n_u16 = __vdup<uint16x4_t, uint16_t>;
const auto &vdup_n_u32 = __vdup<uint32x2_t, uint32_t>;
const auto &vdup_n_u64 = __vdup<uint64x1_t, uint64_t>;

const auto &vmov_n_u8 = __vdup<uint8x8_t, uint8_t>;
const auto &vmov_n_u16 = __vdup<uint16x4_t, uint16_t>;
const auto &vmov_n_u32 = __vdup<uint32x2_t, uint32_t>;
const auto &vmov_n_u64 = __vdup<uint64x1_t, uint64_t>;

const auto &vdup_n_f32 = __vdup<float32x2_t, float>;
const auto &vmov_n_f32 = __vdup<float32x2_t, float>;

const auto &vdupq_n_s8 = __vdup<int8x16_t, int8_t>;
const auto &vdupq_n_s16 = __vdup<int16x8_t, int16_t>;
const auto &vdupq_n_s32 = __vdup<int32x4_t, int32_t>;
const auto &vdupq_n_s64 = __vdup<int64x2_t, int64_t>;

const auto &vmovq_n_s8 = __vdup<int8x16_t, int8_t>;
const auto &vmovq_n_s16 = __vdup<int16x8_t, int16_t>;
const auto &vmovq_n_s32 = __vdup<int32x4_t, int32_t>;
const auto &vmovq_n_s64 = __vdup<int64x2_t, int64_t>;

const auto &vdupq_n_u8 = __vdup<uint8x16_t, uint8_t>;
const auto &vdupq_n_u16 = __vdup<uint16x8_t, uint16_t>;
const auto &vdupq_n_u32 = __vdup<uint32x4_t, uint32_t>;
const auto &vdupq_n_u64 = __vdup<uint64x2_t, uint64_t>;

const auto &vmovq_n_u8 = __vdup<uint8x16_t, uint8_t>;
const auto &vmovq_n_u16 = __vdup<uint16x8_t, uint16_t>;
const auto &vmovq_n_u32 = __vdup<uint32x4_t, uint32_t>;
const auto &vmovq_n_u64 = __vdup<uint64x2_t, uint64_t>;

const auto &vdupq_n_f32 = __vdup<float32x4_t, float>;
const auto &vmovq_n_f32 = __vdup<float32x4_t, float>;

template <typename T, typename E>
E __vget_lane(T v, size_t i)
{
    return v.template at<E>(i);
}

const auto &vget_lane_s8 = __vget_lane<int8x8_t, int8_t>;
const auto &vget_lane_s16 = __vget_lane<int16x4_t, int16_t>;
const auto &vget_lane_s32 = __vget_lane<int32x2_t, int32_t>;
const auto &vget_lane_s64 = __vget_lane<int64x1_t, int64_t>;

const auto &vget_lane_u8 = __vget_lane<uint8x8_t, uint8_t>;
const auto &vget_lane_u16 = __vget_lane<uint16x4_t, uint16_t>;
const auto &vget_lane_u32 = __vget_lane<uint32x2_t, uint32_t>;
const auto &vget_lane_u64 = __vget_lane<uint64x1_t, uint64_t>;

const auto &vget_lane_f32 = __vget_lane<float32x2_t, float>;

const auto &vgetq_lane_s8 = __vget_lane<int8x16_t, int8_t>;
const auto &vgetq_lane_s16 = __vget_lane<int16x8_t, int16_t>;
const auto &vgetq_lane_s32 = __vget_lane<int32x4_t, int32_t>;
const auto &vgetq_lane_s64 = __vget_lane<int64x2_t, int64_t>;

const auto &vgetq_lane_u8 = __vget_lane<uint8x16_t, uint8_t>;
const auto &vgetq_lane_u16 = __vget_lane<uint16x8_t, uint16_t>;
const auto &vgetq_lane_u32 = __vget_lane<uint32x4_t, uint32_t>;
const auto &vgetq_lane_u64 = __vget_lane<uint64x2_t, uint64_t>;

const auto &vgetq_lane_f32 = __vget_lane<float32x4_t, float>;

template <typename T, typename E>
T __vdup_lane(T v, int32_t i)
{
    return __vdup<T, E>(__vget_lane<T, E>(v, i));
}

const auto &vdup_lane_s8 = __vdup_lane<int8x8_t, int8_t>;
const auto &vdup_lane_s16 = __vdup_lane<int16x4_t, int16_t>;
const auto &vdup_lane_s32 = __vdup_lane<int32x2_t, int32_t>;
const auto &vdup_lane_s64 = __vdup_lane<int64x1_t, int64_t>;

const auto &vdup_lane_u8 = __vdup_lane<uint8x8_t, uint8_t>;
const auto &vdup_lane_u16 = __vdup_lane<uint16x4_t, uint16_t>;
const auto &vdup_lane_u32 = __vdup_lane<uint32x2_t, uint32_t>;
const auto &vdup_lane_u64 = __vdup_lane<uint64x1_t, uint64_t>;

const auto &vdup_lane_f32 = __vdup_lane<float32x2_t, float>;

const auto &vdupq_lane_s8 = __vdup_lane<int8x16_t, int8_t>;
const auto &vdupq_lane_s16 = __vdup_lane<int16x8_t, int16_t>;
const auto &vdupq_lane_s32 = __vdup_lane<int32x4_t, int32_t>;
const auto &vdupq_lane_s64 = __vdup_lane<int64x2_t, int64_t>;

const auto &vdupq_lane_u8 = __vdup_lane<uint8x16_t, uint8_t>;
const auto &vdupq_lane_u16 = __vdup_lane<uint16x8_t, uint16_t>;
const auto &vdupq_lane_u32 = __vdup_lane<uint32x4_t, uint32_t>;
const auto &vdupq_lane_u64 = __vdup_lane<uint64x2_t, uint64_t>;

const auto &vdupq_lane_f32 = __vdup_lane<float32x4_t, float>;

template <typename T>
T __vset_lane(typename T::elementType x, T v, int32_t i)
{
    T result = v;
    result.template at<typename T::elementType>(i) = x;
    return result;
}

const auto &vset_lane_s8 = __vset_lane<int8x8_t>;
const auto &vset_lane_s16 = __vset_lane<int16x4_t>;
const auto &vset_lane_s32 = __vset_lane<int32x2_t>;
const auto &vset_lane_s64 = __vset_lane<int64x1_t>;

const auto &vset_lane_u8 = __vset_lane<uint8x8_t>;
const auto &vset_lane_u16 = __vset_lane<uint16x4_t>;
const auto &vset_lane_u32 = __vset_lane<uint32x2_t>;
const auto &vset_lane_u64 = __vset_lane<uint64x1_t>;

const auto &vset_lane_f32 = __vset_lane<float32x2_t>;

const auto &vsetq_lane_s8 = __vset_lane<int8x16_t>;
const auto &vsetq_lane_s16 = __vset_lane<int16x8_t>;
const auto &vsetq_lane_s32 = __vset_lane<int32x4_t>;
const auto &vsetq_lane_s64 = __vset_lane<int64x2_t>;

const auto &vsetq_lane_u8 = __vset_lane<uint8x16_t>;
const auto &vsetq_lane_u16 = __vset_lane<uint16x8_t>;
const auto &vsetq_lane_u32 = __vset_lane<uint32x4_t>;
const auto &vsetq_lane_u64 = __vset_lane<uint64x2_t>;

const auto &vsetq_lane_f32 = __vset_lane<float32x4_t>;

template <typename T, typename R>
typename std::enable_if<sizeof(T) / 2 == sizeof(R), R>::type __vget_high(T v)
{
    R result;
    for (size_t i = T::length / 2, j = 0; i < T::length; i++, j++)
    {
        result.template at<typename R::elementType>(j) = v.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vget_high_s8 = __vget_high<int8x16_t, int8x8_t>;
const auto &vget_high_s16 = __vget_high<int16x8_t, int16x4_t>;
const auto &vget_high_s32 = __vget_high<int32x4_t, int32x2_t>;
const auto &vget_high_s64 = __vget_high<int64x2_t, int64x1_t>;

const auto &vget_high_u8 = __vget_high<uint8x16_t, uint8x8_t>;
const auto &vget_high_u16 = __vget_high<uint16x8_t, uint16x4_t>;
const auto &vget_high_u32 = __vget_high<uint32x4_t, uint32x2_t>;
const auto &vget_high_u64 = __vget_high<uint64x2_t, uint64x1_t>;

const auto &vget_high_f32 = __vget_high<float32x4_t, float32x2_t>;

template <typename T, typename R>
typename std::enable_if<sizeof(T) / 2 == sizeof(R), R>::type __vget_low(T v)
{
    R result;
    for (size_t i = 0; i < R::length; i++)
    {
        result.template at<typename R::elementType>(i) = v.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vget_low_s8 = __vget_low<int8x16_t, int8x8_t>;
const auto &vget_low_s16 = __vget_low<int16x8_t, int16x4_t>;
const auto &vget_low_s32 = __vget_low<int32x4_t, int32x2_t>;
const auto &vget_low_s64 = __vget_low<int64x2_t, int64x1_t>;

const auto &vget_low_u8 = __vget_low<uint8x16_t, uint8x8_t>;
const auto &vget_low_u16 = __vget_low<uint16x8_t, uint16x4_t>;
const auto &vget_low_u32 = __vget_low<uint32x4_t, uint32x2_t>;
const auto &vget_low_u64 = __vget_low<uint64x2_t, uint64x1_t>;

const auto &vget_low_f32 = __vget_low<float32x4_t, float32x2_t>;

template <typename T, typename R>
typename std::enable_if<sizeof(T) * 2 == sizeof(R), R>::type __vcombine(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename R::elementType>(i) = v1.template at<typename T::elementType>(i);
    }
    for (size_t i = 0, j = T::length; i < T::length; i++, j++)
    {
        result.template at<typename R::elementType>(j) = v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vcombine_s8 = __vcombine<int8x8_t, int8x16_t>;
const auto &vcombine_s16 = __vcombine<int16x4_t, int16x8_t>;
const auto &vcombine_s32 = __vcombine<int32x2_t, int32x4_t>;
const auto &vcombine_s64 = __vcombine<int64x1_t, int64x2_t>;

const auto &vcombine_u8 = __vcombine<uint8x8_t, uint8x16_t>;
const auto &vcombine_u16 = __vcombine<uint16x4_t, uint16x8_t>;
const auto &vcombine_u32 = __vcombine<uint32x2_t, uint32x4_t>;
const auto &vcombine_u64 = __vcombine<uint64x1_t, uint64x2_t>;

const auto &vcombine_f32 = __vcombine<float32x2_t, float32x4_t>;

} // namespace iris::arm::elements

using namespace iris::arm::elements;

#endif