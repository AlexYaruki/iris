
#include "common.h"
#ifndef IRIS_ARM_ADDITION
#define IRIS_ARM_ADDITION
namespace iris::arm::addition
{

template <typename T>
T __vadd(T v1, T v2)
{
    return v1.add(v2);
}

const auto &vadd_u8 = __vadd<uint8x8_t>;
const auto &vadd_u16 = __vadd<uint16x4_t>;
const auto &vadd_u32 = __vadd<uint32x2_t>;
const auto &vadd_u64 = __vadd<uint64x1_t>;

const auto &vadd_s8 = __vadd<int8x8_t>;
const auto &vadd_s16 = __vadd<int16x4_t>;
const auto &vadd_s32 = __vadd<int32x2_t>;
const auto &vadd_s64 = __vadd<int64x1_t>;

const auto &vadd_f32 = __vadd<float32x2_t>;

const auto &vaddq_u8 = __vadd<uint8x16_t>;
const auto &vaddq_u16 = __vadd<uint16x8_t>;
const auto &vaddq_u32 = __vadd<uint32x4_t>;
const auto &vaddq_u64 = __vadd<uint64x2_t>;

const auto &vaddq_s8 = __vadd<int8x16_t>;
const auto &vaddq_s16 = __vadd<int16x8_t>;
const auto &vaddq_s32 = __vadd<int32x4_t>;
const auto &vaddq_s64 = __vadd<int64x2_t>;

const auto &vaddq_f32 = __vadd<float32x4_t>;

template <typename T,
          typename R>
R __vaddl(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename R::elementType x = static_cast<typename R::elementType>(v1.template at<typename T::elementType>(i));
        typename R::elementType y = static_cast<typename R::elementType>(v2.template at<typename T::elementType>(i));
        result.template at<typename R::elementType>(i) = x + y;
    }
    return result;
}

const auto &vaddl_s8 = __vaddl<int8x8_t, int16x8_t>;
const auto &vaddl_s16 = __vaddl<int16x4_t, int32x4_t>;
const auto &vaddl_s32 = __vaddl<int32x2_t, int64x2_t>;

const auto &vaddl_u8 = __vaddl<uint8x8_t, uint16x8_t>;
const auto &vaddl_u16 = __vaddl<uint16x4_t, uint32x4_t>;
const auto &vaddl_u32 = __vaddl<uint32x2_t, uint64x2_t>;

template <typename R, typename T>
R __vaddw(R v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename R::elementType x = static_cast<typename R::elementType>(v2.template at<typename T::elementType>(i));
        result.template at<typename R::elementType>(i) = v1.template at<typename R::elementType>(i) + x;
    }
    return result;
}

template <typename T>
T __vhadd(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) /= 2;
    }
    return result;
}

template <typename T>
T __vrhadd(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = (v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i));
        if ((x >> 1) * 2 == x)
        {
            x = x >> 1;
        }
        else
        {
            x = (x >> 1) + 1;
        }
        result.template at<typename T::elementType>(i) = x;
    }
    return result;
}

template <typename T>
T __vqadd(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        auto x = v1.template at<typename T::elementType>(i);
        auto y = v2.template at<typename T::elementType>(i);
        if ((y > 0) && (x > std::numeric_limits<typename T::elementType>::max() - y))
        {
            result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        }
        else if ((x < 0) && (y < std::numeric_limits<typename T::elementType>::max() - y))
        {
            result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
        }
        else
        {
            result.template at<typename T::elementType>(i) = x + y;
        }
    }
    return result;
}

template <typename T, typename R>
R __vaddhn(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        auto x = v1.template at<typename T::elementType>(i);
        auto y = v2.template at<typename T::elementType>(i);
        auto temp = x + y;
        auto part = reinterpret_cast<typename R::elementType *>(&temp)[1];
        result.template at<typename R::elementType>(i) = part;
    }
    return result;
}

template <typename T, typename R>
R __vraddhn(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        auto x = v1.template at<typename T::elementType>(i);
        auto y = v2.template at<typename T::elementType>(i);
        typename T::elementType sum = 0;
        if ((x > 0) && (y > std::numeric_limits<typename T::elementType>::max() - x))
        {
            sum = std::numeric_limits<typename T::elementType>::max();
        }
        else if ((x < 0) && (y < std::numeric_limits<typename T::elementType>::min() - x))
        {
            sum = std::numeric_limits<typename T::elementType>::min();
        }
        else
        {
            sum = x + y;
        }
        auto part = reinterpret_cast<typename R::elementType *>(&sum)[1];
        result.template at<typename R::elementType>(i) = part;
    }
    return result;
}

const auto &vaddw_u8 = __vaddw<uint16x8_t, uint8x8_t>;
const auto &vaddw_u16 = __vaddw<uint32x4_t, uint16x4_t>;
const auto &vaddw_u32 = __vaddw<uint64x2_t, uint32x2_t>;

const auto &vaddw_s8 = __vaddw<int16x8_t, int8x8_t>;
const auto &vaddw_s16 = __vaddw<int32x4_t, int16x4_t>;
const auto &vaddw_s32 = __vaddw<int64x2_t, int32x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vaddhn ///////////////////////////////////////////////////////
const auto &vaddhn_s16 = __vaddhn<int16x8_t, int8x8_t>;
const auto &vaddhn_s32 = __vaddhn<int32x4_t, int16x4_t>;
const auto &vaddhn_s64 = __vaddhn<int64x2_t, int32x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vhadd - 64-bit vectors ///////////////////////////////////////////////////////
const auto &vhadd_u8 = __vhadd<uint8x8_t>;
const auto &vhadd_u16 = __vhadd<uint16x4_t>;
const auto &vhadd_u32 = __vhadd<uint32x2_t>;

const auto &vhadd_s8 = __vhadd<int16x8_t>;
const auto &vhadd_s16 = __vhadd<int32x4_t>;
const auto &vhadd_s32 = __vhadd<int64x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vhadd - 128-bit vectors ///////////////////////////////////////////////////////
const auto &vhaddq_u8 = __vhadd<uint8x16_t>;
const auto &vhaddq_u16 = __vhadd<uint16x8_t>;
const auto &vhaddq_u32 = __vhadd<uint32x4_t>;

const auto &vhaddq_s8 = __vhadd<int8x16_t>;
const auto &vhaddq_s16 = __vhadd<int16x8_t>;
const auto &vhaddq_s32 = __vhadd<int32x4_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vrhadd - 64-bit vectors ///////////////////////////////////////////////////////
const auto &vrhadd_u8 = __vrhadd<uint8x8_t>;
const auto &vrhadd_u16 = __vrhadd<uint16x4_t>;
const auto &vrhadd_u32 = __vrhadd<uint32x2_t>;

const auto &vrhadd_s8 = __vrhadd<int16x8_t>;
const auto &vrhadd_s16 = __vrhadd<int32x4_t>;
const auto &vrhadd_s32 = __vrhadd<int64x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vrhadd - 128-bit vectors ///////////////////////////////////////////////////////
const auto &vrhaddq_u8 = __vrhadd<uint8x16_t>;
const auto &vrhaddq_u16 = __vrhadd<uint16x8_t>;
const auto &vrhaddq_u32 = __vrhadd<uint32x4_t>;

const auto &vrhaddq_s8 = __vrhadd<int8x16_t>;
const auto &vrhaddq_s16 = __vrhadd<int16x8_t>;
const auto &vrhaddq_s32 = __vrhadd<int32x4_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vraddhn - 128-bit vectors ///////////////////////////////////////////////////////
const auto &vraddhn_u16 = __vraddhn<uint16x8_t, uint8x8_t>;
const auto &vraddhn_u32 = __vraddhn<uint32x4_t, uint16x4_t>;
const auto &vraddhn_u64 = __vraddhn<uint64x2_t, uint32x2_t>;

const auto &vraddhn_s16 = __vraddhn<int16x8_t, int8x8_t>;
const auto &vraddhn_s32 = __vraddhn<int32x4_t, int16x4_t>;
const auto &vraddhn_s64 = __vraddhn<int64x2_t, int32x2_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vqadd - 64-bit vectors ///////////////////////////////////////////////////////
const auto &vqadd_u8 = __vqadd<uint8x8_t>;
const auto &vqadd_u16 = __vqadd<uint16x4_t>;
const auto &vqadd_u32 = __vqadd<uint32x2_t>;
const auto &vqadd_u64 = __vqadd<uint64x1_t>;

const auto &vqadd_s8 = __vqadd<int8x8_t>;
const auto &vqadd_s16 = __vqadd<int16x4_t>;
const auto &vqadd_s32 = __vqadd<int32x2_t>;
const auto &vqadd_s64 = __vqadd<int64x1_t>;
///////////////////////////////////////////////////////////////////////////

// ARM NEON - vqadd - 128-bit vectors ///////////////////////////////////////////////////////
const auto &vqaddq_u8 = __vqadd<uint8x16_t>;
const auto &vqaddq_u16 = __vqadd<uint16x8_t>;
const auto &vqaddq_u32 = __vqadd<uint32x4_t>;
const auto &vqaddq_u64 = __vqadd<uint64x2_t>;

const auto &vqaddq_s8 = __vqadd<int8x16_t>;
const auto &vqaddq_s16 = __vqadd<int16x8_t>;
const auto &vqaddq_s32 = __vqadd<int32x4_t>;
const auto &vqaddq_s64 = __vqadd<int64x2_t>;

} // namespace iris::arm::addition
using namespace iris::arm::addition;
#endif