#include "iris_common.h"
#include <cstdint>

#ifndef IRIS_X86_COMMON
#define IRIS_X86_COMMON

namespace iris::x86::common
{
#ifndef _MSC_VER
using __int64 = int64_t;
#endif //_MSC_VER
using __m64 = iris::common::vector<uint8_t, 8>;
using __m128 = iris::common::vector<uint8_t, 16>;

template <typename T, typename E>
T ____mm_add(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<E>(i) = v1.template at<E>(i) + v2.template at<E>(i);
    }
    return result;
}

template <typename T, typename E>
T ____mm_add_single(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        if (i == 0)
        {
            result.template at<E>(i) = v1.template at<E>(i) + v2.template at<E>(i);
        }
        else
        {
            result.template at<E>(i) = v1.template at<E>(i);
        }
    }
    return result;
}

template <typename T, typename E>
T ____mm_sub(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<E>(i) = v1.template at<E>(i) - v2.template at<E>(i);
    }
    return result;
}

template <typename T, typename E>
T ____mm_sub_single(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        if (i == 0)
        {
            result.template at<E>(i) = v1.template at<E>(i) - v2.template at<E>(i);
        }
        else
        {
            result.template at<E>(i) = v1.template at<E>(i);
        }
    }
    return result;
}

template <typename T, typename E, typename E_TMP>
T ____mm_sad_(T v1, T v2)
{
    T result;
    std::memset(&result, 0, sizeof(result));
    E_TMP tmp = 0;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        E x = v1.template at<E>(i);
        E y = v2.template at<E>(i);
        E_TMP z = x - y;
        if (z < 0)
        {
            z *= -1;
        }
        tmp += z;
    }
    result.template at<E_TMP>(0) = tmp;
    return result;
}

template <typename T, typename E>
T ____mm_mul(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<E>(i) = v1.template at<E>(i) * v2.template at<E>(i);
    }
    return result;
}

template <typename T, typename E>
T ____mm_mul_single(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        if (i == 0)
        {
            result.template at<E>(i) = v1.template at<E>(i) * v2.template at<E>(i);
        }
        else
        {
            result.template at<E>(i) = v1.template at<E>(i);
        }
    }
    return result;
}

template <typename T, typename E>
T ____mm_div(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        result.template at<E>(i) = v1.template at<E>(i) / v2.template at<E>(i);
    }
    return result;
}

template <typename T, typename E>
T ____mm_div_single(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        if (i == 0)
        {
            result.template at<E>(i) = v1.template at<E>(i) / v2.template at<E>(i);
        }
        else
        {
            result.template at<E>(i) = v1.template at<E>(i);
        }
    }
    return result;
}

template <typename T, typename E>
T ____mm_adds(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        E x = v1.template at<E>(i);
        E y = v2.template at<E>(i);
        if ((x > 0) && (y > std::numeric_limits<E>::max() - x))
        { // Overflow
            result.template at<E>(i) = std::numeric_limits<E>::max();
        }
        else if (std::numeric_limits<E>::is_signed && (x < 0) && (y < std::numeric_limits<E>::min() - x))
        { //Underflow
            result.template at<E>(i) = std::numeric_limits<E>::min();
        }
        else
        {
            result.template at<E>(i) = x + y;
        }
    }
    return result;
}

template <typename T, typename E>
T ____mm_subs(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        E x = v1.template at<E>(i);
        E y = v2.template at<E>(i);
        if ((x > 0) && (y < std::numeric_limits<E>::min() + x))
        { // Overflow
            result.template at<E>(i) = std::numeric_limits<E>::max();
        }
        else if (std::numeric_limits<E>::is_signed && (x < 0) && (y > std::numeric_limits<E>::min() + x))
        { //Underflow
            result.template at<E>(i) = std::numeric_limits<E>::min();
        }
        else
        {
            result.template at<E>(i) = x - y;
        }
    }
    return result;
}

template <typename T, typename E, typename E_TMP>
T ____mm_mulhi(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        E_TMP tmp = v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);
        result.template at<E>(i) = reinterpret_cast<E *>(&tmp)[1];
    }
    return result;
}

template <typename T, typename E, typename E_TMP>
T ____mm_mullo(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < T::length; i++)
    {
        E_TMP tmp = v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);
        result.template at<E>(i) = reinterpret_cast<E *>(&tmp)[0];
    }
    return result;
}

template <typename T, typename E, typename E_TMP>
T ____mm_madd(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i += 2)
    {
        E_TMP tmp = v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);
        tmp += v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);

        result.template at<E_TMP>(i % 2) = tmp;
    }
    return result;
}

template <bool...>
struct bool_pack;
template <bool... v>
using all_true = std::is_same<bool_pack<true, v...>, bool_pack<v..., true>>;

template <typename E>
void ____m_set2(E *target)
{
}

template <typename E, typename... Args, typename = std::enable_if<all_true<std::is_convertible<Args, E>{}...>{}>>
void ____m_set2(E *target, E value, Args... args)
{
    *target = value;
    ____m_set2(target + 1, args...);
}

template <typename T, typename E, size_t N, typename... Args, typename = typename std::enable_if<sizeof...(Args) == N>::type>
T ____mm_set(Args &&... args)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    ____m_set2(target, args...);
    return result;
}

template <typename T, typename E, size_t N, typename... Args, typename = typename std::enable_if<sizeof...(Args) == N>::type>
T ____mm_setr(Args &&... args)
{
    T result = ____mm_set<T, E, N>(args...);
    for (size_t i = 0; i < (sizeof(T) / sizeof(E) / 2); i++)
    {
        std::swap(result.template at<E>(i), result.template at<E>((sizeof(T) / sizeof(E) - 1 - i)));
    }
    return result;
}

template <typename T, typename E>
T ____mm_set1(E x)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = x;
    }
    return result;
}

template <typename T>
T ____mm_setzero()
{
    T result;
    for (size_t i = 0; i < sizeof(T); i++)
    {
        result.template at<uint8_t>(i) = 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_unpackhi(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0, j = (sizeof(T) / sizeof(E)) / 2; i < (sizeof(T) / sizeof(E)) / 2; i += 2, j++)
    {
        target[i] = v1.template at<E>(j);
        target[i + 1] = v2.template at<E>(j);
    }
    return result;
}

template <typename T, typename E>
T ____mm_unpacklo(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0, j = 0; i < (sizeof(T) / sizeof(E)) / 2; i += 2, j++)
    {
        target[i] = v1.template at<E>(j);
        target[i + 1] = v2.template at<E>(j);
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpeq(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = v1.template at<E>(i) == v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpgt(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = v1.template at<E>(i) > v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpge(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = v1.template at<E>(i) >= v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmplt(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = v1.template at<E>(i) < v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmple(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = v1.template at<E>(i) <= v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpneq(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = v1.template at<E>(i) != v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpngt(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = !(v1.template at<E>(i) > v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpnge(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = !(v1.template at<E>(i) >= v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpnlt(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = !(v1.template at<E>(i) < v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpnle(T v1, T v2)
{
    T result;
    E *target = reinterpret_cast<E *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        target[i] = !(v1.template at<E>(i) <= v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpeq_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = v1.template at<E>(0) == v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpgt_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = v1.template at<E>(0) > v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpge_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = v1.template at<E>(0) >= v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmplt_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = v1.template at<E>(0) < v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmple_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = v1.template at<E>(0) <= v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpneq_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = v1.template at<E>(0) != v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpngt_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = !(v1.template at<E>(0) > v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpnge_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = !(v1.template at<E>(0) >= v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpnlt_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = !(v1.template at<E>(0) < v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpnle_single(T v1, T v2)
{
    T result = v1;
    result.template at<E>(0) = !(v1.template at<E>(0) <= v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpord(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        bool x = v1.template at<E>(i) == std::numeric_limits<float>::quiet_NaN();
        bool y = v1.template at<E>(i) == std::numeric_limits<float>::quiet_NaN();
        result.template at<E>(i) = (x || y) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpunord(T v1, T v2)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        bool x = v1.template at<E>(i) != std::numeric_limits<float>::quiet_NaN();
        bool y = v1.template at<E>(i) != std::numeric_limits<float>::quiet_NaN();
        result.template at<E>(i) = (x || y) ? std::numeric_limits<E>::max() : 0;
    }
    return result;
}

template <typename T, typename E>
T ____mm_cmpord_single(T v1, T v2)
{
    T result = v1;
    bool x = v1.template at<E>(0) == std::numeric_limits<E>::quiet_NaN();
    bool y = v1.template at<E>(0) == std::numeric_limits<E>::quiet_NaN();
    result.template at<E>(0) = (x || y) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E>
T ____mm_cmpunord_single(T v1, T v2)
{
    T result = v1;
    bool x = v1.template at<E>(0) != std::numeric_limits<E>::quiet_NaN();
    bool y = v1.template at<E>(0) != std::numeric_limits<E>::quiet_NaN();
    result.template at<E>(0) = (x || y) ? std::numeric_limits<E>::max() : 0;
    return result;
}

template <typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
int32_t ____mm_comieq_ss(T v1, T v2)
{
    return v1.template at<E>(0) == v2.template at<E>(0) ? 1 : 0;
}

template <typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
int32_t ____mm_comineq_ss(T v1, T v2)
{
    return v1.template at<E>(0) != v2.template at<E>(0) ? 1 : 0;
}

template <typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
int32_t ____mm_comigt_ss(T v1, T v2)
{
    return v1.template at<E>(0) > v2.template at<E>(0) ? 1 : 0;
}
template <typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
int32_t ____mm_comige_ss(T v1, T v2)
{
    return v1.template at<E>(0) >= v2.template at<E>(0) ? 1 : 0;
}
template <typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
int32_t ____mm_comilt_ss(T v1, T v2)
{
    return v1.template at<E>(0) < v2.template at<E>(0) ? 1 : 0;
}
template <typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
int32_t ____mm_comile_ss(T v1, T v2)
{
    return v1.template at<E>(0) <= v2.template at<E>(0) ? 1 : 0;
}

template <typename T>
T ____mm_and(T v1, T v2)
{
    T result;
    uint8_t *target = reinterpret_cast<uint8_t *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(uint8_t); i++)
    {
        target[i] = v1.template at<uint8_t>(i) & v2.template at<uint8_t>(i);
    }
    return result;
}

template <typename T>
T ____mm_or(T v1, T v2)
{
    T result;
    uint8_t *target = reinterpret_cast<uint8_t *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(uint8_t); i++)
    {
        target[i] = v1.template at<uint8_t>(i) | v2.template at<uint8_t>(i);
    }
    return result;
}

template <typename T>
T ____mm_xor(T v1, T v2)
{
    T result;
    uint8_t *target = reinterpret_cast<uint8_t *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(uint8_t); i++)
    {
        target[i] = v1.template at<uint8_t>(i) ^ v2.template at<uint8_t>(i);
    }
    return result;
}

template <typename T>
T ____mm_andnot(T v1, T v2)
{
    T result;
    uint8_t *target = reinterpret_cast<uint8_t *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(uint8_t); i++)
    {
        target[i] = (~v1.template at<uint8_t>(i)) & v2.template at<uint8_t>(i);
    }
    return result;
}

template <typename T, typename U>
T ____mm_cvt(U e)
{
    T result;
    if (sizeof(T) <= sizeof(U))
    {
        result = reinterpret_cast<T *>(&e)[0];
    }
    else
    {
        U *target = reinterpret_cast<U *>(&result);
        for (size_t i = 0; i < sizeof(T) / sizeof(U); i++)
        {
            if (i == 0)
            {
                target[i] = e;
            }
            else
            {
                std::memset(target + i, 0, sizeof(U));
            }
        }
    }
    return result;
}

template <typename T, typename From, typename To>
T ____mm_packs(T v1, T v2)
{
    T result;
    To *target = reinterpret_cast<To *>(&result);
    for (size_t i = 0; i < sizeof(T) / sizeof(From); i++)
    {
        From temp = reinterpret_cast<From *>(&v1)[i];
        if (temp > std::numeric_limits<To>::max())
        {
            *target = std::numeric_limits<To>::max();
        }
        else if (temp < std::numeric_limits<To>::min())
        {
            *target = std::numeric_limits<To>::min();
        }
        else
        {
            *target = (To)temp;
        }
        target++;
    }
    for (size_t i = 0; i < sizeof(T) / sizeof(From); i++)
    {
        From temp = reinterpret_cast<From *>(&v2)[i];
        if (temp > std::numeric_limits<To>::max())
        {
            *target = std::numeric_limits<To>::max();
        }
        else if (temp < std::numeric_limits<To>::min())
        {
            *target = std::numeric_limits<To>::min();
        }
        else
        {
            *target = (To)temp;
        }
        target++;
    }
    return result;
}

template <typename T>
T ____bits_front(size_t N)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    for (size_t i = 0; i < (sizeof(T) * 8 - N); i++)
    {
        result |= 1 << i;
    }
    return result;
}

template <typename T>
T ____shift_right_zero_extend(T t, size_t N)
{
    if (sizeof(T) * 8 < N)
    {
        return 0;
    }
    else
    {
        return ____bits_front<T>(N) & (t >> N);
    }
}

template <typename T>
T ____shift_right_sign_extend(T t, size_t N)
{
    if (sizeof(T) * 8 < N)
    {
        return t & (1 << (sizeof(T) * 8 - 1));
    }
    else
    {
        return t >> N;
    }
}

template <typename T, typename E>
T ____mm_sll(T v, T count)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        if (count.template at<int64_t>(0) < sizeof(E) - 1)
        {
            result.template at<E>(i) = v.template at<E>(i) << count.template at<int64_t>(0);
        }
    }
    return result;
}

template <typename T, typename E>
T ____mm_slli(T v, int32_t imm)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        if (reinterpret_cast<uint8_t *>(&imm)[0] < sizeof(E) - 1)
        {
            result.template at<E>(i) = v.template at<E>(i) << reinterpret_cast<uint8_t *>(&imm)[0];
        }
    }
    return result;
}

template <typename T, typename E>
T ____mm_srl(T v, T count)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = ____shift_right_zero_extend(v.template at<E>(i), count.template at<int64_t>(0));
    }
    return result;
}

template <typename T, typename E>
T ____mm_srli(T v, int32_t imm)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = ____shift_right_zero_extend(v.template at<E>(i), reinterpret_cast<uint8_t *>(&imm)[0]);
    }
    return result;
}

template <typename T, typename E>
T ____mm_sra(T v, T count)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = ____shift_right_sign_extend(v.template at<E>(i), count.template at<int64_t>(0));
    }
    return result;
}

template <typename T, typename E>
T ____mm_srai(T v, int32_t imm)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = ____shift_right_sign_extend(v.template at<E>(i), reinterpret_cast<uint8_t *>(&imm)[0]);
    }
    return result;
}

template <typename... Args>
void ____mm_noop(Args &&... args)
{
}

template <typename T, typename E>
T ____mm_rcp(T v)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = static_cast<E>(1.0) / v.template at<E>(i);
    }
    return result;
}

template <typename T, typename E>
T ____mm_rcp_single(T v)
{
    T result = v;
    result.template at<E>(0) = static_cast<E>(1.0) / v.template at<E>(0);
    return result;
}
template <typename T, typename E>
T ____mm_rsqrt(T v)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = static_cast<E>(1.0) / std::sqrt(v.template at<E>(i));
    }
    return result;
}

template <typename T, typename E>
T ____mm_rsqrt_single(T v)
{
    T result = v;
    result.template at<E>(0) = static_cast<E>(1.0) / std::sqrt(v.template at<E>(0));
    return result;
}

template <typename T, typename E>
T ____mm_sqrt(T v)
{
    T result;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = std::sqrt(v.template at<E>(i));
    }
    return result;
}

template <typename T, typename E>
T ____mm_sqrt_single(T v)
{
    T result = v;
    result.template at<E>(0) = std::sqrt(v.template at<E>(0));
    return result;
}

template <typename T, typename E>
T ____mm_load(E *source)
{
    T result;
    std::memcpy(&result, source, sizeof(T));
    return result;
}

template <typename T, typename E>
T ____mm_load_single(E *source)
{
    T result;
    std::memset(&result, 0, sizeof(T));
    result.template at<E>(0) = *source;
    std::memcpy(&result, source, sizeof(E));
    return result;
}

template <typename T, typename E>
T ____mm_load_single_all(E const *source)
{
    T result;
    E e = *source;
    for (size_t i = 0; i < sizeof(T) / sizeof(E); i++)
    {
        result.template at<E>(i) = e;
    }
    return result;
}

} // namespace iris::x86::common

#endif