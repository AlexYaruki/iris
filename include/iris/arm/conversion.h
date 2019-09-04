#include "common.h"
#include <type_traits>

#ifndef IRIS_ARM_CONVERSION
#define IRIS_ARM_CONVERSION

namespace iris::arm::conversion
{

template <typename T, typename R>
typename std::enable_if<T::length == R::length, R>::type __vcvt(T v)
{
    R result;
    for (size_t i = 0; i < R::length; i++)
    {
        result.template at<typename R::elementType>(i) = static_cast<typename R::elementType>(v.template at<typename T::elementType>(i));
    }
    return result;
}

const auto &vcvt_f32_u32 = __vcvt<float32x2_t, uint32x2_t>;
const auto &vcvt_f32_s32 = __vcvt<float32x2_t, int32x2_t>;
const auto &vcvt_s32_f32 = __vcvt<int32x2_t, float32x2_t>;
const auto &vcvt_u32_f32 = __vcvt<uint32x2_t, float32x2_t>;

const auto &vcvtq_f32_u32 = __vcvt<float32x4_t, uint32x4_t>;
const auto &vcvtq_f32_s32 = __vcvt<float32x4_t, int32x4_t>;
const auto &vcvtq_s32_f32 = __vcvt<int32x4_t, float32x4_t>;
const auto &vcvtq_u32_f32 = __vcvt<uint32x4_t, float32x4_t>;

template <typename T, typename R>
typename std::enable_if<T::length == R::length, R>::type __vcvt_n(T v, int32_t x)
{
    T p = __vdup_lane<T, typename T::elementType>(v, x);
    return __vcvt<T, R>(p);
}

const auto &vcvt_n_f32_u32 = __vcvt_n<float32x2_t, uint32x2_t>;
const auto &vcvt_n_f32_s32 = __vcvt_n<float32x2_t, int32x2_t>;
const auto &vcvt_n_s32_f32 = __vcvt_n<int32x2_t, float32x2_t>;
const auto &vcvt_n_u32_f32 = __vcvt_n<uint32x2_t, float32x2_t>;

const auto &vcvtq_n_f32_u32 = __vcvt_n<float32x4_t, uint32x4_t>;
const auto &vcvtq_n_f32_s32 = __vcvt_n<float32x4_t, int32x4_t>;
const auto &vcvtq_n_s32_f32 = __vcvt_n<int32x4_t, float32x4_t>;
const auto &vcvtq_n_u32_f32 = __vcvt_n<uint32x4_t, float32x4_t>;

} // namespace iris::arm::conversion

using namespace iris::arm::conversion;

#endif