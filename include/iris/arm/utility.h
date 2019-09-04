#include "common.h"

#ifndef IRIS_ARM_UTILITY
#define IRIS_ARM_UTILITY

namespace iris::arm::utility
{

template <typename T>
T __vrev64(typename std::enable_if<sizeof(typename T::elementType) < 8, T>::type v)
{
    T result;
    const size_t packs = (T::length * sizeof(typename T::elementType)) / 8;
    const size_t elementsPerPack = T::length / packs;
    for (size_t j = 0; j < packs; j++)
    {
        for (size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j + 1); i++, k++)
        {
            result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>((elementsPerPack * (j + 1)) - (k + 1));
        }
    }
    return result;
}

const auto &vrev64_s8 = __vrev64<int8x8_t>;
const auto &vrev64_s16 = __vrev64<int16x4_t>;
const auto &vrev64_s32 = __vrev64<int32x2_t>;

const auto &vrev64_u8 = __vrev64<uint8x8_t>;
const auto &vrev64_u16 = __vrev64<uint16x4_t>;
const auto &vrev64_u32 = __vrev64<uint32x2_t>;

const auto &vrev64_f32 = __vrev64<float32x2_t>;

const auto &vrev64q_s8 = __vrev64<int8x16_t>;
const auto &vrev64q_s16 = __vrev64<int16x8_t>;
const auto &vrev64q_s32 = __vrev64<int32x4_t>;

const auto &vrev64q_u8 = __vrev64<uint8x16_t>;
const auto &vrev64q_u16 = __vrev64<uint16x8_t>;
const auto &vrev64q_u32 = __vrev64<uint32x4_t>;

const auto &vrev64q_f32 = __vrev64<float32x4_t>;

template <typename T>
T __vrev32(typename std::enable_if<sizeof(typename T::elementType) < 4, T>::type v)
{
    T result;
    const size_t packs = (T::length * sizeof(typename T::elementType)) / 4;
    const size_t elementsPerPack = T::length / packs;
    for (size_t j = 0; j < packs; j++)
    {
        for (size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j + 1); i++, k++)
        {
            result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>((elementsPerPack * (j + 1)) - (k + 1));
        }
    }
    return result;
}

const auto &vrev32_s8 = __vrev32<int8x8_t>;
const auto &vrev32_s16 = __vrev32<int16x4_t>;

const auto &vrev32_u8 = __vrev32<uint8x8_t>;
const auto &vrev32_u16 = __vrev32<uint16x4_t>;
const auto &vrev32q_s8 = __vrev32<int8x16_t>;
const auto &vrev32q_s16 = __vrev32<int16x8_t>;

const auto &vrev32q_u8 = __vrev32<uint8x16_t>;
const auto &vrev32q_u16 = __vrev32<uint16x8_t>;

template <typename T>
T __vrev16(typename std::enable_if<sizeof(typename T::elementType) < 2, T>::type v)
{
    T result;
    const size_t packs = (T::length * sizeof(typename T::elementType)) / 2;
    const size_t elementsPerPack = T::length / packs;
    for (size_t j = 0; j < packs; j++)
    {
        for (size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j + 1); i++, k++)
        {
            result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>((elementsPerPack * (j + 1)) - (k + 1));
        }
    }
    return result;
}

const auto &vrev16_s8 = __vrev16<int8x8_t>;
const auto &vrev16_u8 = __vrev16<uint8x8_t>;

const auto &vrev16q_s8 = __vrev16<int8x16_t>;
const auto &vrev16q_u8 = __vrev16<uint8x16_t>;

template <typename T>
T __vext(T v1, T v2, int32_t n)
{
    T result;
    for (int32_t i = 0; i <= n; i++)
    {
        result.template at<typename T::elementType>(i) = v2.template at<typename T::elementType>(i);
    }
    for (int32_t i = n + 1, j = T::length - 1; (size_t)i < T::length; i++, j--)
    {
        result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(j);
    }
    return result;
}

const auto &vext_s8 = __vext<int8x8_t>;
const auto &vext_s16 = __vext<int16x4_t>;
const auto &vext_s32 = __vext<int32x2_t>;
const auto &vext_s64 = __vext<int64x1_t>;

const auto &vext_u8 = __vext<uint8x8_t>;
const auto &vext_u16 = __vext<uint16x4_t>;
const auto &vext_u32 = __vext<uint32x2_t>;
const auto &vext_u64 = __vext<uint64x1_t>;

const auto &vextq_s8 = __vext<int8x16_t>;
const auto &vextq_s16 = __vext<int16x8_t>;
const auto &vextq_s32 = __vext<int32x4_t>;
const auto &vextq_s64 = __vext<int64x2_t>;

const auto &vextq_u8 = __vext<uint8x16_t>;
const auto &vextq_u16 = __vext<uint16x8_t>;
const auto &vextq_u32 = __vext<uint32x4_t>;
const auto &vextq_u64 = __vext<uint64x2_t>;

} // namespace iris::arm::utility

using namespace iris::arm::utility;

#endif