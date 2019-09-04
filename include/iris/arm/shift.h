#include "common.h"

#ifndef IRIS_ARM_SHIFT
#define IRIS_ARM_SHIFT

namespace iris::arm::shift
{

template <typename T>
T __vshl(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType value = v1.template at<typename T::elementType>(i);
        typename T::elementType shift = v2.template at<typename T::elementType>(i);
        if (std::numeric_limits<typename T::elementType>::is_signed && shift < 0)
        {
            result.template at<typename T::elementType>(i) = value >> -shift;
        }
        else
        {
            result.template at<typename T::elementType>(i) = value << shift;
        }
    }
    return result;
}

template <typename T>
T __vshl_n(T v, uint32_t shift)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType value = v.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) = value << shift;
    }
    return result;
}

template <typename T>
T __vshr_n(T v, uint32_t shift)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType value = v.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) = value >> shift;
    }
    return result;
}

template <typename T>
T __vrshr_n(T v, uint32_t shift)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType value = v.template at<typename T::elementType>(i);
        if (value % 2 != 0)
        {
            value = value + 1;
        }
        typename T::elementType part = value >> shift;
        result.template at<typename T::elementType>(i) = part;
    }
    return result;
}

// ARM NEON - vshl - 64-bit vectors ////////////////////////////////////
const auto &vshl_u8 = __vshl<uint8x8_t>;
const auto &vshl_u16 = __vshl<uint16x4_t>;
const auto &vshl_u32 = __vshl<uint32x2_t>;
const auto &vshl_u64 = __vshl<uint64x1_t>;

const auto &vshl_s8 = __vshl<int8x8_t>;
const auto &vshl_s16 = __vshl<int16x4_t>;
const auto &vshl_s32 = __vshl<int32x2_t>;
const auto &vshl_s64 = __vshl<int64x1_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshl - 128-bit vectors ////////////////////////////////////
const auto &vshlq_u8 = __vshl<uint8x16_t>;
const auto &vshlq_u16 = __vshl<uint16x8_t>;
const auto &vshlq_u32 = __vshl<uint32x4_t>;
const auto &vshlq_u64 = __vshl<uint64x2_t>;

const auto &vshlq_s8 = __vshl<int8x16_t>;
const auto &vshlq_s16 = __vshl<int16x8_t>;
const auto &vshlq_s32 = __vshl<int32x4_t>;
const auto &vshlq_s64 = __vshl<int64x2_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshl_n - 64-bit vectors ////////////////////////////////////
const auto &vshl_n_u8 = __vshl_n<uint8x8_t>;
const auto &vshl_n_u16 = __vshl_n<uint16x4_t>;
const auto &vshl_n_u32 = __vshl_n<uint32x2_t>;
const auto &vshl_n_u64 = __vshl_n<uint64x1_t>;

const auto &vshl_n_s8 = __vshl_n<int8x8_t>;
const auto &vshl_n_s16 = __vshl_n<int16x4_t>;
const auto &vshl_n_s32 = __vshl_n<int32x2_t>;
const auto &vshl_n_s64 = __vshl_n<int64x1_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshl - 128-bit vectors ////////////////////////////////////
const auto &vshlq_n_u8 = __vshl_n<uint8x16_t>;
const auto &vshlq_n_u16 = __vshl_n<uint16x8_t>;
const auto &vshlq_n_u32 = __vshl_n<uint32x4_t>;
const auto &vshlq_n_u64 = __vshl_n<uint64x2_t>;

const auto &vshlq_n_s8 = __vshl_n<int8x16_t>;
const auto &vshlq_n_s16 = __vshl_n<int16x8_t>;
const auto &vshlq_n_s32 = __vshl_n<int32x4_t>;
const auto &vshlq_n_s64 = __vshl_n<int64x2_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshr_n - 64-bit vectors ////////////////////////////////////
const auto &vshr_n_u8 = __vshr_n<uint8x8_t>;
const auto &vshr_n_u16 = __vshr_n<uint16x4_t>;
const auto &vshr_n_u32 = __vshr_n<uint32x2_t>;
const auto &vshr_n_u64 = __vshr_n<uint64x1_t>;

const auto &vshr_n_s8 = __vshr_n<int8x8_t>;
const auto &vshr_n_s16 = __vshr_n<int16x4_t>;
const auto &vshr_n_s32 = __vshr_n<int32x2_t>;
const auto &vshr_n_s64 = __vshr_n<int64x1_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshr - 128-bit vectors ////////////////////////////////////
const auto &vshrq_n_u8 = __vshr_n<uint8x16_t>;
const auto &vshrq_n_u16 = __vshr_n<uint16x8_t>;
const auto &vshrq_n_u32 = __vshr_n<uint32x4_t>;
const auto &vshrq_n_u64 = __vshr_n<uint64x2_t>;

const auto &vshrq_n_s8 = __vshr_n<int8x16_t>;
const auto &vshrq_n_s16 = __vshr_n<int16x8_t>;
const auto &vshrq_n_s32 = __vshr_n<int32x4_t>;
const auto &vshrq_n_s64 = __vshr_n<int64x2_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshr_n - 64-bit vectors ////////////////////////////////////
const auto &vrshr_n_u8 = __vrshr_n<uint8x8_t>;
const auto &vrshr_n_u16 = __vrshr_n<uint16x4_t>;
const auto &vrshr_n_u32 = __vrshr_n<uint32x2_t>;
const auto &vrshr_n_u64 = __vrshr_n<uint64x1_t>;

const auto &vrshr_n_s8 = __vrshr_n<int8x8_t>;
const auto &vrshr_n_s16 = __vrshr_n<int16x4_t>;
const auto &vrshr_n_s32 = __vrshr_n<int32x2_t>;
const auto &vrshr_n_s64 = __vrshr_n<int64x1_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vshr - 128-bit vectors ////////////////////////////////////
const auto &vrshrq_n_u8 = __vrshr_n<uint8x16_t>;
const auto &vrshrq_n_u16 = __vrshr_n<uint16x8_t>;
const auto &vrshrq_n_u32 = __vrshr_n<uint32x4_t>;
const auto &vrshrq_n_u64 = __vrshr_n<uint64x2_t>;

const auto &vrshrq_n_s8 = __vrshr_n<int8x16_t>;
const auto &vrshrq_n_s16 = __vrshr_n<int16x8_t>;
const auto &vrshrq_n_s32 = __vrshr_n<int32x4_t>;
const auto &vrshrq_n_s64 = __vrshr_n<int64x2_t>;
////////////////////////////////////////////////////////////////////////

} // namespace iris::arm::shift

using namespace iris::arm::shift;

#endif