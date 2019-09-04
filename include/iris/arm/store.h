#include "common.h"

#ifndef IRIS_ARM_STORE
#define IRIS_ARM_STORE

namespace iris::arm::store
{
template <typename T>
void __vst1(typename T::elementType *dst, T v)
{
    std::memcpy(dst, &v, sizeof(T));
}

const auto &vst1_u8 = __vst1<uint8x8_t>;
const auto &vst1_u16 = __vst1<uint16x4_t>;
const auto &vst1_u32 = __vst1<uint32x2_t>;
const auto &vst1_u64 = __vst1<uint64x1_t>;

const auto &vst1_s8 = __vst1<int8x8_t>;
const auto &vst1_s16 = __vst1<int16x4_t>;
const auto &vst1_s32 = __vst1<int32x2_t>;
const auto &vst1_s64 = __vst1<int64x1_t>;

const auto &vst1_f32 = __vst1<float32x2_t>;

const auto &vst1q_u8 = __vst1<uint8x16_t>;
const auto &vst1q_u16 = __vst1<uint16x8_t>;
const auto &vst1q_u32 = __vst1<uint32x4_t>;
const auto &vst1q_u64 = __vst1<uint64x2_t>;

const auto &vst1q_s8 = __vst1<int8x16_t>;
const auto &vst1q_s16 = __vst1<int16x8_t>;
const auto &vst1q_s32 = __vst1<int32x4_t>;
const auto &vst1q_s64 = __vst1<int64x2_t>;

const auto &vst1q_f32 = __vst1<float32x4_t>;

template <typename T>
void __vst1_lane(typename T::elementType *dst, T v, int pos)
{
    *dst = v.template at<typename T::elementType>(pos);
}

const auto &vst1_lane_u8 = __vst1_lane<uint8x8_t>;
const auto &vst1_lane_u16 = __vst1_lane<uint16x4_t>;
const auto &vst1_lane_u32 = __vst1_lane<uint32x2_t>;
const auto &vst1_lane_u64 = __vst1_lane<uint64x1_t>;

const auto &vst1_lane_s8 = __vst1_lane<int8x8_t>;
const auto &vst1_lane_s16 = __vst1_lane<int16x4_t>;
const auto &vst1_lane_s32 = __vst1_lane<int32x2_t>;
const auto &vst1_lane_s64 = __vst1_lane<int64x1_t>;

const auto &vst1_lane_f32 = __vst1_lane<float32x2_t>;

const auto &vst1q_lane_u8 = __vst1_lane<uint8x16_t>;
const auto &vst1q_lane_u16 = __vst1_lane<uint16x8_t>;
const auto &vst1q_lane_u32 = __vst1_lane<uint32x4_t>;
const auto &vst1q_lane_u64 = __vst1_lane<uint64x2_t>;

const auto &vst1q_lane_s8 = __vst1_lane<int8x16_t>;
const auto &vst1q_lane_s16 = __vst1_lane<int16x8_t>;
const auto &vst1q_lane_s32 = __vst1_lane<int32x4_t>;
const auto &vst1q_lane_s64 = __vst1_lane<int64x2_t>;

const auto &vst1q_lane_f32 = __vst1_lane<float32x4_t>;

} // namespace iris::arm::store

using namespace iris::arm::store;

#endif
