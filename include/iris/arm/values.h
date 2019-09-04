#include "common.h"
#include <cmath>

#ifndef IRIS_ARM_VALUES
#define IRIS_ARM_VALUES

namespace iris::arm::values
{
template <typename T>
T __vneg(T v)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = v.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) = -x;
    }
    return result;
}

const auto &vneg_s8 = __vneg<int8x8_t>;
const auto &vneg_s16 = __vneg<int16x4_t>;
const auto &vneg_s32 = __vneg<int32x2_t>;
const auto &vneg_f32 = __vneg<float32x2_t>;

const auto &vnegq_s8 = __vneg<int8x16_t>;
const auto &vnegq_s16 = __vneg<int16x8_t>;
const auto &vnegq_s32 = __vneg<int32x4_t>;
const auto &vnegq_f32 = __vneg<float32x4_t>;

template <typename T>
T __vqneg(T v)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = v.template at<typename T::elementType>(i);
        if (x == std::numeric_limits<typename T::elementType>::min())
        {
            x = -std::numeric_limits<typename T::elementType>::max();
        }
        else
        {
            x = -x;
        }
        result.template at<typename T::elementType>(i) = x;
    }
    return result;
}

const auto &vqneg_s8 = __vqneg<int8x8_t>;
const auto &vqneg_s16 = __vqneg<int16x4_t>;
const auto &vqneg_s32 = __vqneg<int32x2_t>;

const auto &vqnegq_s8 = __vqneg<int8x16_t>;
const auto &vqnegq_s16 = __vqneg<int16x8_t>;
const auto &vqnegq_s32 = __vqneg<int32x4_t>;

template <typename T>
T __iris__abs(T x)
{
    if (x < 0)
    {
        return x * static_cast<T>(-1);
    }
    else
    {
        return x;
    }
}

template <>
float __iris__abs(float x)
{
    return std::fabs(x);
}

template <typename T>
T __vabs(T v)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = v.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) = __iris__abs(x);
    }
    return result;
}

template <typename T>
T __iris__qabs(T x)
{
    if (x < 0)
    {
        T temp = x * static_cast<T>(-1);
        if (temp > x)
        {
            return temp;
        }
        else
        {
            return std::numeric_limits<T>::max();
        }
    }
    else
    {
        return x;
    }
}

const auto &vabs_s8 = __vabs<int8x8_t>;
const auto &vabs_s16 = __vabs<int16x4_t>;
const auto &vabs_s32 = __vabs<int32x2_t>;
const auto &vabs_f32 = __vabs<float32x2_t>;

const auto &vabsq_s8 = __vabs<int8x16_t>;
const auto &vabsq_s16 = __vabs<int16x8_t>;
const auto &vabsq_s32 = __vabs<int32x4_t>;
const auto &vabsq_f32 = __vabs<float32x4_t>;

template <typename T>
T __vmax(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) > v2.template at<typename T::elementType>(i) ? v1.template at<typename T::elementType>(i) : v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vmax_u8 = __vmax<uint8x8_t>;
const auto &vmax_u16 = __vmax<uint16x4_t>;
const auto &vmax_u32 = __vmax<uint32x2_t>;

const auto &vmax_s8 = __vmax<int8x8_t>;
const auto &vmax_s16 = __vmax<int16x4_t>;
const auto &vmax_s32 = __vmax<int32x2_t>;

const auto &vmax_f32 = __vmax<float32x2_t>;

const auto &vmaxq_u8 = __vmax<uint8x16_t>;
const auto &vmaxq_u16 = __vmax<uint16x8_t>;
const auto &vmaxq_u32 = __vmax<uint32x4_t>;

const auto &vmaxq_s8 = __vmax<int8x16_t>;
const auto &vmaxq_s16 = __vmax<int16x8_t>;
const auto &vmaxq_s32 = __vmax<int32x4_t>;

const auto &vmaxq_f32 = __vmax<float32x4_t>;

template <typename T>
T __vmin(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) < v2.template at<typename T::elementType>(i) ? v1.template at<typename T::elementType>(i) : v2.template at<typename T::elementType>(i);
    }
    return result;
}

const auto &vmin_u8 = __vmin<uint8x8_t>;
const auto &vmin_u16 = __vmin<uint16x4_t>;
const auto &vmin_u32 = __vmin<uint32x2_t>;

const auto &vmin_s8 = __vmin<int8x8_t>;
const auto &vmin_s16 = __vmin<int16x4_t>;
const auto &vmin_s32 = __vmin<int32x2_t>;

const auto &vmin_f32 = __vmin<float32x2_t>;

const auto &vminq_u8 = __vmin<uint8x16_t>;
const auto &vminq_u16 = __vmin<uint16x8_t>;
const auto &vminq_u32 = __vmin<uint32x4_t>;

const auto &vminq_s8 = __vmin<int8x16_t>;
const auto &vminq_s16 = __vmin<int16x8_t>;
const auto &vminq_s32 = __vmin<int32x4_t>;

const auto &vminq_f32 = __vmin<float32x4_t>;

template <typename T>
T __vqabs(T v)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        typename T::elementType x = v.template at<typename T::elementType>(i);
        result.template at<typename T::elementType>(i) = __iris__qabs(x);
    }
    return result;
}

const auto &vqabs_s8 = __vqabs<int8x8_t>;
const auto &vqabs_s16 = __vqabs<int16x4_t>;
const auto &vqabs_s32 = __vqabs<int32x2_t>;
const auto &vqabs_f32 = __vqabs<float32x2_t>;

const auto &vqabsq_s8 = __vqabs<int8x16_t>;
const auto &vqabsq_s16 = __vqabs<int16x8_t>;
const auto &vqabsq_s32 = __vqabs<int32x4_t>;
const auto &vqabsq_f32 = __vqabs<float32x4_t>;

} // namespace iris::arm::values

using namespace iris::arm::values;

#endif