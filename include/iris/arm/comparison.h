#include "common.h"
#include "values.h"

#ifndef IRIS_ARM_COMPARISON
#define IRIS_ARM_COMPARISON

namespace iris::arm::comparison
{

template <typename T, typename R>
T __vtst(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType temp = v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i);
        if (temp == 0)
        {
            result.template at<typename T::elementType>(i) = 0;
        }
        else
        {
            result.template at<typename T::elementType>(i) = 1;
        }
    }
    return result;
}

const auto &vtst_u8 = __vtst<uint8x8_t, uint8x8_t>;
const auto &vtst_u16 = __vtst<uint16x4_t, uint16x4_t>;
const auto &vtst_u32 = __vtst<uint32x2_t, uint32x2_t>;

const auto &vtst_s8 = __vtst<int8x8_t, uint8x8_t>;
const auto &vtst_s16 = __vtst<int16x4_t, uint16x4_t>;
const auto &vtst_s32 = __vtst<int32x2_t, uint32x2_t>;

const auto &vtstq_u8 = __vtst<uint8x16_t, uint8x16_t>;
const auto &vtstq_u16 = __vtst<uint16x8_t, uint16x8_t>;
const auto &vtstq_u32 = __vtst<uint32x4_t, uint32x4_t>;

const auto &vtstq_s8 = __vtst<int8x16_t, uint8x16_t>;
const auto &vtstq_s16 = __vtst<int16x8_t, uint16x8_t>;
const auto &vtstq_s32 = __vtst<int32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vceq(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        if (v1.template at<typename T::elementType>(i) == v2.template at<typename T::elementType>(i))
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
        }
        else
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
        }
    }
    return result;
}

const auto &vceq_u8 = __vceq<uint8x8_t, uint8x8_t>;
const auto &vceq_u16 = __vceq<uint16x4_t, uint16x4_t>;
const auto &vceq_u32 = __vceq<uint32x2_t, uint32x2_t>;

const auto &vceq_s8 = __vceq<int8x8_t, uint8x8_t>;
const auto &vceq_s16 = __vceq<int16x4_t, uint16x4_t>;
const auto &vceq_s32 = __vceq<int32x2_t, uint32x2_t>;

const auto &vceq_f32 = __vceq<float32x2_t, uint32x2_t>;

const auto &vceqq_u8 = __vceq<uint8x16_t, uint8x16_t>;
const auto &vceqq_u16 = __vceq<uint16x8_t, uint16x8_t>;
const auto &vceqq_u32 = __vceq<uint32x4_t, uint32x4_t>;

const auto &vceqq_s8 = __vceq<int8x16_t, uint8x16_t>;
const auto &vceqq_s16 = __vceq<int16x8_t, uint16x8_t>;
const auto &vceqq_s32 = __vceq<int32x4_t, uint32x4_t>;

const auto &vceqq_f32 = __vceq<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcgt(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        if (v1.template at<typename T::elementType>(i) > v2.template at<typename T::elementType>(i))
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
        }
        else
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
        }
    }
    return result;
}

const auto &vcgt_u8 = __vcgt<uint8x8_t, uint8x8_t>;
const auto &vcgt_u16 = __vcgt<uint16x4_t, uint16x4_t>;
const auto &vcgt_u32 = __vcgt<uint32x2_t, uint32x2_t>;

const auto &vcgt_s8 = __vcgt<int8x8_t, uint8x8_t>;
const auto &vcgt_s16 = __vcgt<int16x4_t, uint16x4_t>;
const auto &vcgt_s32 = __vcgt<int32x2_t, uint32x2_t>;

const auto &vcgt_f32 = __vcgt<float32x2_t, uint32x2_t>;

const auto &vcgtq_u8 = __vcgt<uint8x16_t, uint8x16_t>;
const auto &vcgtq_u16 = __vcgt<uint16x8_t, uint16x8_t>;
const auto &vcgtq_u32 = __vcgt<uint32x4_t, uint32x4_t>;

const auto &vcgtq_s8 = __vcgt<int8x16_t, uint8x16_t>;
const auto &vcgtq_s16 = __vcgt<int16x8_t, uint16x8_t>;
const auto &vcgtq_s32 = __vcgt<int32x4_t, uint32x4_t>;

const auto &vcgtq_f32 = __vcgt<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcge(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        if (v1.template at<typename T::elementType>(i) >= v2.template at<typename T::elementType>(i))
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
        }
        else
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
        }
    }
    return result;
}

const auto &vcge_u8 = __vcge<uint8x8_t, uint8x8_t>;
const auto &vcge_u16 = __vcge<uint16x4_t, uint16x4_t>;
const auto &vcge_u32 = __vcge<uint32x2_t, uint32x2_t>;

const auto &vcge_s8 = __vcge<int8x8_t, uint8x8_t>;
const auto &vcge_s16 = __vcge<int16x4_t, uint16x4_t>;
const auto &vcge_s32 = __vcge<int32x2_t, uint32x2_t>;

const auto &vcge_f32 = __vcge<float32x2_t, uint32x2_t>;

const auto &vcgeq_u8 = __vcge<uint8x16_t, uint8x16_t>;
const auto &vcgeq_u16 = __vcge<uint16x8_t, uint16x8_t>;
const auto &vcgeq_u32 = __vcge<uint32x4_t, uint32x4_t>;

const auto &vcgeq_s8 = __vcge<int8x16_t, uint8x16_t>;
const auto &vcgeq_s16 = __vcge<int16x8_t, uint16x8_t>;
const auto &vcgeq_s32 = __vcge<int32x4_t, uint32x4_t>;

const auto &vcgeq_f32 = __vcge<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vclt(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        if (v1.template at<typename T::elementType>(i) < v2.template at<typename T::elementType>(i))
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
        }
        else
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
        }
    }
    return result;
}

const auto &vclt_u8 = __vclt<uint8x8_t, uint8x8_t>;
const auto &vclt_u16 = __vclt<uint16x4_t, uint16x4_t>;
const auto &vclt_u32 = __vclt<uint32x2_t, uint32x2_t>;

const auto &vclt_s8 = __vclt<int8x8_t, uint8x8_t>;
const auto &vclt_s16 = __vclt<int16x4_t, uint16x4_t>;
const auto &vclt_s32 = __vclt<int32x2_t, uint32x2_t>;

const auto &vclt_f32 = __vclt<float32x2_t, uint32x2_t>;

const auto &vcltq_u8 = __vclt<uint8x16_t, uint8x16_t>;
const auto &vcltq_u16 = __vclt<uint16x8_t, uint16x8_t>;
const auto &vcltq_u32 = __vclt<uint32x4_t, uint32x4_t>;

const auto &vcltq_s8 = __vclt<int8x16_t, uint8x16_t>;
const auto &vcltq_s16 = __vclt<int16x8_t, uint16x8_t>;
const auto &vcltq_s32 = __vclt<int32x4_t, uint32x4_t>;

const auto &vcltq_f32 = __vclt<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcle(T v1, T v2)
{
    R result;
    for (size_t i = 0; i < T::length; i++)
    {
        if (v1.template at<typename T::elementType>(i) <= v2.template at<typename T::elementType>(i))
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
        }
        else
        {
            result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
        }
    }
    return result;
}

const auto &vcle_u8 = __vcle<uint8x8_t, uint8x8_t>;
const auto &vcle_u16 = __vcle<uint16x4_t, uint16x4_t>;
const auto &vcle_u32 = __vcle<uint32x2_t, uint32x2_t>;

const auto &vcle_s8 = __vcle<int8x8_t, uint8x8_t>;
const auto &vcle_s16 = __vcle<int16x4_t, uint16x4_t>;
const auto &vcle_s32 = __vcle<int32x2_t, uint32x2_t>;

const auto &vcle_f32 = __vcle<float32x2_t, uint32x2_t>;

const auto &vcleq_u8 = __vcle<uint8x16_t, uint8x16_t>;
const auto &vcleq_u16 = __vcle<uint16x8_t, uint16x8_t>;
const auto &vcleq_u32 = __vcle<uint32x4_t, uint32x4_t>;

const auto &vcleq_s8 = __vcle<int8x16_t, uint8x16_t>;
const auto &vcleq_s16 = __vcle<int16x8_t, uint16x8_t>;
const auto &vcleq_s32 = __vcle<int32x4_t, uint32x4_t>;

const auto &vcleq_f32 = __vcle<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcale(T v1, T v2)
{
    return __vcle<T, R>(__vabs<T>(v1), __vabs<T>(v2));
}

const auto &vcale_f32 = __vcale<float32x2_t, uint32x2_t>;

const auto &vcaleq_f32 = __vcale<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcagt(T v1, T v2)
{
    return __vcgt<T, R>(__vabs<T>(v1), __vabs<T>(v2));
}

const auto &vcagt_f32 = __vcagt<float32x2_t, uint32x2_t>;

const auto &vcagtq_f32 = __vcagt<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcage(T v1, T v2)
{
    return __vcge<T, R>(__vabs<T>(v1), __vabs<T>(v2));
}

const auto &vcage_f32 = __vcage<float32x2_t, uint32x2_t>;

const auto &vcageq_f32 = __vcage<float32x4_t, uint32x4_t>;

template <typename T, typename R>
R __vcalt(T v1, T v2)
{
    return __vclt<T, R>(__vabs<T>(v1), __vabs<T>(v2));
}

const auto &vcalt_f32 = __vcalt<float32x2_t, uint32x2_t>;

const auto &vcaltq_f32 = __vcalt<float32x4_t, uint32x4_t>;

} // namespace iris::arm::comparison

using namespace iris::arm::comparison;

#endif