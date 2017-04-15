#ifndef NEXUS_H
#define NEXUS_H

#include <cstdint>
#include <limits>

namespace nexus {

    
    // Core
    namespace {
    
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

    }
    
#ifdef NEXUS_X86_MMX
    
    namespace x86_mmx {
    
    //Internal
    namespace {
    
    template<typename T, typename E>
    T ____mm_add(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<E>(i) = v1.template at<E>(i) + v2.template at<E>(i);
        }
        return result;
    }
    
    template<typename T, typename E>
    T ____mm_sub(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            result.template at<E>(i) = v1.template at<E>(i) - v2.template at<E>(i);
        }
        return result;
    }
    
    template<typename T, typename E>
    T ____mm_adds(T v1, T v2) {
        T result;
        for(size_t i = 0; i < T::length; i++) {
            E x = v1.template at<E>(i);
            E y = v2.template at<E>(i);
            if((x > 0) && (y > std::numeric_limits<E>::max - x)) { // Overflow
                result.template at<E>(i) = std::numeric_limits<E>::max;
            } else if (std::numeric_limits<E>::is_signed && (x < 0) && (y < std::numeric_limits<E>::min - x)) { //Underflow
                result.template at<E>(i) = std::numeric_limits<E>::min;
            } else {
                result.template at<E>(i) = x + y;
            }
        }
        return result;
    }
    
    template <bool...> struct bool_pack;
    template <bool... v>
    using all_true = std::is_same<bool_pack<true, v...>, bool_pack<v..., true>>;
    
    template<typename E>
    void ____m_set2(E* target) {
        
    }
    
    template<typename E, typename... Args, typename = std::enable_if<all_true<std::is_convertible<Args, E>{}...>{}>>
    void ____m_set2(E* target, E value, Args... args) {
        *target = value;
        ____m_set2(target+1,args...);
    }
    
    template<typename T,typename E,size_t N,typename... Args,typename = typename std::enable_if<sizeof...(Args) == N>::type>
    T ____mm_set(Args&&... args) {
        T result;
        E *target = reinterpret_cast<E*>(&result);
        ____m_set2(target,args...);
        return result;
    }
    
    template<typename T, typename E>
    T ____mm_set1(E x) {
        T result;
        E* target = reinterpret_cast<E*>(&result);
        for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
            target[i] = x;
        }
        return result;
    }
    
    template<typename T>
    T ____mm_setzero() {
        T result;
        for(int i = 0; i < sizeof(T); i++) {
            result.template at<uint8_t>(i) = 0;
        }
        return result;
    }
    
    template<typename T, typename E>
    T ____mm_cmpeq(T v1, T v2) {
        T result;
        E* target = reinterpret_cast<E*>(&result);
        for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
            target[i] = v1.template at<E>(i) == v1.template at<E>(i) ? std::numeric_limits<E>::max : 0;
        }
        return result;
    }
    
    template<typename T, typename E>
    T ____mm_cmpgt(T v1, T v2) {
        T result;
        E* target = reinterpret_cast<E*>(&result);
        for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
            target[i] = v1.template at<E>(i) > v1.template at<E>(i) ? std::numeric_limits<E>::max : 0;
        }
        return result;
    }
    
    template<typename T>
    T ____mm_and(T v1, T v2) {
        T result;
        uint8_t* target = reinterpret_cast<uint8_t*>(&result);
        for(int i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
            target[i] = v1.template at<uint8_t>(i) & v1.template at<uint8_t>(i);
        }
        return result;
    }
    
    template<typename T>
    T ____mm_andnot(T v1, T v2) {
        T result;
        uint8_t* target = reinterpret_cast<uint8_t*>(&result);
        for(int i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
            target[i] = (~v1.template at<uint8_t>(i)) & v1.template at<uint8_t>(i);
        }
        return result;
    }
    
    }
    
    using __int64 = int64_t;
    using __m64 = vector<int8_t, 8>;
        
    const auto& _mm_add_pi8   = ____mm_add<__m64,  int8_t>;
    const auto& _mm_add_pi16  = ____mm_add<__m64, int16_t>;
    const auto& _mm_add_pi32  = ____mm_add<__m64, int32_t>;
    
    const auto& _mm_adds_pi8  = ____mm_add<__m64,  int8_t>;
    const auto& _mm_adds_pi16 = ____mm_add<__m64, int16_t>;
    const auto& _mm_adds_pu8  = ____mm_add<__m64, uint8_t>;
    const auto& _mm_adds_pu16 = ____mm_add<__m64,uint16_t>;
    
    const auto& _m_paddb   = _mm_add_pi8;
    const auto& _m_paddw   = _mm_add_pi16;
    const auto& _m_paddd   = _mm_add_pi32;
        
    const auto& _m_paddsb  = _mm_adds_pi8;
    const auto& _m_paddsw  = _mm_adds_pi16;
    const auto& _m_paddusb = _mm_adds_pu8;
    const auto& _m_paddusw = _mm_adds_pu16;
        
    const auto& _mm_sub_pi8   = ____mm_sub<__m64,  int8_t>;
    const auto& _mm_sub_pi16  = ____mm_sub<__m64, int16_t>;
    const auto& _mm_sub_pi32  = ____mm_sub<__m64, int32_t>;
        
    const auto& _m_psubb   = _mm_sub_pi8;
    const auto& _m_psubw   = _mm_sub_pi16;
    const auto& _m_psubd   = _mm_sub_pi32;
    
    const auto& _mm_set_pi8  = ____mm_set<__m64,  int8_t,8, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>;
    const auto& _mm_set_pi16 = ____mm_set<__m64, int16_t,4,int16_t,int16_t,int16_t,int16_t>;
    const auto& _mm_set_pi32 = ____mm_set<__m64, int32_t,2,int32_t,int32_t>;
    
    const auto& _mm_set1_pi8  = ____mm_set1<__m64,  int8_t>;
    const auto& _mm_set1_pi16 = ____mm_set1<__m64, int16_t>;
    const auto& _mm_set1_pi32 = ____mm_set1<__m64, int32_t>;
    
    const auto& _mm_cmpeq_pi8  = ____mm_cmpeq<__m64,  int8_t>;
    const auto& _mm_cmpeq_pi16 = ____mm_cmpeq<__m64, int16_t>;
    const auto& _mm_cmpeq_pi32 = ____mm_cmpeq<__m64, int32_t>;
    
    const auto& _mm_cmpgt_pi8  = ____mm_cmpgt<__m64,  int8_t>;
    const auto& _mm_cmpgt_pi16 = ____mm_cmpgt<__m64, int16_t>;
    const auto& _mm_cmpgt_pi32 = ____mm_cmpgt<__m64, int32_t>;
    
    const auto& _mm_and_si64    = ____mm_and<__m64>;
    const auto& _mm_andnot_si64 = ____mm_andnot<__m64>;
    
    
    const auto& _m_pcmpeqb  = _mm_cmpeq_pi8;
    const auto& _m_pcmpeqw = _mm_cmpeq_pi16;
    const auto& _m_pcmpeqd = _mm_cmpeq_pi32;
    
    const auto& _m_pcmpgtb = _mm_cmpgt_pi8;
    const auto& _m_pcmpgtw = _mm_cmpgt_pi16;
    const auto& _m_pcmpgtd = _mm_cmpgt_pi32;
    
    
    const auto& _mm_setzero_si64 = ____mm_setzero<__m64>();
    
    }
    
    using namespace x86_mmx;
    
#endif

#ifdef NEXUS_ARM_NEON
    
    namespace arm_neon {
    
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
    
    using namespace arm_neon;
    
#endif

}

#endif
