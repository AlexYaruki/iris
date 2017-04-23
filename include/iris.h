#ifndef IRIS_H
#define IRIS_H

#include <cstdint>
#include <cmath>
#include <limits>
#include <utility>
#include <cstring>

namespace iris {

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

#ifdef IRIS_X86_MMX

    namespace x86 {

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
            T ____mm_add_single(T v1, T v2) {
                T result;
                for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                    if(i == 0) {
                        result.template at<E>(i) = v1.template at<E>(i) + v2.template at<E>(i);
                    } else {
                        result.template at<E>(i) = v1.template at<E>(i);
                    }
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
            T ____mm_sub_single(T v1, T v2) {
                T result;
                for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                    if(i == 0) {
                        result.template at<E>(i) = v1.template at<E>(i) - v2.template at<E>(i);
                    } else {
                        result.template at<E>(i) = v1.template at<E>(i);
                    }
                }
                return result;
            }

            template<typename T, typename E, typename E_TMP>
            T ____mm_sad_(T v1, T v2) {
                T result;
                std::memset(&result, 0, sizeof(result));
                E_TMP tmp = 0;
                for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                    E x = v1.template at<E>(i);
                    E y = v2.template at<E>(i);
                    E_TMP z = x - y;
                    if(z < 0) {
                        z *= -1;
                    }
                    tmp += z;
                    std::cout << "x: " << (int)x << ",y: " << (int)y << ",tmp: " << tmp << std::endl;
                }
                result.template at<E_TMP>(0) = tmp;
                return result;
            }

            template<typename T, typename E>
            T ____mm_mul(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<E>(i) = v1.template at<E>(i) * v2.template at<E>(i);
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_mul_single(T v1, T v2) {
                T result;
                for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                    if(i == 0) {
                        result.template at<E>(i) = v1.template at<E>(i) * v2.template at<E>(i);
                    } else {
                        result.template at<E>(i) = v1.template at<E>(i);
                    }
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_div(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<E>(i) = v1.template at<E>(i) / v2.template at<E>(i);
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_div_single(T v1, T v2) {
                T result;
                for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                    if(i == 0) {
                        result.template at<E>(i) = v1.template at<E>(i) / v2.template at<E>(i);
                    } else {
                        result.template at<E>(i) = v1.template at<E>(i);
                    }
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_adds(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    E x = v1.template at<E>(i);
                    E y = v2.template at<E>(i);
                    if((x > 0) && (y > std::numeric_limits<E>::max() - x)) { // Overflow
                        result.template at<E>(i) = std::numeric_limits<E>::max();
                    } else if (std::numeric_limits<E>::is_signed && (x < 0) && (y < std::numeric_limits<E>::min() - x)) { //Underflow
                        result.template at<E>(i) = std::numeric_limits<E>::min();
                    } else {
                        result.template at<E>(i) = x + y;
                    }
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_subs(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    E x = v1.template at<E>(i);
                    E y = v2.template at<E>(i);
                    if((x > 0) && (y < std::numeric_limits<E>::min() + x)) { // Overflow
                        result.template at<E>(i) = std::numeric_limits<E>::max();
                    } else if (std::numeric_limits<E>::is_signed && (x < 0) && (y > std::numeric_limits<E>::min() + x)) { //Underflow
                        result.template at<E>(i) = std::numeric_limits<E>::min();
                    } else {
                        result.template at<E>(i) = x - y;
                    }
                }
                return result;
            }

            template<typename T, typename E, typename E_TMP>
            T ____mm_mulhi(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    E_TMP tmp = v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);
                    result.template at<E>(i) = reinterpret_cast<E*>(&tmp)[1];
                }
                return result;
            }

            template<typename T, typename E, typename E_TMP>
            T ____mm_mullo(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    E_TMP tmp = v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);
                    result.template at<E>(i) = reinterpret_cast<E*>(&tmp)[0];
                }
                return result;
            }

            template<typename T, typename E, typename E_TMP>
            T ____mm_madd(T v1, T v2) {
                T result;
                for(size_t i = 0; i < sizeof(T)/sizeof(E); i += 2) {
                    E_TMP tmp = v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);
                    tmp += v1.template at<E>(i) * (E_TMP)v2.template at<E>(i);

                    result.template at<E_TMP>(i%2) = tmp;
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

            template<typename T,typename E,size_t N,typename... Args,typename = typename std::enable_if<sizeof...(Args) == N>::type>
            T ____mm_setr(Args&&... args) {
                T result = ____mm_set<T, E, N>(args...);
                for(int i = 0; i < (sizeof(T)/sizeof(E)/2); i++) {
                    std::swap(result.template at<E>(i),result.template at<E>((sizeof(T)/sizeof(E) - 1 - i)));
                }
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
            T ____mm_unpackhi(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0, j = (sizeof(T)/sizeof(E))/2; i < (sizeof(T)/sizeof(E))/2; i+=2, j++) {
                    target[i]   = v1.template at<E>(j);
                    target[i+1] = v2.template at<E>(j);
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_unpacklo(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0, j = 0; i < (sizeof(T)/sizeof(E))/2; i+=2, j++) {
                    target[i]   = v1.template at<E>(j);
                    target[i+1] = v2.template at<E>(j);
                }
                return result;
            }


            template<typename T, typename E>
            T ____mm_cmpeq(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = v1.template at<E>(i) == v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpgt(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = v1.template at<E>(i) > v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpge(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = v1.template at<E>(i) >= v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmplt(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = v1.template at<E>(i) < v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmple(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = v1.template at<E>(i) <= v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpneq(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = v1.template at<E>(i) != v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpngt(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = !(v1.template at<E>(i) > v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpnge(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = !(v1.template at<E>(i) >= v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpnlt(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = !(v1.template at<E>(i) < v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpnle(T v1, T v2) {
                T result;
                E* target = reinterpret_cast<E*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    target[i] = !(v1.template at<E>(i) <= v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpeq_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = v1.template at<E>(0) == v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpgt_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = v1.template at<E>(0) > v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpge_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = v1.template at<E>(0) >= v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmplt_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = v1.template at<E>(0) < v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmple_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = v1.template at<E>(0) <= v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpneq_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = v1.template at<E>(0) != v1.template at<E>(0) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpngt_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = !(v1.template at<E>(0) > v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpnge_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = !(v1.template at<E>(0) >= v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpnlt_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = !(v1.template at<E>(0) < v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpnle_single(T v1, T v2) {
                T result = v1;
                result.template at<E>(0) = !(v1.template at<E>(0) <= v1.template at<E>(0)) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpord(T v1, T v2){
                T result;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    bool x = v1.template at<E>(i) == std::numeric_limits<float>::quiet_NaN();
                    bool y = v1.template at<E>(i) == std::numeric_limits<float>::quiet_NaN();
                    result.template at<E>(i) = ( x || y ) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpunord(T v1, T v2){
                T result;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    bool x = v1.template at<E>(i) != std::numeric_limits<float>::quiet_NaN();
                    bool y = v1.template at<E>(i) != std::numeric_limits<float>::quiet_NaN();
                    result.template at<E>(i) = ( x || y ) ? std::numeric_limits<E>::max() : 0;
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpord_single(T v1, T v2){
                T result = v1;
                bool x = v1.template at<E>(0) == std::numeric_limits<E>::quiet_NaN();
                bool y = v1.template at<E>(0) == std::numeric_limits<E>::quiet_NaN();
                result.template at<E>(0) = ( x || y ) ? std::numeric_limits<E>::max() : 0;
                return result;
            }

            template<typename T, typename E>
            T ____mm_cmpunord_single(T v1, T v2){
                T result = v1;
                bool x = v1.template at<E>(0) != std::numeric_limits<E>::quiet_NaN();
                bool y = v1.template at<E>(0) != std::numeric_limits<E>::quiet_NaN();
                result.template at<E>(0) = ( x || y ) ? std::numeric_limits<E>::max() : 0;
                return result;
            }


            template<typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
            int32_t ____mm_comieq_ss(T v1, T v2) {
                return v1.template at<E>(0) == v2.template at<E>(0) ? 1 : 0;
            }

            template<typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
            int32_t ____mm_comineq_ss(T v1, T v2) {
                return v1.template at<E>(0) != v2.template at<E>(0) ? 1 : 0;
            }

            template<typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
            int32_t ____mm_comigt_ss(T v1, T v2) {
                return v1.template at<E>(0) > v2.template at<E>(0) ? 1 : 0;
            }
            template<typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
            int32_t ____mm_comige_ss(T v1, T v2) {
                return v1.template at<E>(0) >= v2.template at<E>(0) ? 1 : 0;
            }
            template<typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
            int32_t ____mm_comilt_ss(T v1, T v2) {
                return v1.template at<E>(0) < v2.template at<E>(0) ? 1 : 0;
            }
            template<typename T, typename E, typename = typename std::enable_if<sizeof(T) >= sizeof(E)>::type>
            int32_t ____mm_comile_ss(T v1, T v2) {
                return v1.template at<E>(0) <= v2.template at<E>(0) ? 1 : 0;
            }

            template<typename T>
            T ____mm_and(T v1, T v2) {
                T result;
                uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                    target[i] = v1.template at<uint8_t>(i) & v2.template at<uint8_t>(i);
                }
                return result;
            }

            template<typename T>
            T ____mm_or(T v1, T v2) {
                T result;
                uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                    target[i] = v1.template at<uint8_t>(i) | v2.template at<uint8_t>(i);
                }
                return result;
            }

            template<typename T>
            T ____mm_xor(T v1, T v2) {
                T result;
                uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                    target[i] = v1.template at<uint8_t>(i) ^ v2.template at<uint8_t>(i);
                }
                return result;
            }

            template<typename T>
            T ____mm_andnot(T v1, T v2) {
                T result;
                uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                    target[i] = (~v1.template at<uint8_t>(i)) & v2.template at<uint8_t>(i);
                }
                return result;
            }

            template<typename T, typename U>
            T ____mm_cvt(U e) {
                T result;
                if(sizeof(T) <= sizeof(U)) {
                    result = reinterpret_cast<T*>(&e)[0];
                } else {
                    U* target = reinterpret_cast<U*>(&result);
                    for(int i = 0; i < sizeof(T)/sizeof(U); i++) {
                        if(i == 0) {
                            target[i] = e;
                        } else {
                            std::memset(target + i, 0, sizeof(U));
                        }
                    }
                }
                return result;
            }

            template<typename T, typename From, typename To>
            T ____mm_packs(T v1, T v2){
                T result;
                To* target = reinterpret_cast<To*>(&result);
                for(int i = 0; i < sizeof(T)/sizeof(From); i++){
                    From temp = reinterpret_cast<From*>(&v1)[i];
                    if(temp > std::numeric_limits<To>::max()) {
                        *target = std::numeric_limits<To>::max();
                    } else if(temp < std::numeric_limits<To>::min()) {
                        *target = std::numeric_limits<To>::min();
                    } else {
                        *target = (To)temp;
                    }
                    target++;
                }
                for(int i = 0; i < sizeof(T)/sizeof(From); i++){
                    From temp = reinterpret_cast<From*>(&v2)[i];
                    if(temp > std::numeric_limits<To>::max()) {
                        *target = std::numeric_limits<To>::max();
                    } else if(temp < std::numeric_limits<To>::min()) {
                        *target = std::numeric_limits<To>::min();
                    } else {
                        *target = (To)temp;
                    }
                    target++;
                }
                return result;
            }

            template<typename T>
            T ____bits_front(size_t N) {
                T result;
                std::memset(&result, 0, sizeof(T));
                for(int i = 0; i < (sizeof(T)*8 - N); i++) {
                    result |= 1 << i;
                }
                return result;
            }

            template<typename T>
            T ____shift_right_zero_extend(T t, size_t N){
                if(sizeof(T)*8 < N) {
                    return 0;
                } else {
                    return ____bits_front<T>(N) & (t >> N);
                }
            }

            template<typename T>
            T ____shift_right_sign_extend(T t, size_t N){
                if(sizeof(T)*8 < N) {
                    return t & (1 << (sizeof(T)*8 -1));
                } else {
                    return t >> N;
                }
            }

            template<typename T, typename E>
            T ____mm_sll(T v, T count) {
                T result;
                std::memset(&result, 0, sizeof(T));
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    if(count.template at<int64_t>(0) < sizeof(E)-1) {
                        result.template at<E>(i) = v.template at<E>(i) << count.template at<int64_t>(0);
                    }
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_slli(T v, int32_t imm) {
                T result;
                std::memset(&result, 0, sizeof(T));
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    if(reinterpret_cast<uint8_t*>(&imm)[0] < sizeof(E)-1) {
                        result.template at<E>(i) = v.template at<E>(i) << reinterpret_cast<uint8_t*>(&imm)[0];
                    }
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_srl(T v, T count) {
                T result;
                std::memset(&result, 0, sizeof(T));
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = ____shift_right_zero_extend(v.template at<E>(i),count.template at<int64_t>(0));
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_srli(T v, int32_t imm) {
                T result;
                std::memset(&result, 0, sizeof(T));
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = ____shift_right_zero_extend(v.template at<E>(i),reinterpret_cast<uint8_t*>(&imm)[0]);
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_sra(T v, T count) {
                T result;
                std::memset(&result, 0, sizeof(T));
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = ____shift_right_sign_extend(v.template at<E>(i),count.template at<int64_t>(0));
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_srai(T v, int32_t imm) {
                T result;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = ____shift_right_sign_extend(v.template at<E>(i),reinterpret_cast<uint8_t*>(&imm)[0]);
                }
                return result;
            }

            template<typename... Args>
            void ____mm_noop(Args&&... args) {

            }

            template<typename T, typename E>
            T ____mm_rcp(T v) {
                T result;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = static_cast<E>(1.0)/v.template at<E>(i);
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_rcp_single(T v) {
                T result = v;
                result.template at<E>(0) = static_cast<E>(1.0)/v.template at<E>(0);
                return result;
            }
            template<typename T, typename E>
            T ____mm_rsqrt(T v) {
                T result;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = static_cast<E>(1.0)/std::sqrt(v.template at<E>(i));
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_rsqrt_single(T v) {
                T result = v;
                result.template at<E>(0) = static_cast<E>(1.0)/std::sqrt(v.template at<E>(0));
                return result;
            }

            template<typename T, typename E>
            T ____mm_sqrt(T v) {
                T result;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = std::sqrt(v.template at<E>(i));
                }
                return result;
            }

            template<typename T, typename E>
            T ____mm_sqrt_single(T v) {
                T result = v;
                result.template at<E>(0) = std::sqrt(v.template at<E>(0));
                return result;
            }

            template<typename T, typename E>
            T ____mm_load(E* source) {
                T result;
                std::memcpy(&result, source, sizeof(T));
                return result;
            }

            template<typename T, typename E>
            T ____mm_load_single(E* source) {
                T result;
                std::memset(&result, 0, sizeof(T));
                result.template at<E>(0) = *source;
                std::memcpy(&result, source, sizeof(E));
                return result;
            }

            template<typename T, typename E>
            T ____mm_load_single_all(E const * source) {
                T result;
                E e = *source;
                for(int i = 0; i < sizeof(T)/sizeof(E); i++) {
                    result.template at<E>(i) = e;
                }
                return result;
            }
        }
#if !defined(_MSC_VER)
        using __int64 = int64_t;
#endif
        using __m64 = vector<uint8_t, 8>;
        using __m128 = vector<uint8_t,16>;

        namespace mmx {


        const auto& _mm_sll_pi16 = ____mm_sll<__m64, int16_t>;
        const auto& _mm_sll_pi32 = ____mm_sll<__m64, int32_t>;
        const auto& _mm_sll_si64 = ____mm_sll<__m64, int64_t>;

        const auto& _mm_slli_pi16 = ____mm_slli<__m64, int16_t>;
        const auto& _mm_slli_pi32 = ____mm_slli<__m64, int32_t>;
        const auto& _mm_slli_si64 = ____mm_slli<__m64, int64_t>;

        const auto& _mm_srl_pi16 = ____mm_sll<__m64, int16_t>;
        const auto& _mm_srl_pi32 = ____mm_sll<__m64, int32_t>;
        const auto& _mm_srl_si64 = ____mm_sll<__m64, int64_t>;

        const auto& _mm_srli_pi16 = ____mm_slli<__m64, int16_t>;
        const auto& _mm_srli_pi32 = ____mm_slli<__m64, int32_t>;
        const auto& _mm_srli_si64 = ____mm_slli<__m64, int64_t>;

        const auto& _mm_sra_pi16 = ____mm_sra<__m64, int16_t>;
        const auto& _mm_sra_pi32 = ____mm_sra<__m64, int32_t>;

        const auto& _mm_srai_pi16 = ____mm_srai<__m64, int16_t>;
        const auto& _mm_srai_pi32 = ____mm_srai<__m64, int32_t>;

        const auto& _m_psllw = ____mm_sll<__m64, int16_t>;
        const auto& _m_pslld = ____mm_sll<__m64, int32_t>;
        const auto& _m_psllq = ____mm_sll<__m64, int64_t>;

        const auto& _m_psllwi = ____mm_slli<__m64, int16_t>;
        const auto& _m_pslldi = ____mm_slli<__m64, int32_t>;
        const auto& _m_psllqi = ____mm_slli<__m64, int64_t>;

        const auto& _m_psrlw = ____mm_sll<__m64, int16_t>;
        const auto& _m_psrld = ____mm_sll<__m64, int32_t>;
        const auto& _m_psrlq = ____mm_sll<__m64, int64_t>;

        const auto& _m_psrliw = ____mm_slli<__m64, int16_t>;
        const auto& _m_psrlid = ____mm_slli<__m64, int32_t>;
        const auto& _m_psrliq = ____mm_slli<__m64, int64_t>;

        const auto& _m_psraw = ____mm_sra<__m64, int16_t>;
        const auto& _m_psrad = ____mm_sra<__m64, int32_t>;

        const auto& _m_psraiw = ____mm_srai<__m64, int16_t>;
        const auto& _m_psraid = ____mm_srai<__m64, int32_t>;

        const auto& _mm_add_pi8   = ____mm_add<__m64,  int8_t>;
        const auto& _mm_add_pi16  = ____mm_add<__m64, int16_t>;
        const auto& _mm_add_pi32  = ____mm_add<__m64, int32_t>;

        const auto& _mm_adds_pi8  = ____mm_adds<__m64,  int8_t>;
        const auto& _mm_adds_pi16 = ____mm_adds<__m64, int16_t>;
        const auto& _mm_adds_pu8  = ____mm_adds<__m64, uint8_t>;
        const auto& _mm_adds_pu16 = ____mm_adds<__m64,uint16_t>;

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

        const auto& _mm_subs_pi8  = ____mm_subs<__m64,  int8_t>;
        const auto& _mm_subs_pi16 = ____mm_subs<__m64, int16_t>;
        const auto& _mm_subs_pu8  = ____mm_subs<__m64, uint8_t>;
        const auto& _mm_subs_pu16 = ____mm_subs<__m64,uint16_t>;

        const auto& _m_psubb   = _mm_sub_pi8;
        const auto& _m_psubw   = _mm_sub_pi16;
        const auto& _m_psubd   = _mm_sub_pi32;

        const auto& _m_psubsb  = _mm_subs_pi8;
        const auto& _m_psubsw  = _mm_subs_pi16;
        const auto& _m_psubusb = _mm_subs_pu8;
        const auto& _m_psubusw = _mm_subs_pu16;

        const auto& _mm_mulhi_pi16 = ____mm_mulhi<__m64, int16_t, int32_t>;
        const auto& _mm_mullo_pi16 = ____mm_mullo<__m64, int16_t, int32_t>;
        const auto& _mm_madd_pi16  = ____mm_madd<__m64, int16_t, int32_t>;

        const auto& _m_pmulhw   = ____mm_mulhi<__m64, int16_t, int32_t>;
        const auto& _m_pmullw   = ____mm_mullo<__m64, int16_t, int32_t>;
        const auto& _m_pmaddwd  = ____mm_madd <__m64, int16_t, int32_t>;

        const auto& _mm_set_pi8  = ____mm_set<__m64,  int8_t,8, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>;
        const auto& _mm_set_pi16 = ____mm_set<__m64, int16_t,4,int16_t,int16_t,int16_t,int16_t>;
        const auto& _mm_set_pi32 = ____mm_set<__m64, int32_t,2,int32_t,int32_t>;

        const auto& _mm_set1_pi8  = ____mm_set1<__m64,  int8_t>;
        const auto& _mm_set1_pi16 = ____mm_set1<__m64, int16_t>;
        const auto& _mm_set1_pi32 = ____mm_set1<__m64, int32_t>;


        const auto& _mm_setr_pi8  = ____mm_setr<__m64,  int8_t,8, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>;
        const auto& _mm_setr_pi16 = ____mm_setr<__m64, int16_t,4,int16_t,int16_t,int16_t,int16_t>;
        const auto& _mm_setr_pi32 = ____mm_setr<__m64, int32_t,2,int32_t,int32_t>;

        const auto& _mm_setzero_si64 = ____mm_setzero<__m64>();

        const auto& _mm_cmpeq_pi8  = ____mm_cmpeq<__m64,  int8_t>;
        const auto& _mm_cmpeq_pi16 = ____mm_cmpeq<__m64, int16_t>;
        const auto& _mm_cmpeq_pi32 = ____mm_cmpeq<__m64, int32_t>;

        const auto& _mm_cmpgt_pi8  = ____mm_cmpgt<__m64,  int8_t>;
        const auto& _mm_cmpgt_pi16 = ____mm_cmpgt<__m64, int16_t>;
        const auto& _mm_cmpgt_pi32 = ____mm_cmpgt<__m64, int32_t>;

        const auto& _mm_and_si64    = ____mm_and<__m64>;
        const auto& _mm_or_si64     = ____mm_or<__m64>;
        const auto& _mm_xor_si64    = ____mm_xor<__m64>;
        const auto& _mm_andnot_si64 = ____mm_andnot<__m64>;

        const auto& _m_pand  = _mm_and_si64;
        const auto& _m_por   = _mm_or_si64;
        const auto& _m_pxor  = _mm_xor_si64;
        const auto& _m_pandn = _mm_andnot_si64;

        const auto& _m_pcmpeqb  = _mm_cmpeq_pi8;
        const auto& _m_pcmpeqw = _mm_cmpeq_pi16;
        const auto& _m_pcmpeqd = _mm_cmpeq_pi32;

        const auto& _m_pcmpgtb = _mm_cmpgt_pi8;
        const auto& _m_pcmpgtw = _mm_cmpgt_pi16;
        const auto& _m_pcmpgtd = _mm_cmpgt_pi32;

        const auto& _mm_cvtm64_si64 = ____mm_cvt<__int64,__m64>;
        const auto& _mm_cvtsi64_si32 = ____mm_cvt<__m64,int32_t>;
        const auto& _mm_cvtsi64_m64 = ____mm_cvt<__m64,__int64>;
        const auto& _mm_cvtsi32_si64 = ____mm_cvt<int32_t,__m64>;

        const auto& _m_from_int = ____mm_cvt<__m64,int32_t>;
        const auto& _m_from_int64 = ____mm_cvt<__m64,__int64>;
        const auto& _m_to_int = ____mm_cvt<int32_t,__m64>;
        const auto& _m_to_int64 = ____mm_cvt<__int64,__m64>;

        const auto& _mm_packs_pi16 = ____mm_packs<__m64,  int16_t,  int8_t>;
        const auto& _mm_packs_pi32 = ____mm_packs<__m64,  int32_t, int16_t>;
        const auto& _mm_packs_pu16 = ____mm_packs<__m64, uint16_t, uint8_t>;

        const auto& _mm_unpackhi_pi8  = ____mm_unpackhi<__m64, int8_t>;
        const auto& _mm_unpackhi_pi16 = ____mm_unpackhi<__m64, int16_t>;
        const auto& _mm_unpackhi_pi32 = ____mm_unpackhi<__m64, int32_t>;

        const auto& _mm_unpacklo_pi8  = ____mm_unpacklo<__m64, int8_t>;
        const auto& _mm_unpacklo_pi16 = ____mm_unpacklo<__m64, int16_t>;
        const auto& _mm_unpacklo_pi32 = ____mm_unpacklo<__m64, int32_t>;

        const auto& _m_punpckhbw  = ____mm_unpackhi<__m64, int8_t>;
        const auto& _m_punpckhwd = ____mm_unpackhi<__m64, int16_t>;
        const auto& _m_punpckhdq = ____mm_unpackhi<__m64, int32_t>;

        const auto& _m_punpcklbw  = ____mm_unpacklo<__m64, int8_t>;
        const auto& _m_punpcklwd = ____mm_unpacklo<__m64, int16_t>;
        const auto& _m_punpckldq = ____mm_unpacklo<__m64, int32_t>;

        const auto& _m_packssdw = _mm_packs_pi32;
        const auto& _m_packsswb = _mm_packs_pi16;
        const auto& _m_packuswb = _mm_packs_pu16;

        const auto& _mm_empty = ____mm_noop<>;
        const auto& _m_empty = _mm_empty;

        }

        namespace sse {
            const auto& __mm_add_ps = ____mm_add<__m128, float>;
            const auto& __mm_add_ss = ____mm_add_single<__m128, float>;
            const auto& __mm_sub_ps = ____mm_sub<__m128, float>;
            const auto& __mm_sub_ss = ____mm_sub_single<__m128, float>;
            const auto& __mm_sad_pu8 = ____mm_sad_<__m64, uint8_t, int16_t>;
            const auto& _m_psadbw = __mm_sad_pu8;
            const auto& __mm_mul_ps = ____mm_mul<__m128, float>;
            const auto& __mm_mul_ss = ____mm_mul_single<__m128, float>;
            const auto& __mm_mulhi_pu16 = ____mm_mulhi<__m64, uint16_t, uint32_t>;
            const auto& _m_pmulhuw = __mm_mulhi_pu16;
            const auto& __mm_div_ps = ____mm_div<__m128, float>;
            const auto& __mm_div_ss = ____mm_div_single<__m128, float>;

            const auto& __mm_cmpeq_ps = ____mm_cmpeq<__m128, float>;
            const auto& __mm_cmpgt_ps = ____mm_cmpgt<__m128, float>;
            const auto& __mm_cmpge_ps = ____mm_cmpge<__m128, float>;
            const auto& __mm_cmplt_ps = ____mm_cmplt<__m128, float>;
            const auto& __mm_cmple_ps = ____mm_cmple<__m128, float>;
            const auto& __mm_cmpneq_ps = ____mm_cmpeq<__m128, float>;
            const auto& __mm_cmpngt_ps = ____mm_cmpgt<__m128, float>;
            const auto& __mm_cmpnge_ps = ____mm_cmpge<__m128, float>;
            const auto& __mm_cmpnlt_ps = ____mm_cmplt<__m128, float>;
            const auto& __mm_cmpnle_ps = ____mm_cmple<__m128, float>;
            const auto& __mm_cmpeq_ss = ____mm_cmpeq_single<__m128, float>;
            const auto& __mm_cmpgt_ss = ____mm_cmpgt_single<__m128, float>;
            const auto& __mm_cmpge_ss = ____mm_cmpge_single<__m128, float>;
            const auto& __mm_cmplt_ss = ____mm_cmplt_single<__m128, float>;
            const auto& __mm_cmple_ss = ____mm_cmple_single<__m128, float>;
            const auto& __mm_cmpneq_ss = ____mm_cmpeq_single<__m128, float>;
            const auto& __mm_cmpngt_ss = ____mm_cmpgt_single<__m128, float>;
            const auto& __mm_cmpnge_ss = ____mm_cmpge_single<__m128, float>;
            const auto& __mm_cmpnlt_ss = ____mm_cmplt_single<__m128, float>;
            const auto& __mm_cmpnle_ss = ____mm_cmple_single<__m128, float>;
            const auto& __mm_cmpord_ps = ____mm_cmpord<__m128, float>;
            const auto& __mm_cmpunord_ps = ____mm_cmpunord<__m128, float>;
            const auto& __mm_cmpord_ss = ____mm_cmpord_single<__m128, float>;
            const auto& __mm_cmpunord_ss = ____mm_cmpunord_single<__m128, float>;
            const auto& __mm_comieq_ss  = ____mm_comieq_ss<__m128, float>;
            const auto& __mm_comineq_ss = ____mm_comineq_ss<__m128, float>;
            const auto& __mm_comigt_ss  = ____mm_comigt_ss<__m128, float>;
            const auto& __mm_comige_ss  = ____mm_comige_ss<__m128, float>;
            const auto& __mm_comilt_ss  = ____mm_comilt_ss<__m128, float>;
            const auto& __mm_comile_ss  = ____mm_comile_ss<__m128, float>;
            const auto& __mm_ucomieq_ss  = __mm_comieq_ss;
            const auto& __mm_ucomineq_ss = __mm_comineq_ss;
            const auto& __mm_ucomigt_ss  = __mm_comigt_ss;
            const auto& __mm_ucomige_ss  = __mm_comige_ss;
            const auto& __mm_ucomilt_ss  = __mm_comilt_ss;
            const auto& __mm_ucomile_ss  = __mm_comile_ss;

            const auto& __mm_rcp_ps = ____mm_rcp<__m128, float>;
            const auto& __mm_rcp_ss = ____mm_rcp_single<__m128, float>;
            const auto& __mm_rsqrt_ps = ____mm_rcp<__m128, float>;
            const auto& __mm_rsqrt_ss = ____mm_rcp_single<__m128, float>;
            const auto& __mm_sqrt_ps = ____mm_rcp<__m128, float>;
            const auto& __mm_sqrt_ss = ____mm_rcp_single<__m128, float>;

            const auto& __mm_load_ps = ____mm_load<__m128,float>;
            const auto& __mm_load_ss = ____mm_load_single<__m128,float>;
            const auto& __mm_load_ps1 = ____mm_load_single_all<__m128,float>;
            const auto& __mm_load1_ps = __mm_load_ps1;
        }


    }

#if !defined(_MSC_VER)
    using x86::__int64;
#endif
    using x86::__m64;
    using x86::__m128;
    using namespace x86::mmx;
    using namespace x86::sse;

#endif

#ifdef IRIS_ARM_NEON

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

        template<typename T, typename E>
        T __vld(E* src) {
            T result;
            std::memcpy(&result, src, sizeof(T));
            return result;
        }

		// ARM NEON - Comparision ///////////////////////////////////////////////////

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

        template<typename T, typename R>
        R __vcgt(T v1, T v2) {
            R result;
            for(size_t i = 0; T::length; i++) {
                if(v1.template at<typename T::elementType>(i) > v2.template at<typename T::elementType>(i)) {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                } else {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                }
            }
        }

        template<typename T, typename R>
        R __vcge(T v1, T v2) {
            R result;
            for(size_t i = 0; T::length; i++) {
                if(v1.template at<typename T::elementType>(i) >= v2.template at<typename T::elementType>(i)) {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                } else {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                }
            }
        }

        template<typename T, typename R>
        R __vclt(T v1, T v2) {
            R result;
            for(size_t i = 0; T::length; i++) {
                if(v1.template at<typename T::elementType>(i) < v2.template at<typename T::elementType>(i)) {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                } else {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                }
            }
        }

        template<typename T, typename R>
        R __vcle(T v1, T v2) {
            R result;
            for(size_t i = 0; T::length; i++) {
                if(v1.template at<typename T::elementType>(i) <= v2.template at<typename T::elementType>(i)) {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                } else {
                    result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                }
            }
        }

		/*
		
		vcagt
		vcage
		vcalt
		vcale
		vtst

		*/

		/////////////////////////////////////////////////////////////////////////////

		// ARM NEON - Bitwise ///////////////////////////////////////////////////////

		/*
		
		vmvn
		vand
		vorr
		veor
		vbic
		vbsl

		*/

		/////////////////////////////////////////////////////////////////////////////

		// ARM NEON - Addition //////////////////////////////////////////////////////
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

        template<typename T, typename R>
        R __vaddw(R v1, T v2) {
            R result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename R::elementType>(i) = v1.template at<typename R::elementType>(i) + v2.template at<typename T::elementType>(i);
            }
            return result;
        }

        template<typename T>
        T __vhadd(T v1, T v2) {
            T result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i);
                result.template at<typename T::elementType>(i) /=2;
            }
            return result;
        }
		
        template<typename T>
        T __vqadd(T v1, T v2) {
            T result;
            for(size_t i = 0; i < T::length; i++) {
                auto x = v1.template at<typename T::elementType>(i);
                auto y = v2.template at<typename T::elementType>(i);
                if((x > 0) && (y > std::numeric_limits<typename T::elementType>::max() - x)) { // Overflow
                    result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
                } else if (std::numeric_limits<typename T::elementType>::is_signed && (x < 0) && (y < std::numeric_limits<typename T::elementType>::min() - x)) { //Underflow
                    result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
                } else {
                    result.template at<typename T::elementType>(i) = x + y;
                }
            }
            return result;
        }

		// vraddhn
		// vaddhn
		// vrhadd

		/////////////////////////////////////////////////////////////////////////////

		// ARM NEON - Subtraction ///////////////////////////////////////////////////
        template<typename T>
        T __vsub(T v1, T v2) {
            T result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
            }
            return result;
        }

        template<typename T, typename R>
        R __vsubl(T v1, T v2) {
            R result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename R::elementType>(i) = (typename R::elementType)v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
            }
            return result;
        }

        template<typename T, typename R>
        R __vsubw(R v1, T v2) {
            R result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename R::elementType>(i) = v1.template at<typename R::elementType>(i) - v2.template at<typename T::elementType>(i);
            }
            return result;
        }

        template<typename T>
        T __vhsub(T v1, T v2) {
            T result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) - v2.template at<typename T::elementType>(i);
                result.template at<typename T::elementType>(i) /=2;
            }
            return result;
        }

        template<typename T>
        T __vqsub(T v1, T v2) {
            T result;
            for(size_t i = 0; i < T::length; i++) {
                auto x = v1.template at<typename T::elementType>(i);
                auto y = v2.template at<typename T::elementType>(i);
                if((x > 0) && (y < std::numeric_limits<typename T::elementType>::min() + x)) { // Overflow
                    result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
                } else if (std::numeric_limits<typename T::elementType>::is_signed && (x < 0) && (y > std::numeric_limits<typename T::elementType>::min() + x)) { //Underflow
                    result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
                } else {
                    result.template at<typename T::elementType>(i) = x - y;
                }
            }
            return result;
        }

		// vrsubhn
		// vsubhn
		// vrhsub

		/////////////////////////////////////////////////////////////////////////////

		// ARM NEON - Multiplication ////////////////////////////////////////////////

        template<typename T>
        T __vmul(T v1, T v2) {
            T result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) * v2.template at<typename T::elementType>(i);
            }
            return result;
        }

        template<typename T, typename R>
        R __vmull(T v1, T v2) {
            R result;
            for(size_t i = 0; i < T::length; i++) {
                result.template at<typename R::elementType>(i) = (typename R::elementType)v1.template at<typename T::elementType>(i) * v2.template at<typename T::elementType>(i);
            }
            return result;
        }

		// ARM NEON - Multiplication-Accumulate /////////////////////////////////////

        template<typename T>
        T __vmla(T v1, T v2, T v3) {
            return __vadd(v3, __vmul(v1, v2));
        }

		/////////////////////////////////////////////////////////////////////////////

		// ARM NEON - Multiplication-Subtract ///////////////////////////////////////

		template<typename T>
		T __vmls(T v1, T v2, T v3) {
			return __vsub(v3, __vmul(v1, v2));
		}

		/////////////////////////////////////////////////////////////////////////////

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

#ifdef IRIS_ARM_NEON_EXPANSION

        namespace expansion {

        // ARM NEON - Types - 256-bit

        using int8x32_t  = vector<int8_t,32>;
        using int16x16_t = vector<int16_t,16>;
        using int32x8_t  = vector<int32_t,8>;
        using int64x4_t  = vector<int64_t,4>;

        using uint8x32_t  = vector<uint8_t,32>;
        using uint16x16_t = vector<uint16_t,16>;
        using uint32x8_t = vector<uint32_t,8>;
        using uint64x4_t  = vector<uint64_t,4>;

        using float32x8_t = vector<float,8>;

        // ARM NEON - Types - 512-bit

        using int8x64_t = vector<int8_t,64>;
        using int16x32_t = vector<int16_t,32>;
        using int32x16_t = vector<int32_t,16>;
        using int64x8_t = vector<int64_t,8>;

        using uint8x64_t  = vector<uint8_t,64>;
        using uint16x32_t = vector<uint16_t,32>;
        using uint32x16_t  = vector<uint32_t,16>;
        using uint64x8_t  = vector<uint64_t,8>;

        using float32x16_t = vector<float,16>;

        // ARM NEON - Types - 1024-bit

        using int8x128_t = vector<int8_t,128>;
        using int16x64_t = vector<int16_t,64>;
        using int32x32_t = vector<int32_t,32>;
        using int64x16_t = vector<int64_t,16>;

        using uint8x128_t  = vector<uint8_t,128>;
        using uint16x64_t = vector<uint16_t,64>;
        using uint32x32_t  = vector<uint32_t,32>;
        using uint64x16_t  = vector<uint64_t,16>;

        using float32x32_t = vector<float,32>;

        // ARM NEON - Types - 2048-bit

        using int8x256_t = vector<int8_t,256>;
        using int16x128_t = vector<int16_t,128>;
        using int32x64_t = vector<int32_t,64>;
        using int64x32_t = vector<int64_t,32>;

        using uint8x256_t  = vector<uint8_t,256>;
        using uint16x128_t = vector<uint16_t,128>;
        using uint32x64_t  = vector<uint32_t,64>;
        using uint64x32_t  = vector<uint64_t,32>;

        using float32x64_t = vector<float,64>;

        }

        using namespace expansion;

#endif

        // ARM NEON - vld1 - 64-bit vector //////////////////////////////////////////
        const auto& vld1_u8  = __vld<uint8x8_t, uint8_t>;
        const auto& vld1_u16 = __vld<uint16x4_t,uint16_t>;
        const auto& vld1_u32 = __vld<uint32x2_t,uint32_t>;
        const auto& vld1_u64 = __vld<uint64x1_t,uint64_t>;

        const auto& vld1_s8  = __vld<int8x8_t, int8_t>;
        const auto& vld1_s16 = __vld<int16x4_t,int16_t>;
        const auto& vld1_s32 = __vld<int32x2_t,int32_t>;
        const auto& vld1_s64 = __vld<int64x1_t,int64_t>;

        const auto& vld1_f32 = __vld<float32x2_t, float>;
        /////////////////////////////////////////////////////////////////////////////

        // ARM NEON - vld1 - 128-bit vector //////////////////////////////////////////
        const auto& vld1q_u8  = __vld<uint8x16_t, uint8_t>;
        const auto& vld1q_u16 = __vld<uint16x8_t,uint16_t>;
        const auto& vld1q_u32 = __vld<uint32x4_t,uint32_t>;
        const auto& vld1q_u64 = __vld<uint64x2_t,uint64_t>;

        const auto& vld1q_s8  = __vld<int8x16_t, int8_t>;
        const auto& vld1q_s16 = __vld<int16x8_t,int16_t>;
        const auto& vld1q_s32 = __vld<int32x4_t,int32_t>;
        const auto& vld1q_s64 = __vld<int64x2_t,int64_t>;

        const auto& vld1q_f32 = __vld<float32x4_t, float>;
        /////////////////////////////////////////////////////////////////////////////

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

        const auto& vadd_f32 = __vadd<float32x2_t>;
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


        // ARM NEON - vaddw ///////////////////////////////////////////////////////
        const auto& vaddw_u8  = __vaddw<uint16x8_t, uint8x8_t>;
        const auto& vaddw_u16 = __vaddw<uint32x4_t, uint16x4_t>;
        const auto& vaddw_u32 = __vaddw<uint64x2_t, uint32x2_t>;

        const auto& vaddw_s8  = __vaddw<int16x8_t, int8x8_t>;
        const auto& vaddw_s16 = __vaddw<int32x4_t, int16x4_t>;
        const auto& vaddw_s32 = __vaddw<int64x2_t, int32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vhadd - 64-bit vectors ///////////////////////////////////////////////////////
        const auto& vhadd_u8  = __vhadd<uint8x8_t>;
        const auto& vhadd_u16 = __vhadd<uint16x4_t>;
        const auto& vhadd_u32 = __vhadd<uint32x2_t>;

        const auto& vhadd_s8  = __vhadd<int16x8_t>;
        const auto& vhadd_s16 = __vhadd<int32x4_t>;
        const auto& vhadd_s32 = __vhadd<int64x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vhadd - 128-bit vectors ///////////////////////////////////////////////////////
        const auto& vhaddq_u8  = __vhadd<uint8x16_t>;
        const auto& vhaddq_u16 = __vhadd<uint16x8_t>;
        const auto& vhaddq_u32 = __vhadd<uint32x4_t>;

        const auto& vhaddq_s8  = __vhadd<int8x16_t>;
        const auto& vhaddq_s16 = __vhadd<int16x8_t>;
        const auto& vhaddq_s32 = __vhadd<int32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vqadd - 64-bit vectors ///////////////////////////////////////////////////////
        const auto& vqadd_u8  = __vqadd<uint8x8_t>;
        const auto& vqadd_u16 = __vqadd<uint16x4_t>;
        const auto& vqadd_u32 = __vqadd<uint32x2_t>;
        const auto& vqadd_u64 = __vqadd<uint64x1_t>;

        const auto& vqadd_s8  = __vqadd<int8x8_t>;
        const auto& vqadd_s16 = __vqadd<int16x4_t>;
        const auto& vqadd_s32 = __vqadd<int32x2_t>;
        const auto& vqadd_s64 = __vqadd<int64x1_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vqadd - 128-bit vectors ///////////////////////////////////////////////////////
        const auto& vqaddq_u8  = __vqadd<uint8x16_t>;
        const auto& vqaddq_u16 = __vqadd<uint16x8_t>;
        const auto& vqaddq_u32 = __vqadd<uint32x4_t>;
        const auto& vqaddq_u64 = __vqadd<uint64x2_t>;

        const auto& vqaddq_s8  = __vqadd<int8x16_t>;
        const auto& vqaddq_s16 = __vqadd<int16x8_t>;
        const auto& vqaddq_s32 = __vqadd<int32x4_t>;
        const auto& vqaddq_s64 = __vqadd<int64x2_t>;
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

        const auto& vsub_f32 = __vsub<float32x2_t>;
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

        // ARM NEON - vsubl ///////////////////////////////////////////////////////
        const auto& vsubl_s8  = __vsubl< int8x8_t,int16x8_t>;
        const auto& vsubl_s16 = __vsubl<int16x4_t,int32x4_t>;
        const auto& vsubl_s32 = __vsubl<int32x2_t,int64x2_t>;

        const auto& vsubl_u8  = __vsubl< uint8x8_t,uint16x8_t>;
        const auto& vsubl_u16 = __vsubl<uint16x4_t,uint32x4_t>;
        const auto& vsubl_u32 = __vsubl<uint32x2_t,uint64x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vsubw ///////////////////////////////////////////////////////
        const auto& vsubw_u8  = __vsubw<uint16x8_t, uint8x8_t>;
        const auto& vsubw_u16 = __vsubw<uint32x4_t, uint16x4_t>;
        const auto& vsubw_u32 = __vsubw<uint64x2_t, uint32x2_t>;

        const auto& vsubw_s8  = __vsubw<int16x8_t, int8x8_t>;
        const auto& vsubw_s16 = __vsubw<int32x4_t, int16x4_t>;
        const auto& vsubw_s32 = __vsubw<int64x2_t, int32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vhsub - 64-bit vectors ///////////////////////////////////////////////////////
        const auto& vhsub_u8  = __vhsub<uint8x8_t>;
        const auto& vhsub_u16 = __vhsub<uint16x4_t>;
        const auto& vhsub_u32 = __vhsub<uint32x2_t>;

        const auto& vhsub_s8  = __vhsub<int16x8_t>;
        const auto& vhsub_s16 = __vhsub<int32x4_t>;
        const auto& vhsub_s32 = __vhsub<int64x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vhsub - 128-bit vectors ///////////////////////////////////////////////////////
        const auto& vhsubq_u8  = __vhsub<uint8x16_t>;
        const auto& vhsubq_u16 = __vhsub<uint16x8_t>;
        const auto& vhsubq_u32 = __vhsub<uint32x4_t>;

        const auto& vhsubq_s8  = __vhsub<int8x16_t>;
        const auto& vhsubq_s16 = __vhsub<int16x8_t>;
        const auto& vhsubq_s32 = __vhsub<int32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vmul - 64-bit vectors ///////////////////////////////////////
        const auto& vmul_u8  = __vmul< uint8x8_t>;
        const auto& vmul_u16 = __vmul<uint16x4_t>;
        const auto& vmul_u32 = __vmul<uint32x2_t>;

        const auto& vmul_s8  = __vmul<  int8x8_t>;
        const auto& vmul_s16 = __vmul< int16x4_t>;
        const auto& vmul_s32 = __vmul< int32x2_t>;

        const auto& vmul_f32 = __vmul<float32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vmul - 128-bit vectors //////////////////////////////////////
        const auto& vmulq_u8  = __vmul<uint8x16_t>;
        const auto& vmulq_u16 = __vmul<uint16x8_t>;
        const auto& vmulq_u32 = __vmul<uint32x4_t>;

        const auto& vmulq_s8  = __vmul< int8x16_t>;
        const auto& vmulq_s16 = __vmul< int16x8_t>;
        const auto& vmulq_s32 = __vmul< int32x4_t>;

        const auto& vmulq_f32 = __vmul<float32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vmull ///////////////////////////////////////////////////////
        const auto& vmull_s8  = __vmull< int8x8_t,int16x8_t>;
        const auto& vmull_s16 = __vmull<int16x4_t,int32x4_t>;
        const auto& vmull_s32 = __vmull<int32x2_t,int64x2_t>;

        const auto& vmull_u8  = __vmull< uint8x8_t,uint16x8_t>;
        const auto& vmull_u16 = __vmull<uint16x4_t,uint32x4_t>;
        const auto& vmull_u32 = __vmull<uint32x2_t,uint64x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vmla - 64-bit vector ///////////////////////////////////////////////////////
        const auto& vmla_s8  = __vmla< int8x8_t>;
        const auto& vmla_s16 = __vmla<int16x4_t>;
        const auto& vmla_s32 = __vmla<int32x2_t>;

        const auto& vmla_u8  = __vmla<uint8x8_t>;
        const auto& vmla_u16 = __vmla<uint16x4_t>;
        const auto& vmla_u32 = __vmla<uint32x2_t>;

        const auto& vmla_f32 = __vmla<float32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vmla - 128-bit vector ///////////////////////////////////////////////////////
        const auto& vmlaq_s8  = __vmla<int8x16_t>;
        const auto& vmlaq_s16 = __vmla<int16x8_t>;
        const auto& vmlaq_s32 = __vmla<int32x4_t>;

        const auto& vmlaq_u8  = __vmla<uint8x16_t>;
        const auto& vmlaq_u16 = __vmla<uint16x8_t>;
        const auto& vmlaq_u32 = __vmla<uint32x4_t>;

        const auto& vmlaq_f32 = __vmla<float32x4_t>;
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

        // ARM NEON - vcgt - 64-bit vectors ///////////////////////////////////////
        const auto& vcgt_u8  = __vcgt<   uint8x8_t,  uint8x8_t>;
        const auto& vcgt_u16 = __vcgt<  uint16x4_t, uint16x4_t>;
        const auto& vcgt_u32 = __vcgt<  uint32x2_t, uint32x2_t>;

        const auto& vcgt_s8  = __vcgt<    int8x8_t,  uint8x8_t>;
        const auto& vcgt_s16 = __vcgt<   int16x4_t, uint16x4_t>;
        const auto& vcgt_s32 = __vcgt<   int32x2_t, uint32x2_t>;

        const auto& vcgt_f32 = __vcgt< float32x2_t, uint32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vcgt - 128-bit vectors ///////////////////////////////////////
        const auto& vcgtq_u8  = __vcgt<  uint8x16_t, uint8x16_t>;
        const auto& vcgtq_u16 = __vcgt<  uint16x8_t, uint16x8_t>;
        const auto& vcgtq_u32 = __vcgt<  uint32x4_t, uint32x4_t>;

        const auto& vcgtq_s8  = __vcgt<   int8x16_t, uint8x16_t>;
        const auto& vcgtq_s16 = __vcgt<   int16x8_t, uint16x8_t>;
        const auto& vcgtq_s32 = __vcgt<   int32x4_t, uint32x4_t>;

        const auto& vcgtq_f32 = __vcgt< float32x4_t, uint32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vcge - 64-bit vectors ///////////////////////////////////////
        const auto& vcge_u8  = __vcge<   uint8x8_t,  uint8x8_t>;
        const auto& vcge_u16 = __vcge<  uint16x4_t, uint16x4_t>;
        const auto& vcge_u32 = __vcge<  uint32x2_t, uint32x2_t>;

        const auto& vcge_s8  = __vcge<    int8x8_t,  uint8x8_t>;
        const auto& vcge_s16 = __vcge<   int16x4_t, uint16x4_t>;
        const auto& vcge_s32 = __vcge<   int32x2_t, uint32x2_t>;

        const auto& vcge_f32 = __vcge< float32x2_t, uint32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vcge - 128-bit vectors ///////////////////////////////////////
        const auto& vcgeq_u8  = __vcge<  uint8x16_t, uint8x16_t>;
        const auto& vcgeq_u16 = __vcge<  uint16x8_t, uint16x8_t>;
        const auto& vcgeq_u32 = __vcge<  uint32x4_t, uint32x4_t>;

        const auto& vcgeq_s8  = __vcge<   int8x16_t, uint8x16_t>;
        const auto& vcgeq_s16 = __vcge<   int16x8_t, uint16x8_t>;
        const auto& vcgeq_s32 = __vcge<   int32x4_t, uint32x4_t>;

        const auto& vcgeq_f32 = __vcge< float32x4_t, uint32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vclt - 64-bit vectors ///////////////////////////////////////
        const auto& vclt_u8  = __vclt<   uint8x8_t,  uint8x8_t>;
        const auto& vclt_u16 = __vclt<  uint16x4_t, uint16x4_t>;
        const auto& vclt_u32 = __vclt<  uint32x2_t, uint32x2_t>;

        const auto& vclt_s8  = __vclt<    int8x8_t,  uint8x8_t>;
        const auto& vclt_s16 = __vclt<   int16x4_t, uint16x4_t>;
        const auto& vclt_s32 = __vclt<   int32x2_t, uint32x2_t>;

        const auto& vclt_f32 = __vclt< float32x2_t, uint32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vclt - 128-bit vectors ///////////////////////////////////////
        const auto& vcltq_u8  = __vclt<  uint8x16_t, uint8x16_t>;
        const auto& vcltq_u16 = __vclt<  uint16x8_t, uint16x8_t>;
        const auto& vcltq_u32 = __vclt<  uint32x4_t, uint32x4_t>;

        const auto& vcltq_s8  = __vclt<   int8x16_t, uint8x16_t>;
        const auto& vcltq_s16 = __vclt<   int16x8_t, uint16x8_t>;
        const auto& vcltq_s32 = __vclt<   int32x4_t, uint32x4_t>;

        const auto& vcltq_f32 = __vclt< float32x4_t, uint32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vcle - 64-bit vectors ///////////////////////////////////////
        const auto& vcle_u8  = __vcle<   uint8x8_t,  uint8x8_t>;
        const auto& vcle_u16 = __vcle<  uint16x4_t, uint16x4_t>;
        const auto& vcle_u32 = __vcle<  uint32x2_t, uint32x2_t>;

        const auto& vcle_s8  = __vcle<    int8x8_t,  uint8x8_t>;
        const auto& vcle_s16 = __vcle<   int16x4_t, uint16x4_t>;
        const auto& vcle_s32 = __vcle<   int32x2_t, uint32x2_t>;

        const auto& vcle_f32 = __vcle< float32x2_t, uint32x2_t>;
        ///////////////////////////////////////////////////////////////////////////

        // ARM NEON - vcle - 128-bit vectors ///////////////////////////////////////
        const auto& vcleq_u8  = __vcle<  uint8x16_t, uint8x16_t>;
        const auto& vcleq_u16 = __vcle<  uint16x8_t, uint16x8_t>;
        const auto& vcleq_u32 = __vcle<  uint32x4_t, uint32x4_t>;

        const auto& vcleq_s8  = __vcle<   int8x16_t, uint8x16_t>;
        const auto& vcleq_s16 = __vcle<   int16x8_t, uint16x8_t>;
        const auto& vcleq_s32 = __vcle<   int32x4_t, uint32x4_t>;

        const auto& vcleq_f32 = __vcle< float32x4_t, uint32x4_t>;
        ///////////////////////////////////////////////////////////////////////////

    }

    using namespace arm_neon;

#endif

}

#endif
