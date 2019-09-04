#include "iris_x86_common.h"
#include <cstdint>
#ifndef IRIS_X86_MMX
#define IRIS_X86_MMX

namespace iris::x86::mmx
{
    const auto &_mm_sll_pi16 = ____mm_sll<__m64, int16_t>;
    const auto &_mm_sll_pi32 = ____mm_sll<__m64, int32_t>;
    const auto &_mm_sll_si64 = ____mm_sll<__m64, int64_t>;

    const auto &_mm_slli_pi16 = ____mm_slli<__m64, int16_t>;
    const auto &_mm_slli_pi32 = ____mm_slli<__m64, int32_t>;
    const auto &_mm_slli_si64 = ____mm_slli<__m64, int64_t>;

    const auto &_mm_srl_pi16 = ____mm_sll<__m64, int16_t>;
    const auto &_mm_srl_pi32 = ____mm_sll<__m64, int32_t>;
    const auto &_mm_srl_si64 = ____mm_sll<__m64, int64_t>;

    const auto &_mm_srli_pi16 = ____mm_slli<__m64, int16_t>;
    const auto &_mm_srli_pi32 = ____mm_slli<__m64, int32_t>;
    const auto &_mm_srli_si64 = ____mm_slli<__m64, int64_t>;

    const auto &_mm_sra_pi16 = ____mm_sra<__m64, int16_t>;
    const auto &_mm_sra_pi32 = ____mm_sra<__m64, int32_t>;

    const auto &_mm_srai_pi16 = ____mm_srai<__m64, int16_t>;
    const auto &_mm_srai_pi32 = ____mm_srai<__m64, int32_t>;

    const auto &_m_psllw = ____mm_sll<__m64, int16_t>;
    const auto &_m_pslld = ____mm_sll<__m64, int32_t>;
    const auto &_m_psllq = ____mm_sll<__m64, int64_t>;

    const auto &_m_psllwi = ____mm_slli<__m64, int16_t>;
    const auto &_m_pslldi = ____mm_slli<__m64, int32_t>;
    const auto &_m_psllqi = ____mm_slli<__m64, int64_t>;

    const auto &_m_psrlw = ____mm_sll<__m64, int16_t>;
    const auto &_m_psrld = ____mm_sll<__m64, int32_t>;
    const auto &_m_psrlq = ____mm_sll<__m64, int64_t>;

    const auto &_m_psrliw = ____mm_slli<__m64, int16_t>;
    const auto &_m_psrlid = ____mm_slli<__m64, int32_t>;
    const auto &_m_psrliq = ____mm_slli<__m64, int64_t>;

    const auto &_m_psraw = ____mm_sra<__m64, int16_t>;
    const auto &_m_psrad = ____mm_sra<__m64, int32_t>;

    const auto &_m_psraiw = ____mm_srai<__m64, int16_t>;
    const auto &_m_psraid = ____mm_srai<__m64, int32_t>;

    const auto &_mm_add_pi8 = ____mm_add<__m64, int8_t>;
    const auto &_mm_add_pi16 = ____mm_add<__m64, int16_t>;
    const auto &_mm_add_pi32 = ____mm_add<__m64, int32_t>;

    const auto &_mm_adds_pi8 = ____mm_adds<__m64, int8_t>;
    const auto &_mm_adds_pi16 = ____mm_adds<__m64, int16_t>;
    const auto &_mm_adds_pu8 = ____mm_adds<__m64, uint8_t>;
    const auto &_mm_adds_pu16 = ____mm_adds<__m64, uint16_t>;

    const auto &_m_paddb = _mm_add_pi8;
    const auto &_m_paddw = _mm_add_pi16;
    const auto &_m_paddd = _mm_add_pi32;

    const auto &_m_paddsb = _mm_adds_pi8;
    const auto &_m_paddsw = _mm_adds_pi16;
    const auto &_m_paddusb = _mm_adds_pu8;
    const auto &_m_paddusw = _mm_adds_pu16;

    const auto &_mm_sub_pi8 = ____mm_sub<__m64, int8_t>;
    const auto &_mm_sub_pi16 = ____mm_sub<__m64, int16_t>;
    const auto &_mm_sub_pi32 = ____mm_sub<__m64, int32_t>;

    const auto &_mm_subs_pi8 = ____mm_subs<__m64, int8_t>;
    const auto &_mm_subs_pi16 = ____mm_subs<__m64, int16_t>;
    const auto &_mm_subs_pu8 = ____mm_subs<__m64, uint8_t>;
    const auto &_mm_subs_pu16 = ____mm_subs<__m64, uint16_t>;

    const auto &_m_psubb = _mm_sub_pi8;
    const auto &_m_psubw = _mm_sub_pi16;
    const auto &_m_psubd = _mm_sub_pi32;

    const auto &_m_psubsb = _mm_subs_pi8;
    const auto &_m_psubsw = _mm_subs_pi16;
    const auto &_m_psubusb = _mm_subs_pu8;
    const auto &_m_psubusw = _mm_subs_pu16;

    const auto &_mm_mulhi_pi16 = ____mm_mulhi<__m64, int16_t, int32_t>;
    const auto &_mm_mullo_pi16 = ____mm_mullo<__m64, int16_t, int32_t>;
    const auto &_mm_madd_pi16 = ____mm_madd<__m64, int16_t, int32_t>;

    const auto &_m_pmulhw = ____mm_mulhi<__m64, int16_t, int32_t>;
    const auto &_m_pmullw = ____mm_mullo<__m64, int16_t, int32_t>;
    const auto &_m_pmaddwd = ____mm_madd<__m64, int16_t, int32_t>;

    const auto &_mm_set_pi8 = ____mm_set<__m64, int8_t, 8, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>;
    const auto &_mm_set_pi16 = ____mm_set<__m64, int16_t, 4, int16_t, int16_t, int16_t, int16_t>;
    const auto &_mm_set_pi32 = ____mm_set<__m64, int32_t, 2, int32_t, int32_t>;

    const auto &_mm_set1_pi8 = ____mm_set1<__m64, int8_t>;
    const auto &_mm_set1_pi16 = ____mm_set1<__m64, int16_t>;
    const auto &_mm_set1_pi32 = ____mm_set1<__m64, int32_t>;

    const auto &_mm_setr_pi8 = ____mm_setr<__m64, int8_t, 8, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>;
    const auto &_mm_setr_pi16 = ____mm_setr<__m64, int16_t, 4, int16_t, int16_t, int16_t, int16_t>;
    const auto &_mm_setr_pi32 = ____mm_setr<__m64, int32_t, 2, int32_t, int32_t>;

    const auto &_mm_setzero_si64 = ____mm_setzero<__m64>();

    const auto &_mm_cmpeq_pi8 = ____mm_cmpeq<__m64, int8_t>;
    const auto &_mm_cmpeq_pi16 = ____mm_cmpeq<__m64, int16_t>;
    const auto &_mm_cmpeq_pi32 = ____mm_cmpeq<__m64, int32_t>;

    const auto &_mm_cmpgt_pi8 = ____mm_cmpgt<__m64, int8_t>;
    const auto &_mm_cmpgt_pi16 = ____mm_cmpgt<__m64, int16_t>;
    const auto &_mm_cmpgt_pi32 = ____mm_cmpgt<__m64, int32_t>;

    const auto &_mm_and_si64 = ____mm_and<__m64>;
    const auto &_mm_or_si64 = ____mm_or<__m64>;
    const auto &_mm_xor_si64 = ____mm_xor<__m64>;
    const auto &_mm_andnot_si64 = ____mm_andnot<__m64>;

    const auto &_m_pand = _mm_and_si64;
    const auto &_m_por = _mm_or_si64;
    const auto &_m_pxor = _mm_xor_si64;
    const auto &_m_pandn = _mm_andnot_si64;

    const auto &_m_pcmpeqb = _mm_cmpeq_pi8;
    const auto &_m_pcmpeqw = _mm_cmpeq_pi16;
    const auto &_m_pcmpeqd = _mm_cmpeq_pi32;

    const auto &_m_pcmpgtb = _mm_cmpgt_pi8;
    const auto &_m_pcmpgtw = _mm_cmpgt_pi16;
    const auto &_m_pcmpgtd = _mm_cmpgt_pi32;

    const auto &_mm_cvtm64_si64 = ____mm_cvt<__int64, __m64>;
    const auto &_mm_cvtsi64_si32 = ____mm_cvt<__m64, int32_t>;
    const auto &_mm_cvtsi64_m64 = ____mm_cvt<__m64, __int64>;
    const auto &_mm_cvtsi32_si64 = ____mm_cvt<int32_t, __m64>;

    const auto &_m_from_int = ____mm_cvt<__m64, int32_t>;
    const auto &_m_from_int64 = ____mm_cvt<__m64, __int64>;
    const auto &_m_to_int = ____mm_cvt<int32_t, __m64>;
    const auto &_m_to_int64 = ____mm_cvt<__int64, __m64>;

    const auto &_mm_packs_pi16 = ____mm_packs<__m64, int16_t, int8_t>;
    const auto &_mm_packs_pi32 = ____mm_packs<__m64, int32_t, int16_t>;
    const auto &_mm_packs_pu16 = ____mm_packs<__m64, uint16_t, uint8_t>;

    const auto &_mm_unpackhi_pi8 = ____mm_unpackhi<__m64, int8_t>;
    const auto &_mm_unpackhi_pi16 = ____mm_unpackhi<__m64, int16_t>;
    const auto &_mm_unpackhi_pi32 = ____mm_unpackhi<__m64, int32_t>;

    const auto &_mm_unpacklo_pi8 = ____mm_unpacklo<__m64, int8_t>;
    const auto &_mm_unpacklo_pi16 = ____mm_unpacklo<__m64, int16_t>;
    const auto &_mm_unpacklo_pi32 = ____mm_unpacklo<__m64, int32_t>;

    const auto &_m_punpckhbw = ____mm_unpackhi<__m64, int8_t>;
    const auto &_m_punpckhwd = ____mm_unpackhi<__m64, int16_t>;
    const auto &_m_punpckhdq = ____mm_unpackhi<__m64, int32_t>;

    const auto &_m_punpcklbw = ____mm_unpacklo<__m64, int8_t>;
    const auto &_m_punpcklwd = ____mm_unpacklo<__m64, int16_t>;
    const auto &_m_punpckldq = ____mm_unpacklo<__m64, int32_t>;

    const auto &_m_packssdw = _mm_packs_pi32;
    const auto &_m_packsswb = _mm_packs_pi16;
    const auto &_m_packuswb = _mm_packs_pu16;

    const auto &_mm_empty = ____mm_noop<>;
    const auto &_m_empty = _mm_empty;
} // namespace iris::x86::mmx
#endif