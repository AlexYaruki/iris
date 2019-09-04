#include "common.h"
#ifndef IRIS_ARM_SUBSTRACTION
#define IRIS_ARM_SUBSTRACTION

namespace iris::arm::substraction
{

template <typename T>
T __vsub(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vsub_u8 = __vsub<uint8x8_t>;
const auto &vsub_u16 = __vsub<uint16x4_t>;
const auto &vsub_u32 = __vsub<uint32x2_t>;
const auto &vsub_u64 = __vsub<uint64x1_t>;

const auto &vsub_s8 = __vsub<int8x8_t>;
const auto &vsub_s16 = __vsub<int16x4_t>;
const auto &vsub_s32 = __vsub<int32x2_t>;
const auto &vsub_s64 = __vsub<int64x1_t>;

const auto &vsub_f32 = __vsub<float32x2_t>;

const auto &vsubq_u8 = __vsub<uint8x16_t>;
const auto &vsubq_u16 = __vsub<uint16x8_t>;
const auto &vsubq_u32 = __vsub<uint32x4_t>;
const auto &vsubq_u64 = __vsub<uint64x2_t>;

const auto &vsubq_s8 = __vsub<int8x16_t>;
const auto &vsubq_s16 = __vsub<int16x8_t>;
const auto &vsubq_s32 = __vsub<int32x4_t>;
const auto &vsubq_s64 = __vsub<int64x2_t>;

const auto &vsubq_f32 = __vsub<float32x4_t>;

template <typename T, typename R>
R __vsubl(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename R::elementType>(i) = (typename R::elementType)v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vsubl_s8 = __vsubl<int8x8_t, int16x8_t>;
const auto &vsubl_s16 = __vsubl<int16x4_t, int32x4_t>;
const auto &vsubl_s32 = __vsubl<int32x2_t, int64x2_t>;

const auto &vsubl_u8 = __vsubl<uint8x8_t, uint16x8_t>;
const auto &vsubl_u16 = __vsubl<uint16x4_t, uint32x4_t>;
const auto &vsubl_u32 = __vsubl<uint32x2_t, uint64x2_t>;

template <typename T, typename R>
R __vsubw(R v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename R::elementType>(i) = v1.template at<typename R::elementType>(i) - v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vsubw_u8 = __vsubw<uint16x8_t, uint8x8_t>;
const auto &vsubw_u16 = __vsubw<uint32x4_t, uint16x4_t>;
const auto &vsubw_u32 = __vsubw<uint64x2_t, uint32x2_t>;

const auto &vsubw_s8 = __vsubw<int16x8_t, int8x8_t>;
const auto &vsubw_s16 = __vsubw<int32x4_t, int16x4_t>;
const auto &vsubw_s32 = __vsubw<int64x2_t, int32x2_t>;

template <typename T>
T __vhsub(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) /= 2;
    }
    return result;
}

const auto &vhsub_u8 = __vhsub<uint8x8_t>;
const auto &vhsub_u16 = __vhsub<uint16x4_t>;
const auto &vhsub_u32 = __vhsub<uint32x2_t>;

const auto &vhsub_s8 = __vhsub<int16x8_t>;
const auto &vhsub_s16 = __vhsub<int32x4_t>;
const auto &vhsub_s32 = __vhsub<int64x2_t>;

const auto &vhsubq_u8 = __vhsub<uint8x16_t>;
const auto &vhsubq_u16 = __vhsub<uint16x8_t>;
const auto &vhsubq_u32 = __vhsub<uint32x4_t>;

const auto &vhsubq_s8 = __vhsub<int8x16_t>;
const auto &vhsubq_s16 = __vhsub<int16x8_t>;
const auto &vhsubq_s32 = __vhsub<int32x4_t>;

template <typename T>
T __vqsub(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        auto x = v1.template at<typename T::elementType>(i);
        auto y = v2.template at<typename T::elementType>(i);
        if ((y > 0) && (x < std::numeric_limits<typename T::elementType>::min() + y))
        {
            result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
        }
        else if ((y < 0) && (x > std::numeric_limits<typename T::elementType>::max() + y))
        {
            result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
        }
        else
        {
            result.template at<typename T::elementType>(i) = x - y;
        }
    }
    return result;
}

const auto &vqsub_u8 = __vqsub<uint8x8_t>;
const auto &vqsub_u16 = __vqsub<uint16x4_t>;
const auto &vqsub_u32 = __vqsub<uint32x2_t>;
const auto &vqsub_u64 = __vqsub<uint64x1_t>;

const auto &vqsub_s8 = __vqsub<int8x8_t>;
const auto &vqsub_s16 = __vqsub<int16x4_t>;
const auto &vqsub_s32 = __vqsub<int32x2_t>;
const auto &vqsub_s64 = __vqsub<int64x1_t>;

const auto &vqsubq_u8 = __vqsub<uint8x16_t>;
const auto &vqsubq_u16 = __vqsub<uint16x8_t>;
const auto &vqsubq_u32 = __vqsub<uint32x4_t>;
const auto &vqsubq_u64 = __vqsub<uint64x2_t>;

const auto &vqsubq_s8 = __vqsub<int8x16_t>;
const auto &vqsubq_s16 = __vqsub<int16x8_t>;
const auto &vqsubq_s32 = __vqsub<int32x4_t>;
const auto &vqsubq_s64 = __vqsub<int64x2_t>;

} 

using namespace iris::arm::substraction;

#endif