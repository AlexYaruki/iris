#include "../iris_common.h"
#include <cstdint>

#ifndef IRIS_ARM_COMMON
#define IRIS_ARM_COMMON

namespace iris::arm::common
{
using int8x8_t = iris::common::vector<int8_t, 8>;
using int8x8x2_t = iris::common::multi_vector<int8x8_t, 2>;
using int8x8x3_t = iris::common::multi_vector<int8x8_t, 3>;
using int8x8x4_t = iris::common::multi_vector<int8x8_t, 4>;

using int16x4_t = iris::common::vector<int16_t, 4>;
using int16x4x2_t = iris::common::multi_vector<int16x4_t, 2>;
using int16x4x3_t = iris::common::multi_vector<int16x4_t, 3>;
using int16x4x4_t = iris::common::multi_vector<int16x4_t, 4>;

using int32x2_t = iris::common::vector<int32_t, 2>;
using int32x2x2_t = iris::common::multi_vector<int32x2_t, 2>;
using int32x2x3_t = iris::common::multi_vector<int32x2_t, 3>;
using int32x2x4_t = iris::common::multi_vector<int32x2_t, 4>;

using int64x1_t = iris::common::vector<int64_t, 1>;
using int64x1x2_t = iris::common::multi_vector<int64x1_t, 2>;
using int64x1x3_t = iris::common::multi_vector<int64x1_t, 3>;
using int64x1x4_t = iris::common::multi_vector<int64x1_t, 4>;

using uint8x8_t = iris::common::vector<uint8_t, 8>;
using uint8x8x2_t = iris::common::multi_vector<uint8x8_t, 2>;
using uint8x8x3_t = iris::common::multi_vector<uint8x8_t, 3>;
using uint8x8x4_t = iris::common::multi_vector<uint8x8_t, 4>;

using uint16x4_t = iris::common::vector<uint16_t, 4>;
using uint16x4x2_t = iris::common::multi_vector<uint16x4_t, 2>;
using uint16x4x3_t = iris::common::multi_vector<uint16x4_t, 3>;
using uint16x4x4_t = iris::common::multi_vector<uint16x4_t, 4>;

using uint32x2_t = iris::common::vector<uint32_t, 2>;
using uint32x2x2_t = iris::common::multi_vector<uint32x2_t, 2>;
using uint32x2x3_t = iris::common::multi_vector<uint32x2_t, 3>;
using uint32x2x4_t = iris::common::multi_vector<uint32x2_t, 4>;

using uint64x1_t = iris::common::vector<uint64_t, 1>;
using uint64x1x2_t = iris::common::multi_vector<uint64x1_t, 2>;
using uint64x1x3_t = iris::common::multi_vector<uint64x1_t, 3>;
using uint64x1x4_t = iris::common::multi_vector<uint64x1_t, 4>;

using float32x2_t = iris::common::vector<float, 2>;
using float32x2x2_t = iris::common::multi_vector<float32x2_t, 2>;
using float32x2x3_t = iris::common::multi_vector<float32x2_t, 3>;
using float32x2x4_t = iris::common::multi_vector<float32x2_t, 4>;

// ARM NEON - Types - 128-bit

using int8x16_t = iris::common::vector<int8_t, 16>;
using int8x16x2_t = iris::common::multi_vector<int8x16_t, 2>;
using int8x16x3_t = iris::common::multi_vector<int8x16_t, 3>;
using int8x16x4_t = iris::common::multi_vector<int8x16_t, 4>;

using int16x8_t = iris::common::vector<int16_t, 8>;
using int16x8x2_t = iris::common::multi_vector<int16x8_t, 2>;
using int16x8x3_t = iris::common::multi_vector<int16x8_t, 3>;
using int16x8x4_t = iris::common::multi_vector<int16x8_t, 4>;

using int32x4_t = iris::common::vector<int32_t, 4>;
using int32x4x2_t = iris::common::multi_vector<int32x4_t, 2>;
using int32x4x3_t = iris::common::multi_vector<int32x4_t, 3>;
using int32x4x4_t = iris::common::multi_vector<int32x4_t, 4>;

using int64x2_t = iris::common::vector<int64_t, 2>;
using int64x2x2_t = iris::common::multi_vector<int64x2_t, 2>;
using int64x2x3_t = iris::common::multi_vector<int64x2_t, 3>;
using int64x2x4_t = iris::common::multi_vector<int64x2_t, 4>;

using uint8x16_t = iris::common::vector<uint8_t, 16>;
using uint8x16x2_t = iris::common::multi_vector<uint8x16_t, 2>;
using uint8x16x3_t = iris::common::multi_vector<uint8x16_t, 3>;
using uint8x16x4_t = iris::common::multi_vector<uint8x16_t, 4>;

using uint16x8_t = iris::common::vector<uint16_t, 8>;
using uint16x8x2_t = iris::common::multi_vector<uint16x8_t, 2>;
using uint16x8x3_t = iris::common::multi_vector<uint16x8_t, 3>;
using uint16x8x4_t = iris::common::multi_vector<uint16x8_t, 4>;

using uint32x4_t = iris::common::vector<uint32_t, 4>;
using uint32x4x2_t = iris::common::multi_vector<uint32x4_t, 2>;
using uint32x4x3_t = iris::common::multi_vector<uint32x4_t, 3>;
using uint32x4x4_t = iris::common::multi_vector<uint32x4_t, 4>;

using uint64x2_t = iris::common::vector<uint64_t, 2>;
using uint64x2x2_t = iris::common::multi_vector<uint64x2_t, 2>;
using uint64x2x3_t = iris::common::multi_vector<uint64x2_t, 3>;
using uint64x2x4_t = iris::common::multi_vector<uint64x2_t, 4>;

using float32x4_t = iris::common::vector<float, 4>;
using float32x4x2_t = iris::common::multi_vector<float32x4_t, 2>;
using float32x4x3_t = iris::common::multi_vector<float32x4_t, 3>;
using float32x4x4_t = iris::common::multi_vector<float32x4_t, 4>;
} // namespace iris::arm::common

using namespace iris::arm::common;
#endif