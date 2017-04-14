#ifndef NEXUS_H
#define NEXUS_H

#include <cstdint>
#include <limits>

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
    template<typename T, typename R>
    R __vceq(T v1, T v2) {
        R result;
        for(size_t i = 0; T::length; i++) {
            if(v1.template at<typename T::elementType>(i) == v2.template at<typename T::elementType>(i)) {
                result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
            } else {
                result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
            }
        }
    }

    template<typename T>
    T __vadd(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i);
        }
        return result;
    }
    
    template<typename T>
    T __vsub(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
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

    
    
    
    // ARM NEON - Types - 64-bit

    using int8x8_t  = vector<int8_t,8>;
    using int16x4_t = vector<int16_t,4>;
    using int32x2_t = vector<int32_t,2>;
    using int64x1_t = vector<int64_t,1>;

    using uint8x8_t  = vector<uint8_t,8>;
    using uint16x4_t = vector<uint16_t,4>;
    using uint32x2_t = vector<uint32_t,2>;
    using uint64x1_t = vector<uint64_t,1>;

    using float32x2_t = vector<float,2>;
    
    // ARM NEON - Types - 128-bit
    
    using int8x16_t = vector<int8_t,16>;
    using int16x8_t = vector<int16_t,8>;
    using int32x4_t = vector<int32_t,4>;
    using int64x2_t = vector<int64_t,2>;

    using uint8x16_t = vector<uint8_t,16>;
    using uint16x8_t = vector<uint16_t,8>;
    using uint32x4_t = vector<uint32_t,4>;
    using uint64x2_t = vector<uint64_t,2>;

    using float32x4_t = vector<float,4>;
    
    // ARM NEON - vdup/vmov - 64-bit vector ///////////////////////////////////
    const auto& vdup_n_s8  = __vdup<int8x8_t ,int8_t >;
    const auto& vdup_n_s16 = __vdup<int16x4_t,int16_t>;
    const auto& vdup_n_s32 = __vdup<int32x2_t,int32_t>;
    const auto& vdup_n_s64 = __vdup<int64x1_t,int64_t>;

    const auto& vmov_n_s8  = __vdup<int8x8_t ,int8_t >;
    const auto& vmov_n_s16 = __vdup<int16x4_t,int16_t>;
    const auto& vmov_n_s32 = __vdup<int32x2_t,int32_t>;
    const auto& vmov_n_s64 = __vdup<int64x1_t,int64_t>;

    const auto& vdup_n_u8  = __vdup<uint8x8_t ,uint8_t>;
    const auto& vdup_n_u16 = __vdup<uint16x4_t,uint16_t>;
    const auto& vdup_n_u32 = __vdup<uint32x2_t,uint32_t>;
    const auto& vdup_n_u64 = __vdup<uint64x1_t,uint64_t>;

    const auto& vmov_n_u8  = __vdup<uint8x8_t ,uint8_t>;
    const auto& vmov_n_u16 = __vdup<uint16x4_t,uint16_t>;
    const auto& vmov_n_u32 = __vdup<uint32x2_t,uint32_t>;
    const auto& vmov_n_u64 = __vdup<uint64x1_t,uint64_t>;

    const auto& vdup_n_f32 = __vdup<float32x2_t,float>;
    const auto& vmov_n_f32 = __vdup<float32x2_t,float>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vdup/vmov - 128-bit vector ///////////////////////////////////
    const auto& vdupq_n_s8  = __vdup<int8x16_t ,int8_t>;
    const auto& vdupq_n_s16 = __vdup<int16x8_t,int16_t>;
    const auto& vdupq_n_s32 = __vdup<int32x4_t,int32_t>;
    const auto& vdupq_n_s64 = __vdup<int64x2_t,int64_t>;

    const auto& vmovq_n_s8  = __vdup<int8x16_t ,int8_t>;
    const auto& vmovq_n_s16 = __vdup<int16x8_t,int16_t>;
    const auto& vmovq_n_s32 = __vdup<int32x4_t,int32_t>;
    const auto& vmovq_n_s64 = __vdup<int64x2_t,int64_t>;

    const auto& vdupq_n_u8  = __vdup<uint8x16_t ,uint8_t>;
    const auto& vdupq_n_u16 = __vdup<uint16x8_t,uint16_t>;
    const auto& vdupq_n_u32 = __vdup<uint32x4_t,uint32_t>;
    const auto& vdupq_n_u64 = __vdup<uint64x2_t,uint64_t>;

    const auto& vmovq_n_u8  = __vdup<uint8x16_t ,uint8_t>;
    const auto& vmovq_n_u16 = __vdup<uint16x8_t,uint16_t>;
    const auto& vmovq_n_u32 = __vdup<uint32x4_t,uint32_t>;
    const auto& vmovq_n_u64 = __vdup<uint64x2_t,uint64_t>;

    const auto& vdupq_n_f32 = __vdup<float32x4_t,float>;
    const auto& vmovq_n_f32 = __vdup<float32x4_t,float>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vget_lane - 64-bit vectors //////////////////////////////////
    const auto& vget_lane_s8  = __vget_lane<int8x8_t,  int8_t>;
    const auto& vget_lane_s16 = __vget_lane<int16x4_t, int16_t>;
    const auto& vget_lane_s32 = __vget_lane<int32x2_t, int32_t>;
    const auto& vget_lane_s64 = __vget_lane<int64x1_t, int64_t>;

    const auto& vget_lane_u8  = __vget_lane<uint8x8_t,  uint8_t>;
    const auto& vget_lane_u16 = __vget_lane<uint16x4_t, uint16_t>;
    const auto& vget_lane_u32 = __vget_lane<uint32x2_t, uint32_t>;
    const auto& vget_lane_u64 = __vget_lane<uint64x1_t, uint64_t>;

    const auto& vget_lane_f32 = __vget_lane<uint64x1_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vget_lane - 128-bit vectors //////////////////////////////////
    const auto& vgetq_lane_s8  = __vget_lane<int8x16_t,  int8_t>;
    const auto& vgetq_lane_s16 = __vget_lane<int16x8_t, int16_t>;
    const auto& vgetq_lane_s32 = __vget_lane<int32x4_t, int32_t>;
    const auto& vgetq_lane_s64 = __vget_lane<int64x2_t, int64_t>;

    const auto& vgetq_lane_u8  = __vget_lane<uint8x16_t,  uint8_t>;
    const auto& vgetq_lane_u16 = __vget_lane<uint16x8_t, uint16_t>;
    const auto& vgetq_lane_u32 = __vget_lane<uint32x4_t, uint32_t>;
    const auto& vgetq_lane_u64 = __vget_lane<uint64x2_t, uint64_t>;

    const auto& vgetq_lane_f32 = __vget_lane<uint64x2_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vdup_lane - 64-bit vectors //////////////////////////////////
    const auto& vdup_lane_s8  = __vdup_lane<int8x8_t,  int8_t>;
    const auto& vdup_lane_s16 = __vdup_lane<int16x4_t, int16_t>;
    const auto& vdup_lane_s32 = __vdup_lane<int32x2_t, int32_t>;
    const auto& vdup_lane_s64 = __vdup_lane<int64x1_t, int64_t>;

    const auto& vdup_lane_u8  = __vdup_lane<uint8x8_t,  uint8_t>;
    const auto& vdup_lane_u16 = __vdup_lane<uint16x4_t, uint16_t>;
    const auto& vdup_lane_u32 = __vdup_lane<uint32x2_t, uint32_t>;
    const auto& vdup_lane_u64 = __vdup_lane<uint64x1_t, uint64_t>;

    const auto& vdup_lane_f32 = __vdup_lane<uint64x1_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vdup_lane - 128-bit vectors /////////////////////////////////
    const auto& vdupq_lane_s8  = __vdup_lane<int8x16_t,  int8_t>;
    const auto& vdupq_lane_s16 = __vdup_lane<int16x8_t, int16_t>;
    const auto& vdupq_lane_s32 = __vdup_lane<int32x4_t, int32_t>;
    const auto& vdupq_lane_s64 = __vdup_lane<int64x2_t, int64_t>;

    const auto& vdupq_lane_u8  = __vdup_lane<uint8x16_t,  uint8_t>;
    const auto& vdupq_lane_u16 = __vdup_lane<uint16x8_t, uint16_t>;
    const auto& vdupq_lane_u32 = __vdup_lane<uint32x4_t, uint32_t>;
    const auto& vdupq_lane_u64 = __vdup_lane<uint64x2_t, uint64_t>;

    const auto& vdupq_lane_f32 = __vdup_lane<uint64x2_t, uint64_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vadd - 64-bit vectors ///////////////////////////////////////
    const auto& vadd_u8  = __vadd< uint8x8_t>;
    const auto& vadd_u16 = __vadd<uint16x4_t>;
    const auto& vadd_u32 = __vadd<uint32x2_t>;
    const auto& vadd_u64 = __vadd<uint64x1_t>;

    const auto& vadd_s8  = __vadd<  int8x8_t>;
    const auto& vadd_s16 = __vadd< int16x4_t>;
    const auto& vadd_s32 = __vadd< int32x2_t>;
    const auto& vadd_s64 = __vadd< int64x1_t>;

    const auto& vadd_f32 = __vmul<float32x2_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vadd - 128-bit vectors //////////////////////////////////////
    const auto& vaddq_u8  = __vadd<uint8x16_t>;
    const auto& vaddq_u16 = __vadd<uint16x8_t>;
    const auto& vaddq_u32 = __vadd<uint32x4_t>;
    const auto& vaddq_u64 = __vadd<uint64x2_t>;

    const auto& vaddq_s8  = __vadd< int8x16_t>;
    const auto& vaddq_s16 = __vadd< int16x8_t>;
    const auto& vaddq_s32 = __vadd< int32x4_t>;
    const auto& vaddq_s64 = __vadd< int64x2_t>;

    const auto& vaddq_f32 = __vadd<float32x4_t>;
    ///////////////////////////////////////////////////////////////////////////
    

    // ARM NEON - vaddl ///////////////////////////////////////////////////////
    const auto& vaddl_s8  = __vaddl< int8x8_t,int16x8_t>;
    const auto& vaddl_s16 = __vaddl<int16x4_t,int32x4_t>;
    const auto& vaddl_s32 = __vaddl<int32x2_t,int64x2_t>;

    const auto& vaddl_u8  = __vaddl< uint8x8_t,uint16x8_t>;
    const auto& vaddl_u16 = __vaddl<uint16x4_t,uint32x4_t>;
    const auto& vaddl_u32 = __vaddl<uint32x2_t,uint64x2_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vsub - 64-bit vectors ///////////////////////////////////////
    const auto& vsub_u8  = __vsub< uint8x8_t>;
    const auto& vsub_u16 = __vsub<uint16x4_t>;
    const auto& vsub_u32 = __vsub<uint32x2_t>;
    const auto& vsub_u64 = __vsub<uint64x1_t>;
    
    const auto& vsub_s8  = __vsub<  int8x8_t>;
    const auto& vsub_s16 = __vsub< int16x4_t>;
    const auto& vsub_s32 = __vsub< int32x2_t>;
    const auto& vsub_s64 = __vsub< int64x1_t>;
    
    const auto& vsub_f32 = __vmul<float32x2_t>;
    ///////////////////////////////////////////////////////////////////////////
    
    // ARM NEON - vsub - 128-bit vectors //////////////////////////////////////
    const auto& vsubq_u8  = __vsub<uint8x16_t>;
    const auto& vsubq_u16 = __vsub<uint16x8_t>;
    const auto& vsubq_u32 = __vsub<uint32x4_t>;
    const auto& vsubq_u64 = __vsub<uint64x2_t>;
    
    const auto& vsubq_s8  = __vsub< int8x16_t>;
    const auto& vsubq_s16 = __vsub< int16x8_t>;
    const auto& vsubq_s32 = __vsub< int32x4_t>;
    const auto& vsubq_s64 = __vsub< int64x2_t>;
    
    const auto& vsubq_f32 = __vsub<float32x4_t>;
    ///////////////////////////////////////////////////////////////////////////
    
    
    // ARM NEON - vceq - 64-bit vectors ///////////////////////////////////////
    const auto& vceq_u8  = __vceq<   uint8x8_t,  uint8x8_t>;
    const auto& vceq_u16 = __vceq<  uint16x4_t, uint16x4_t>;
    const auto& vceq_u32 = __vceq<  uint32x2_t, uint32x2_t>;

    const auto& vceq_s8  = __vceq<    int8x8_t,  uint8x8_t>;
    const auto& vceq_s16 = __vceq<   int16x4_t, uint16x4_t>;
    const auto& vceq_s32 = __vceq<   int32x2_t, uint32x2_t>;

    const auto& vceq_f32 = __vceq< float32x2_t, uint32x2_t>;
    ///////////////////////////////////////////////////////////////////////////

    // ARM NEON - vceq - 128-bit vectors ///////////////////////////////////////
    const auto& vceqq_u8  = __vceq<  uint8x16_t, uint8x16_t>;
    const auto& vceqq_u16 = __vceq<  uint16x8_t, uint16x8_t>;
    const auto& vceqq_u32 = __vceq<  uint32x4_t, uint32x4_t>;

    const auto& vceqq_s8  = __vceq<   int8x16_t, uint8x16_t>;
    const auto& vceqq_s16 = __vceq<   int16x8_t, uint16x8_t>;
    const auto& vceqq_s32 = __vceq<   int32x4_t, uint32x4_t>;

    const auto& vceqq_f32 = __vceq< float32x4_t, uint32x4_t>;
    ///////////////////////////////////////////////////////////////////////////


}

#endif
