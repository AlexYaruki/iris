#include "common.h"

#ifndef IRIS_ARM_BITWISE
#define IRIS_ARM_BITWISE

namespace iris::arm::bitwise
{

template <typename T>
T __vbic(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = ~(v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i));
        result.template at<typename T::elementType>(i) = x;
    }
    return result;
}

const auto &vbic_s8 = __vbic<int8x8_t>;
const auto &vbic_s16 = __vbic<int16x4_t>;
const auto &vbic_s32 = __vbic<int32x2_t>;
const auto &vbic_s64 = __vbic<int64x1_t>;

const auto &vbic_u8 = __vbic<uint8x8_t>;
const auto &vbic_u16 = __vbic<uint16x4_t>;
const auto &vbic_u32 = __vbic<uint32x2_t>;
const auto &vbic_u64 = __vbic<uint64x1_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vbic - 128-bit vector /////////////////////////////////////
const auto &vbicq_s8 = __vbic<int8x16_t>;
const auto &vbicq_s16 = __vbic<int16x8_t>;
const auto &vbicq_s32 = __vbic<int32x4_t>;
const auto &vbicq_s64 = __vbic<int64x2_t>;

const auto &vbicq_u8 = __vbic<uint8x16_t>;
const auto &vbicq_u16 = __vbic<uint16x8_t>;
const auto &vbicq_u32 = __vbic<uint32x4_t>;
const auto &vbicq_u64 = __vbic<uint64x2_t>;

template <typename T>
T __veor(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) ^ v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &veor_s8 = __veor<int8x8_t>;
const auto &veor_s16 = __veor<int16x4_t>;
const auto &veor_s32 = __veor<int32x2_t>;
const auto &veor_s64 = __veor<int64x1_t>;

const auto &veor_u8 = __veor<uint8x8_t>;
const auto &veor_u16 = __veor<uint16x4_t>;
const auto &veor_u32 = __veor<uint32x2_t>;
const auto &veor_u64 = __veor<uint64x1_t>;

const auto &veorq_s8 = __veor<int8x16_t>;
const auto &veorq_s16 = __veor<int16x8_t>;
const auto &veorq_s32 = __veor<int32x4_t>;
const auto &veorq_s64 = __veor<int64x2_t>;

const auto &veorq_u8 = __veor<uint8x16_t>;
const auto &veorq_u16 = __veor<uint16x8_t>;
const auto &veorq_u32 = __veor<uint32x4_t>;
const auto &veorq_u64 = __veor<uint64x2_t>;

template <typename T>
T __vorr(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) | v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vorr_s8 = __vorr<int8x8_t>;
const auto &vorr_s16 = __vorr<int16x4_t>;
const auto &vorr_s32 = __vorr<int32x2_t>;
const auto &vorr_s64 = __vorr<int64x1_t>;

const auto &vorr_u8 = __vorr<uint8x8_t>;
const auto &vorr_u16 = __vorr<uint16x4_t>;
const auto &vorr_u32 = __vorr<uint32x2_t>;
const auto &vorr_u64 = __vorr<uint64x1_t>;

const auto &vorrq_s8 = __vorr<int8x16_t>;
const auto &vorrq_s16 = __vorr<int16x8_t>;
const auto &vorrq_s32 = __vorr<int32x4_t>;
const auto &vorrq_s64 = __vorr<int64x2_t>;

const auto &vorrq_u8 = __vorr<uint8x16_t>;
const auto &vorrq_u16 = __vorr<uint16x8_t>;
const auto &vorrq_u32 = __vorr<uint32x4_t>;
const auto &vorrq_u64 = __vorr<uint64x2_t>;

template <typename T>
T __vorn(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = ~(v1.template at<typename T::elementType>(i) | v2.template at<typename T::elementType>(i));
        result.template at<typename T::elementType>(i) = x;
    }
    return result;
}

const auto &vorn_s8 = __vorn<int8x8_t>;
const auto &vorn_s16 = __vorn<int16x4_t>;
const auto &vorn_s32 = __vorn<int32x2_t>;
const auto &vorn_s64 = __vorn<int64x1_t>;

const auto &vorn_u8 = __vorn<uint8x8_t>;
const auto &vorn_u16 = __vorn<uint16x4_t>;
const auto &vorn_u32 = __vorn<uint32x2_t>;
const auto &vorn_u64 = __vorn<uint64x1_t>;
////////////////////////////////////////////////////////////////////////

// ARM NEON - vorn - 128-bit vector /////////////////////////////////////
const auto &vornq_s8 = __vorn<int8x16_t>;
const auto &vornq_s16 = __vorn<int16x8_t>;
const auto &vornq_s32 = __vorn<int32x4_t>;
const auto &vornq_s64 = __vorn<int64x2_t>;

const auto &vornq_u8 = __vorn<uint8x16_t>;
const auto &vornq_u16 = __vorn<uint16x8_t>;
const auto &vornq_u32 = __vorn<uint32x4_t>;
const auto &vornq_u64 = __vorn<uint64x2_t>;

template <typename T>
T __vand(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vand_s8 = __vand<int8x8_t>;
const auto &vand_s16 = __vand<int16x4_t>;
const auto &vand_s32 = __vand<int32x2_t>;
const auto &vand_s64 = __vand<int64x1_t>;

const auto &vand_u8 = __vand<uint8x8_t>;
const auto &vand_u16 = __vand<uint16x4_t>;
const auto &vand_u32 = __vand<uint32x2_t>;
const auto &vand_u64 = __vand<uint64x1_t>;

const auto &vandq_s8 = __vand<int8x16_t>;
const auto &vandq_s16 = __vand<int16x8_t>;
const auto &vandq_s32 = __vand<int32x4_t>;
const auto &vandq_s64 = __vand<int64x2_t>;

const auto &vandq_u8 = __vand<uint8x16_t>;
const auto &vandq_u16 = __vand<uint16x8_t>;
const auto &vandq_u32 = __vand<uint32x4_t>;
const auto &vandq_u64 = __vand<uint64x2_t>;

} // namespace iris::arm::bitwise

using namespace iris::arm::bitwise;

#endif