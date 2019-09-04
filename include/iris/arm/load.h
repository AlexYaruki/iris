#include "common.h"
#include "elements.h"

#ifndef IRIS_ARM_NEON_LOAD
#define IRIS_ARM_NEON_LOAD

namespace iris::arm::load
{
template <typename T>
T __vld1(const typename T::elementType *src)
{
    T result;
    result.setAll(src[0]);
    return result;
}

template <typename T>
T __vld(const typename T::vectorType::elementType *src)
{
    T result;
    size_t elementCount = T::lanes * T::vectorType::length;
    for (size_t i = 0; i < elementCount; i++)
    {
        result.val[i % T::lanes].template at<typename T::vectorType::elementType>(i / T::lanes) = src[i];
    }
    return result;
}

template <typename T>
T __vld1_lane(typename T::elementType *src, T v, int pos)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        if (i == static_cast<size_t>(pos))
        {
            result.template at<typename T::elementType>(i) = *src;
        }
        else
        {
            result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>(i);
        }
    }
    return result;
}

template <typename T>
T __vld_lane(typename T::vectorType::elementType *src, T v, int32_t pos)
{
    T result = v;
    for (size_t i = 0, j = 0; i < T::lanes; i++, j++)
    {
        result.val[i].template at<typename T::vectorType::elementType>(pos) = src[j];
    }
    return result;
}

template <typename T>
T __vld1_dup(typename T::elementType *src)
{
    typename T::elementType x = *src;
    T result = __vdup<T, typename T::elementType>(x);
    return result;
}

template <typename T>
T __vld_dup(typename T::vectorType::elementType *src)
{
    T result;
    for (size_t i = 0; i < T::lanes; i++)
    {
        result.val[i] = __vld1_dup<typename T::vectorType>(src + i);
    }
    return result;
}

// ARM NEON - vld1 - 64-bit vector //////////////////////////////////////////
const auto &vld1_u8 = __vld1<uint8x8_t>;
const auto &vld1_u16 = __vld1<uint16x4_t>;
const auto &vld1_u32 = __vld1<uint32x2_t>;
const auto &vld1_u64 = __vld1<uint64x1_t>;

const auto &vld1_s8 = __vld1<int8x8_t>;
const auto &vld1_s16 = __vld1<int16x4_t>;
const auto &vld1_s32 = __vld1<int32x2_t>;
const auto &vld1_s64 = __vld1<int64x1_t>;

const auto &vld1_f32 = __vld1<float32x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld1 - 128-bit vector //////////////////////////////////////////
const auto &vld1q_u8 = __vld1<uint8x16_t>;
const auto &vld1q_u16 = __vld1<uint16x8_t>;
const auto &vld1q_u32 = __vld1<uint32x4_t>;
const auto &vld1q_u64 = __vld1<uint64x2_t>;

const auto &vld1q_s8 = __vld1<int8x16_t>;
const auto &vld1q_s16 = __vld1<int16x8_t>;
const auto &vld1q_s32 = __vld1<int32x4_t>;
const auto &vld1q_s64 = __vld1<int64x2_t>;

const auto &vld1q_f32 = __vld1<float32x4_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld1_lane - 64-bit vector //////////////////////////////////////////
const auto &vld1_lane_u8 = __vld1_lane<uint8x8_t>;
const auto &vld1_lane_u16 = __vld1_lane<uint16x4_t>;
const auto &vld1_lane_u32 = __vld1_lane<uint32x2_t>;
const auto &vld1_lane_u64 = __vld1_lane<uint64x1_t>;

const auto &vld1_lane_s8 = __vld1_lane<int8x8_t>;
const auto &vld1_lane_s16 = __vld1_lane<int16x4_t>;
const auto &vld1_lane_s32 = __vld1_lane<int32x2_t>;
const auto &vld1_lane_s64 = __vld1_lane<int64x1_t>;

const auto &vld1_lane_f32 = __vld1_lane<float32x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld1_lane - 128-bit vector //////////////////////////////////////////
const auto &vld1q_lane_u8 = __vld1_lane<uint8x16_t>;
const auto &vld1q_lane_u16 = __vld1_lane<uint16x8_t>;
const auto &vld1q_lane_u32 = __vld1_lane<uint32x4_t>;
const auto &vld1q_lane_u64 = __vld1_lane<uint64x2_t>;

const auto &vld1q_lane_s8 = __vld1_lane<int8x16_t>;
const auto &vld1q_lane_s16 = __vld1_lane<int16x8_t>;
const auto &vld1q_lane_s32 = __vld1_lane<int32x4_t>;
const auto &vld1q_lane_s64 = __vld1_lane<int64x2_t>;

const auto &vld1q_lane_f32 = __vld1_lane<float32x4_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld1_dup - 64-bit vector //////////////////////////////////////////
const auto &vld1_dup_u8 = __vld1_dup<uint8x8_t>;
const auto &vld1_dup_u16 = __vld1_dup<uint16x4_t>;
const auto &vld1_dup_u32 = __vld1_dup<uint32x2_t>;
const auto &vld1_dup_u64 = __vld1_dup<uint64x1_t>;

const auto &vld1_dup_s8 = __vld1_dup<int8x8_t>;
const auto &vld1_dup_s16 = __vld1_dup<int16x4_t>;
const auto &vld1_dup_s32 = __vld1_dup<int32x2_t>;
const auto &vld1_dup_s64 = __vld1_dup<int64x1_t>;

const auto &vld1_dup_f32 = __vld1_dup<float32x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld1_dup - 128-bit vector //////////////////////////////////////////
const auto &vld1q_dup_u8 = __vld1_dup<uint8x16_t>;
const auto &vld1q_dup_u16 = __vld1_dup<uint16x8_t>;
const auto &vld1q_dup_u32 = __vld1_dup<uint32x4_t>;
const auto &vld1q_dup_u64 = __vld1_dup<uint64x2_t>;

const auto &vld1q_dup_s8 = __vld1_dup<int8x16_t>;
const auto &vld1q_dup_s16 = __vld1_dup<int16x8_t>;
const auto &vld1q_dup_s32 = __vld1_dup<int32x4_t>;
const auto &vld1q_dup_s64 = __vld1_dup<int64x2_t>;

const auto &vld1q_dup_f32 = __vld1_dup<float32x4_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON vld2 - 64-bit vectors ///////////////////////////////////////////
const auto &vld2_s8 = __vld<int8x8x2_t>;
const auto &vld2_s16 = __vld<int16x4x2_t>;
const auto &vld2_s32 = __vld<int32x2x2_t>;
const auto &vld2_s64 = __vld<int64x1x2_t>;

const auto &vld2_u8 = __vld<uint8x8x2_t>;
const auto &vld2_u16 = __vld<uint16x4x2_t>;
const auto &vld2_u32 = __vld<uint32x2x2_t>;
const auto &vld2_u64 = __vld<uint64x1x2_t>;

const auto &vld2_f32 = __vld<float32x2x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON vld2 - 128-bit vectors ///////////////////////////////////////////
const auto &vld2q_s8 = __vld<int8x16x2_t>;
const auto &vld2q_s16 = __vld<int16x8x2_t>;
const auto &vld2q_s32 = __vld<int32x4x2_t>;
const auto &vld2q_s64 = __vld<int64x2x2_t>;

const auto &vld2q_u8 = __vld<uint8x16x2_t>;
const auto &vld2q_u16 = __vld<uint16x8x2_t>;
const auto &vld2q_u32 = __vld<uint32x4x2_t>;
const auto &vld2q_u64 = __vld<uint64x2x2_t>;

const auto &vld2q_f32 = __vld<float32x4x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vld2_lane - 64-bit vector //////////////////////////////////////////
const auto &vld2_lane_u8 = __vld_lane<uint8x8x2_t>;
const auto &vld2_lane_u16 = __vld_lane<uint16x4x2_t>;
const auto &vld2_lane_u32 = __vld_lane<uint32x2x2_t>;

const auto &vld2_lane_s8 = __vld_lane<int8x8x2_t>;
const auto &vld2_lane_s16 = __vld_lane<int16x4x2_t>;
const auto &vld2_lane_s32 = __vld_lane<int32x2x2_t>;

const auto &vld2_lane_f32 = __vld_lane<float32x2x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld2_lane - 128-bit vector //////////////////////////////////////////
const auto &vld2q_lane_u8 = __vld_lane<uint8x16x2_t>;
const auto &vld2q_lane_u16 = __vld_lane<uint16x8x2_t>;
const auto &vld2q_lane_u32 = __vld_lane<uint32x4x2_t>;

const auto &vld2q_lane_s8 = __vld_lane<int8x16x2_t>;
const auto &vld2q_lane_s16 = __vld_lane<int16x8x2_t>;
const auto &vld2q_lane_s32 = __vld_lane<int32x4x2_t>;

const auto &vld2q_lane_f32 = __vld_lane<float32x4x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld2_dup - 64-bit vector //////////////////////////////////////////
const auto &vld2_dup_u8 = __vld_dup<uint8x8x2_t>;
const auto &vld2_dup_u16 = __vld_dup<uint16x4x2_t>;
const auto &vld2_dup_u32 = __vld_dup<uint32x2x2_t>;
const auto &vld2_dup_u64 = __vld_dup<uint64x1x2_t>;

const auto &vld2_dup_s8 = __vld_dup<int8x8x2_t>;
const auto &vld2_dup_s16 = __vld_dup<int16x4x2_t>;
const auto &vld2_dup_s32 = __vld_dup<int32x2x2_t>;
const auto &vld2_dup_s64 = __vld_dup<int64x1x2_t>;

const auto &vld2_dup_f32 = __vld_dup<float32x2x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld2_dup - 128-bit vector //////////////////////////////////////////
const auto &vld2q_dup_u8 = __vld_dup<uint8x16x2_t>;
const auto &vld2q_dup_u16 = __vld_dup<uint16x8x2_t>;
const auto &vld2q_dup_u32 = __vld_dup<uint32x4x2_t>;
const auto &vld2q_dup_u64 = __vld_dup<uint64x2x2_t>;

const auto &vld2q_dup_s8 = __vld_dup<int8x16x2_t>;
const auto &vld2q_dup_s16 = __vld_dup<int16x8x2_t>;
const auto &vld2q_dup_s32 = __vld_dup<int32x4x2_t>;
const auto &vld2q_dup_s64 = __vld_dup<int64x2x2_t>;

const auto &vld2q_dup_f32 = __vld_dup<float32x4x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON vld3 - 64-bit vectors ///////////////////////////////////////////
const auto &vld3_s8 = __vld<int8x8x3_t>;
const auto &vld3_s16 = __vld<int16x4x3_t>;
const auto &vld3_s32 = __vld<int32x2x3_t>;
const auto &vld3_s64 = __vld<int64x1x3_t>;

const auto &vld3_u8 = __vld<uint8x8x3_t>;
const auto &vld3_u16 = __vld<uint16x4x3_t>;
const auto &vld3_u32 = __vld<uint32x2x3_t>;
const auto &vld3_u64 = __vld<uint64x1x3_t>;

const auto &vld3_f32 = __vld<float32x2x3_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON vld3 - 128-bit vectors ///////////////////////////////////////////
const auto &vld3q_s8 = __vld<int8x16x3_t>;
const auto &vld3q_s16 = __vld<int16x8x3_t>;
const auto &vld3q_s32 = __vld<int32x4x3_t>;
const auto &vld3q_s64 = __vld<int64x2x3_t>;

const auto &vld3q_u8 = __vld<uint8x16x3_t>;
const auto &vld3q_u16 = __vld<uint16x8x3_t>;
const auto &vld3q_u32 = __vld<uint32x4x3_t>;
const auto &vld3q_u64 = __vld<uint64x2x3_t>;

const auto &vld3q_f32 = __vld<float32x4x3_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vld3_lane - 64-bit vector //////////////////////////////////////////
const auto &vld3_lane_u8 = __vld_lane<uint8x8x3_t>;
const auto &vld3_lane_u16 = __vld_lane<uint16x4x3_t>;
const auto &vld3_lane_u32 = __vld_lane<uint32x2x3_t>;

const auto &vld3_lane_s8 = __vld_lane<int8x8x3_t>;
const auto &vld3_lane_s16 = __vld_lane<int16x4x3_t>;
const auto &vld3_lane_s32 = __vld_lane<int32x2x3_t>;

const auto &vld3_lane_f32 = __vld_lane<float32x2x3_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld3_lane - 128-bit vector //////////////////////////////////////////
const auto &vld3q_lane_u8 = __vld_lane<uint8x16x3_t>;
const auto &vld3q_lane_u16 = __vld_lane<uint16x8x3_t>;
const auto &vld3q_lane_u32 = __vld_lane<uint32x4x3_t>;

const auto &vld3q_lane_s8 = __vld_lane<int8x16x3_t>;
const auto &vld3q_lane_s16 = __vld_lane<int16x8x3_t>;
const auto &vld3q_lane_s32 = __vld_lane<int32x4x3_t>;

const auto &vld3q_lane_f32 = __vld_lane<float32x4x3_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld3_dup - 64-bit vector //////////////////////////////////////////
const auto &vld3_dup_u8 = __vld_dup<uint8x8x2_t>;
const auto &vld3_dup_u16 = __vld_dup<uint16x4x2_t>;
const auto &vld3_dup_u32 = __vld_dup<uint32x2x2_t>;
const auto &vld3_dup_u64 = __vld_dup<uint64x1x2_t>;

const auto &vld3_dup_s8 = __vld_dup<int8x8x2_t>;
const auto &vld3_dup_s16 = __vld_dup<int16x4x2_t>;
const auto &vld3_dup_s32 = __vld_dup<int32x2x2_t>;
const auto &vld3_dup_s64 = __vld_dup<int64x1x2_t>;

const auto &vld3_dup_f32 = __vld_dup<float32x2x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld3_dup - 128-bit vector //////////////////////////////////////////
const auto &vld3q_dup_u8 = __vld_dup<uint8x16x2_t>;
const auto &vld3q_dup_u16 = __vld_dup<uint16x8x2_t>;
const auto &vld3q_dup_u32 = __vld_dup<uint32x4x2_t>;
const auto &vld3q_dup_u64 = __vld_dup<uint64x2x2_t>;

const auto &vld3q_dup_s8 = __vld_dup<int8x16x2_t>;
const auto &vld3q_dup_s16 = __vld_dup<int16x8x2_t>;
const auto &vld3q_dup_s32 = __vld_dup<int32x4x2_t>;
const auto &vld3q_dup_s64 = __vld_dup<int64x2x2_t>;

const auto &vld3q_dup_f32 = __vld_dup<float32x4x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON vld4 - 64-bit vectors ///////////////////////////////////////////
const auto &vld4_s8 = __vld<int8x8x4_t>;
const auto &vld4_s16 = __vld<int16x4x4_t>;
const auto &vld4_s32 = __vld<int32x2x4_t>;
const auto &vld4_s64 = __vld<int64x1x4_t>;

const auto &vld4_u8 = __vld<uint8x8x4_t>;
const auto &vld4_u16 = __vld<uint16x4x4_t>;
const auto &vld4_u32 = __vld<uint32x2x4_t>;
const auto &vld4_u64 = __vld<uint64x1x4_t>;

const auto &vld4_f32 = __vld<float32x2x4_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON vld4 - 128-bit vectors ///////////////////////////////////////////
const auto &vld4q_s8 = __vld<int8x16x4_t>;
const auto &vld4q_s16 = __vld<int16x8x4_t>;
const auto &vld4q_s32 = __vld<int32x4x4_t>;
const auto &vld4q_s64 = __vld<int64x2x4_t>;

const auto &vld4q_u8 = __vld<uint8x16x4_t>;
const auto &vld4q_u16 = __vld<uint16x8x4_t>;
const auto &vld4q_u32 = __vld<uint32x4x4_t>;
const auto &vld4q_u64 = __vld<uint64x2x4_t>;

const auto &vld4q_f32 = __vld<float32x4x4_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vld4_lane - 64-bit vector //////////////////////////////////////////
const auto &vld4_lane_u8 = __vld_lane<uint8x8x4_t>;
const auto &vld4_lane_u16 = __vld_lane<uint16x4x4_t>;
const auto &vld4_lane_u32 = __vld_lane<uint32x2x4_t>;

const auto &vld4_lane_s8 = __vld_lane<int8x8x4_t>;
const auto &vld4_lane_s16 = __vld_lane<int16x4x4_t>;
const auto &vld4_lane_s32 = __vld_lane<int32x2x4_t>;

const auto &vld4_lane_f32 = __vld_lane<float32x2x4_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld4_lane - 128-bit vector //////////////////////////////////////////
const auto &vld4q_lane_u8 = __vld_lane<uint8x16x4_t>;
const auto &vld4q_lane_u16 = __vld_lane<uint16x8x4_t>;
const auto &vld4q_lane_u32 = __vld_lane<uint32x4x4_t>;

const auto &vld4q_lane_s8 = __vld_lane<int8x16x4_t>;
const auto &vld4q_lane_s16 = __vld_lane<int16x8x4_t>;
const auto &vld4q_lane_s32 = __vld_lane<int32x4x4_t>;

const auto &vld4q_lane_f32 = __vld_lane<float32x4x4_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld4_dup - 64-bit vector //////////////////////////////////////////
const auto &vld4_dup_u8 = __vld_dup<uint8x8x2_t>;
const auto &vld4_dup_u16 = __vld_dup<uint16x4x2_t>;
const auto &vld4_dup_u32 = __vld_dup<uint32x2x2_t>;
const auto &vld4_dup_u64 = __vld_dup<uint64x1x2_t>;

const auto &vld4_dup_s8 = __vld_dup<int8x8x2_t>;
const auto &vld4_dup_s16 = __vld_dup<int16x4x2_t>;
const auto &vld4_dup_s32 = __vld_dup<int32x2x2_t>;
const auto &vld4_dup_s64 = __vld_dup<int64x1x2_t>;

const auto &vld4_dup_f32 = __vld_dup<float32x2x2_t>;
/////////////////////////////////////////////////////////////////////////////

// ARM NEON - vld4_dup - 128-bit vector //////////////////////////////////////////
const auto &vld4q_dup_u8 = __vld_dup<uint8x16x2_t>;
const auto &vld4q_dup_u16 = __vld_dup<uint16x8x2_t>;
const auto &vld4q_dup_u32 = __vld_dup<uint32x4x2_t>;
const auto &vld4q_dup_u64 = __vld_dup<uint64x2x2_t>;

const auto &vld4q_dup_s8 = __vld_dup<int8x16x2_t>;
const auto &vld4q_dup_s16 = __vld_dup<int16x8x2_t>;
const auto &vld4q_dup_s32 = __vld_dup<int32x4x2_t>;
const auto &vld4q_dup_s64 = __vld_dup<int64x2x2_t>;

const auto &vld4q_dup_f32 = __vld_dup<float32x4x2_t>;
/////////////////////////////////////////////////////////////////////////////
} // namespace iris::arm::load

using namespace iris::arm::load;

#endif