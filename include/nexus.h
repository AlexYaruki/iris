#ifndef NEXUS_H
#define NEXUS_H

#include <cstdint>

namespace nexus {

    template<typename T, size_t len>
    struct vector {
        using elementType = T;
        const static auto length = len;
            int8_t value_s8[sizeof(T) * length];

        template<typename E>
        E& at(size_t i) {
            return reinterpret_cast<E*>(&value_s8)[i];
        }

    };

    template<typename T, typename E>
    T __vdup(E elem) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<typename T::elementType>(i) = elem;
        }
        return result;
    }

    template<typename T, typename E>
    E __vget_lane(T v, size_t i) {
        return v.template at<E>(i);
    }

    template<typename T, typename E>
    T __vdup_lane(T v, size_t i) {
        return __vdup<T,E>(__vget_lane<T,E>(v,i));
    }

    template<typename T>
    T __vadd(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i);
        }
        return result;
    }

    template<typename T, typename R>
    R __vaddl(T v1, T v2) {
        R result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<typename R::elementType>(i) = (typename R::elementType)v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i);
        }
        return result;
    }


    template<typename T>
    T __vmul(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) * v2.template at<typename T::elementType>(i);
        }
        return result;
    }

    // ARM NEON - Types

    using int8_8_t  = vector<int8_t,8>;
    using int16_4_t = vector<int16_t,4>;
    using int32_2_t = vector<int32_t,2>;
    using int64_1_t = vector<int64_t,1>;

    using uint8_8_t  = vector<uint8_t,8>;
    using uint16_4_t = vector<uint16_t,4>;
    using uint32_2_t = vector<uint32_t,2>;
    using uint64_1_t = vector<uint64_t,1>;

    using int8_16_t = vector<int8_t,16>;
    using int16_8_t = vector<int16_t,8>;
    using int32_4_t = vector<int32_t,4>;
    using int64_2_t = vector<int64_t,2>;

    using uint8_16_t = vector<uint8_t,16>;
    using uint16_8_t = vector<uint16_t,8>;
    using uint32_4_t = vector<uint32_t,4>;
    using uint64_2_t = vector<uint64_t,2>;

    using float32_2_t = vector<float,2>;
    using float32_4_t = vector<float,4>;

    // ARM NEON - vdup/vmov - 64-bit vector ///////////////////////////////////
    const auto& vdup_n_s8  = __vdup<int8_8_t ,int8_t >;
    const auto& vdup_n_s16 = __vdup<int16_4_t,int16_t>;
    const auto& vdup_n_s32 = __vdup<int32_2_t,int32_t>;
    const auto& vdup_n_s64 = __vdup<int64_1_t,int64_t>;

    const auto& vmov_n_s8  = __vdup<int8_8_t ,int8_t >;
    const auto& vmov_n_s16 = __vdup<int16_4_t,int16_t>;
    const auto& vmov_n_s32 = __vdup<int32_2_t,int32_t>;
    const auto& vmov_n_s64 = __vdup<int64_1_t,int64_t>;

    const auto& vdup_n_u8  = __vdup<uint8_8_t ,uint8_t>;
    const auto& vdup_n_u16 = __vdup<uint16_4_t,uint16_t>;
    const auto& vdup_n_u32 = __vdup<uint32_2_t,uint32_t>;
    const auto& vdup_n_u64 = __vdup<uint64_1_t,uint64_t>;

    const auto& vmov_n_u8  = __vdup<uint8_8_t ,uint8_t>;
    const auto& vmov_n_u16 = __vdup<uint16_4_t,uint16_t>;
    const auto& vmov_n_u32 = __vdup<uint32_2_t,uint32_t>;
    const auto& vmov_n_u64 = __vdup<uint64_1_t,uint64_t>;

    const auto& vdup_n_f32 = __vdup<float32_2_t,float>;
    const auto& vmov_n_f32 = __vdup<float32_2_t,float>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vdup/vmov - 128-bit vector ///////////////////////////////////
    const auto& vdupq_n_s8  = __vdup<int8_16_t ,int8_t>;
    const auto& vdupq_n_s16 = __vdup<int16_8_t,int16_t>;
    const auto& vdupq_n_s32 = __vdup<int32_4_t,int32_t>;
    const auto& vdupq_n_s64 = __vdup<int64_2_t,int64_t>;

    const auto& vmovq_n_s8  = __vdup<int8_16_t ,int8_t>;
    const auto& vmovq_n_s16 = __vdup<int16_8_t,int16_t>;
    const auto& vmovq_n_s32 = __vdup<int32_4_t,int32_t>;
    const auto& vmovq_n_s64 = __vdup<int64_2_t,int64_t>;

    const auto& vdupq_n_u8  = __vdup<uint8_16_t ,uint8_t>;
    const auto& vdupq_n_u16 = __vdup<uint16_8_t,uint16_t>;
    const auto& vdupq_n_u32 = __vdup<uint32_4_t,uint32_t>;
    const auto& vdupq_n_u64 = __vdup<uint64_2_t,uint64_t>;

    const auto& vmovq_n_u8  = __vdup<uint8_16_t ,uint8_t>;
    const auto& vmovq_n_u16 = __vdup<uint16_8_t,uint16_t>;
    const auto& vmovq_n_u32 = __vdup<uint32_4_t,uint32_t>;
    const auto& vmovq_n_u64 = __vdup<uint64_2_t,uint64_t>;

    const auto& vdupq_n_f32 = __vdup<float32_4_t,float>;
    const auto& vmovq_n_f32 = __vdup<float32_4_t,float>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vget_lane - 64-bit vectors //////////////////////////////////
    const auto& vget_lane_s8  = __vget_lane<int8_8_t,  int8_t>;
    const auto& vget_lane_s16 = __vget_lane<int16_4_t, int16_t>;
    const auto& vget_lane_s32 = __vget_lane<int32_2_t, int32_t>;
    const auto& vget_lane_s64 = __vget_lane<int64_1_t, int64_t>;

    const auto& vget_lane_u8  = __vget_lane<uint8_8_t,  uint8_t>;
    const auto& vget_lane_u16 = __vget_lane<uint16_4_t, uint16_t>;
    const auto& vget_lane_u32 = __vget_lane<uint32_2_t, uint32_t>;
    const auto& vget_lane_u64 = __vget_lane<uint64_1_t, uint64_t>;

    const auto& vget_lane_f32 = __vget_lane<uint64_1_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vget_lane - 128-bit vectors //////////////////////////////////
    const auto& vgetq_lane_s8  = __vget_lane<int8_16_t,  int8_t>;
    const auto& vgetq_lane_s16 = __vget_lane<int16_8_t, int16_t>;
    const auto& vgetq_lane_s32 = __vget_lane<int32_4_t, int32_t>;
    const auto& vgetq_lane_s64 = __vget_lane<int64_2_t, int64_t>;

    const auto& vgetq_lane_u8  = __vget_lane<uint8_16_t,  uint8_t>;
    const auto& vgetq_lane_u16 = __vget_lane<uint16_8_t, uint16_t>;
    const auto& vgetq_lane_u32 = __vget_lane<uint32_4_t, uint32_t>;
    const auto& vgetq_lane_u64 = __vget_lane<uint64_2_t, uint64_t>;

    const auto& vgetq_lane_f32 = __vget_lane<uint64_2_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vdup_lane - 64-bit vectors //////////////////////////////////
    const auto& vdup_lane_s8  = __vdup_lane<int8_8_t,  int8_t>;
    const auto& vdup_lane_s16 = __vdup_lane<int16_4_t, int16_t>;
    const auto& vdup_lane_s32 = __vdup_lane<int32_2_t, int32_t>;
    const auto& vdup_lane_s64 = __vdup_lane<int64_1_t, int64_t>;

    const auto& vdup_lane_u8  = __vdup_lane<uint8_8_t,  uint8_t>;
    const auto& vdup_lane_u16 = __vdup_lane<uint16_4_t, uint16_t>;
    const auto& vdup_lane_u32 = __vdup_lane<uint32_2_t, uint32_t>;
    const auto& vdup_lane_u64 = __vdup_lane<uint64_1_t, uint64_t>;

    const auto& vdup_lane_f32 = __vdup_lane<uint64_1_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vdup_lane - 128-bit vectors /////////////////////////////////
    const auto& vdupq_lane_s8  = __vdup_lane<int8_16_t,  int8_t>;
    const auto& vdupq_lane_s16 = __vdup_lane<int16_8_t, int16_t>;
    const auto& vdupq_lane_s32 = __vdup_lane<int32_4_t, int32_t>;
    const auto& vdupq_lane_s64 = __vdup_lane<int64_2_t, int64_t>;

    const auto& vdupq_lane_u8  = __vdup_lane<uint8_16_t,  uint8_t>;
    const auto& vdupq_lane_u16 = __vdup_lane<uint16_8_t, uint16_t>;
    const auto& vdupq_lane_u32 = __vdup_lane<uint32_4_t, uint32_t>;
    const auto& vdupq_lane_u64 = __vdup_lane<uint64_2_t, uint64_t>;

    const auto& vdupq_lane_f32 = __vdup_lane<uint64_2_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vadd - 64-bit vectors ///////////////////////////////////////
    const auto& vadd_u8  = __vadd< uint8_8_t>;
    const auto& vadd_u16 = __vadd<uint16_4_t>;
    const auto& vadd_u32 = __vadd<uint32_2_t>;
    const auto& vadd_u64 = __vadd<uint64_1_t>;

    const auto& vadd_s8  = __vadd<  int8_8_t>;
    const auto& vadd_s16 = __vadd< int16_4_t>;
    const auto& vadd_s32 = __vadd< int32_2_t>;
    const auto& vadd_s64 = __vadd< int64_1_t>;

    const auto& vadd_f32 = __vmul<float32_2_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vadd - 128-bit vectors ///////////////////////////////////////
    const auto& vaddq_u8  = __vadd<uint8_16_t>;
    const auto& vaddq_u16 = __vadd<uint16_8_t>;
    const auto& vaddq_u32 = __vadd<uint32_4_t>;
    const auto& vaddq_u64 = __vadd<uint64_2_t>;

    const auto& vaddq_s8  = __vadd< int8_16_t>;
    const auto& vaddq_s16 = __vadd< int16_8_t>;
    const auto& vaddq_s32 = __vadd< int32_4_t>;
    const auto& vaddq_s64 = __vadd< int64_2_t>;

    const auto& vaddq_f32 = __vmul<float32_4_t>;
    ///////////////////////////////////////////////////////////////////////////

    const auto& vaddl_s8  = __vaddl< int8_8_t,int16_8_t>;
    const auto& vaddl_s16 = __vaddl<int16_4_t,int32_4_t>;
    const auto& vaddl_s32 = __vaddl<int32_2_t,int64_2_t>;

    const auto& vaddl_u8  = __vaddl< uint8_8_t,uint16_8_t>;
    const auto& vaddl_u16 = __vaddl<uint16_4_t,uint32_4_t>;
    const auto& vaddl_u32 = __vaddl<uint32_2_t,uint64_2_t>;

}

#endif

/*
template<typename T, typename R>
R __vaddl(T v1, T v2) {
*/
