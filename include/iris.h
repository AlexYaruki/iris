#ifndef IRIS_H
#define IRIS_H

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <cstring>
#include <type_traits>

namespace iris {

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
                    for(size_t i = 0; i < (sizeof(T)/sizeof(E)/2); i++) {
                        std::swap(result.template at<E>(i),result.template at<E>((sizeof(T)/sizeof(E) - 1 - i)));
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_set1(E x) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = x;
                    }
                    return result;
                }

                template<typename T>
                T ____mm_setzero() {
                    T result;
                    for(size_t i = 0; i < sizeof(T); i++) {
                        result.template at<uint8_t>(i) = 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_unpackhi(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0, j = (sizeof(T)/sizeof(E))/2; i < (sizeof(T)/sizeof(E))/2; i+=2, j++) {
                        target[i]   = v1.template at<E>(j);
                        target[i+1] = v2.template at<E>(j);
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_unpacklo(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0, j = 0; i < (sizeof(T)/sizeof(E))/2; i+=2, j++) {
                        target[i]   = v1.template at<E>(j);
                        target[i+1] = v2.template at<E>(j);
                    }
                    return result;
                }


                template<typename T, typename E>
                T ____mm_cmpeq(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = v1.template at<E>(i) == v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpgt(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = v1.template at<E>(i) > v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpge(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = v1.template at<E>(i) >= v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmplt(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = v1.template at<E>(i) < v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmple(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = v1.template at<E>(i) <= v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpneq(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = v1.template at<E>(i) != v1.template at<E>(i) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpngt(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = !(v1.template at<E>(i) > v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpnge(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = !(v1.template at<E>(i) >= v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpnlt(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        target[i] = !(v1.template at<E>(i) < v1.template at<E>(i)) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpnle(T v1, T v2) {
                    T result;
                    E* target = reinterpret_cast<E*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        bool x = v1.template at<E>(i) == std::numeric_limits<float>::quiet_NaN();
                        bool y = v1.template at<E>(i) == std::numeric_limits<float>::quiet_NaN();
                        result.template at<E>(i) = ( x || y ) ? std::numeric_limits<E>::max() : 0;
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_cmpunord(T v1, T v2){
                    T result;
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                        target[i] = v1.template at<uint8_t>(i) & v2.template at<uint8_t>(i);
                    }
                    return result;
                }

                template<typename T>
                T ____mm_or(T v1, T v2) {
                    T result;
                    uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                        target[i] = v1.template at<uint8_t>(i) | v2.template at<uint8_t>(i);
                    }
                    return result;
                }

                template<typename T>
                T ____mm_xor(T v1, T v2) {
                    T result;
                    uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
                        target[i] = v1.template at<uint8_t>(i) ^ v2.template at<uint8_t>(i);
                    }
                    return result;
                }

                template<typename T>
                T ____mm_andnot(T v1, T v2) {
                    T result;
                    uint8_t* target = reinterpret_cast<uint8_t*>(&result);
                    for(size_t i = 0; i < sizeof(T)/sizeof(uint8_t); i++) {
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
                        for(size_t i = 0; i < sizeof(T)/sizeof(U); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(From); i++){
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(From); i++){
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
                    for(size_t i = 0; i < (sizeof(T)*8 - N); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        result.template at<E>(i) = ____shift_right_zero_extend(v.template at<E>(i),count.template at<int64_t>(0));
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_srli(T v, int32_t imm) {
                    T result;
                    std::memset(&result, 0, sizeof(T));
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        result.template at<E>(i) = ____shift_right_zero_extend(v.template at<E>(i),reinterpret_cast<uint8_t*>(&imm)[0]);
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_sra(T v, T count) {
                    T result;
                    std::memset(&result, 0, sizeof(T));
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        result.template at<E>(i) = ____shift_right_sign_extend(v.template at<E>(i),count.template at<int64_t>(0));
                    }
                    return result;
                }

                template<typename T, typename E>
                T ____mm_srai(T v, int32_t imm) {
                    T result;
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
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
                    for(size_t i = 0; i < sizeof(T)/sizeof(E); i++) {
                        result.template at<E>(i) = e;
                    }
                    return result;
                }
            }

            #ifndef _MSC_VER
                using __int64 = int64_t;
            #endif //_MSC_VER
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

    

}

#include "iris_arm_neon.h"

#endif
