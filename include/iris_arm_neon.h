#include <cmath>
#include "iris_common.h"

namespace iris {

        namespace arm_neon {

            template<typename T, typename E>
            T __vdup(E elem) {
                T result;
                result.setAll(elem);
                return result;
            }

            template<typename T, typename E>
            E __vget_lane(T v, size_t i) {
                return v.template at<E>(i);
            }

            template<typename T>
            T __vset_lane(typename T::elementType x, T v, int32_t i) {
                T result = v;
                result.template at<typename T::elementType>(i) = x;
                return result;
            }

            template<typename T, typename E>
            T __vdup_lane(T v, int32_t i) {
                return __vdup<T,E>(__vget_lane<T,E>(v,i));
            }

            template<typename T>
            T __vld1(const typename T::elementType* src) {
                T result;
                result.setAll(src[0]);
                return result;
            }

            template<typename T>
            T __vld(const typename T::vectorType::elementType * src) {
                T result;
                size_t elementCount = T::lanes * T::vectorType::length;
                for(size_t i = 0; i < elementCount; i++) {
                    result.val[i % T::lanes].template at<typename T::vectorType::elementType>(i/T::lanes) = src[i];
                }
                return result;
            }

            template<typename T>
            T __vld1_lane(typename T::elementType* src, T v, int pos) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    if(i == static_cast<size_t>(pos)) {
                        result.template at<typename T::elementType>(i) = *src;
                    } else {
                        result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>(i);
                    }
                }
                return result;
            }

            template<typename T>
            T __vld_lane(typename T::vectorType::elementType* src, T v, int32_t pos) {
                T result = v;
                for(size_t i = 0, j = 0; i < T::lanes; i++, j++) {
                    result.val[i].template at<typename T::vectorType::elementType>(pos) = src[j];
                }
                return result;
            }

            template<typename T>
            T __vld1_dup(typename T::elementType* src) {
                typename T::elementType x = *src;
                T result = __vdup<T,typename T::elementType>(x);
                return result;
            }

            template<typename T>
            T __vld_dup(typename T::vectorType::elementType* src) {
                T result;
                for(size_t i = 0; i < T::lanes; i++) {
                    result.val[i] = __vld1_dup<typename T::vectorType>(src + i);
                }
                return result;
            }

            template<typename T>
            void __vst1(typename T::elementType* dst, T v) {
                std::memcpy(dst, &v, sizeof(T));
            }

            template<typename T>
            void __vst1_lane(typename T::elementType* dst, T v, int pos) {
                *dst = v.template at<typename T::elementType>(pos);
            }

            template<typename T>
            T __iris__abs(T x) {
                if(x < 0) {
                    return x * static_cast<T>(-1);
                } else {
                    return x;
                }
            }

            template<>
            float __iris__abs(float x) {
                return std::fabs(x);
            }

            template<typename T>
            T __vabs(T v) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = v.template at<typename T::elementType>(i);
                    result.template at<typename T::elementType>(i) = __iris__abs(x);
                }
                return result;
            }

            template<typename T>
            T __iris__qabs(T x) {
                if(x < 0) {
                    T temp = x * static_cast<T>(-1);
                    if(temp > x) {
                        return temp;
                    } else {
                        return std::numeric_limits<T>::max();
                    }
                } else {
                    return x;
                }
            }

            template<>
            float __iris__qabs(float x) {
                return std::abs(x);
            }

            template<typename T>
            T __vqabs(T v) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = v.template at<typename T::elementType>(i);
                    result.template at<typename T::elementType>(i) = __iris__qabs(x);
                }
                return result;
            }

            // ARM NEON - Comparision ///////////////////////////////////////////////////

            template<typename T, typename R>
            R __vceq(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    if(v1.template at<typename T::elementType>(i) == v2.template at<typename T::elementType>(i)) {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                    } else {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                    }
                }
                return result;
            }

            template<typename T, typename R>
            R __vcgt(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    if(v1.template at<typename T::elementType>(i) > v2.template at<typename T::elementType>(i)) {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                    } else {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                    }
                }
                return result;
            }

            template<typename T, typename R>
            R __vcge(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    if(v1.template at<typename T::elementType>(i) >= v2.template at<typename T::elementType>(i)) {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                    } else {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                    }
                }
                return result;
            }

            template<typename T, typename R>
            R __vclt(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    if(v1.template at<typename T::elementType>(i) < v2.template at<typename T::elementType>(i)) {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                    } else {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                    }
                }
                return result;
            }

            template<typename T, typename R>
            R __vcle(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    if(v1.template at<typename T::elementType>(i) <= v2.template at<typename T::elementType>(i)) {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::max();
                    } else {
                        result.template at<typename R::elementType>(i) = std::numeric_limits<typename R::elementType>::min();
                    }
                }
                return result;
            }

            template<typename T, typename R>
            T __vtst(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType temp = v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i);
                    if(temp == 0) {
                        result.template at<typename T::elementType>(i) = 0;
                    } else {
                        result.template at<typename T::elementType>(i) = 1;
                    }
                }
                return result;
            }


            ////

            // ARM NEON - Comparision (absolute)
            template<typename T, typename R>
            R __vcagt(T v1, T v2) {
                return __vcgt<T,R>(__vabs<T>(v1),__vabs<T>(v2));
            }

            template<typename T, typename R>
            R __vcage(T v1, T v2) {
                return __vcge<T,R>(__vabs<T>(v1),__vabs<T>(v2));
            }

            template<typename T, typename R>
            R __vcalt(T v1, T v2) {
                return __vclt<T,R>(__vabs<T>(v1),__vabs<T>(v2));
            }

            template<typename T, typename R>
            R __vcale(T v1, T v2) {
                return __vcle<T,R>(__vabs<T>(v1),__vabs<T>(v2));
            }

            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - Bitwise ///////////////////////////////////////////////////////

            /*

            vmvn
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
                    typename R::elementType x = static_cast<typename R::elementType>(v1.template at<typename T::elementType>(i));
                    typename R::elementType y = static_cast<typename R::elementType>(v2.template at<typename T::elementType>(i));
                    result.template at<typename R::elementType>(i) = x + y;
                }
                return result;
            }

            template<typename R, typename T>
            R __vaddw(R v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    typename R::elementType x = static_cast<typename R::elementType>(v2.template at<typename T::elementType>(i));
                    result.template at<typename R::elementType>(i) = v1.template at<typename R::elementType>(i) + x;
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
            T __vrhadd(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = (v1.template at<typename T::elementType>(i) + v2.template at<typename T::elementType>(i));
                    if((x >> 1) * 2 == x) {
                        x = x >> 1;
                    } else {
                        x = (x >> 1) + 1;
                    }
                    result.template at<typename T::elementType>(i) = x;
                }
                return result;
            }

            template<typename T>
            T __vqadd(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    auto x = v1.template at<typename T::elementType>(i);
                    auto y = v2.template at<typename T::elementType>(i);
                    if((y > 0) && (x > std::numeric_limits<typename T::elementType>::max() - y)) {
                        result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
                    } else if ((x < 0) && (y < std::numeric_limits<typename T::elementType>::max() - y)) {
                        result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
                    } else {
                        result.template at<typename T::elementType>(i) = x + y;
                    }
                }
                return result;
            }

            template<typename T, typename R>
            R __vaddhn(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    auto x = v1.template at<typename T::elementType>(i);
                    auto y = v2.template at<typename T::elementType>(i);
                    auto temp = x + y;
                    auto part = reinterpret_cast<typename R::elementType*>(&temp)[1];
                    result.template at<typename R::elementType>(i) = part;
                }
                return result;
            }

            template<typename T, typename R>
            R __vraddhn(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    auto x = v1.template at<typename T::elementType>(i);
                    auto y = v2.template at<typename T::elementType>(i);
                    typename T::elementType sum = 0;
                    if((x > 0) && (y > std::numeric_limits<typename T::elementType>::max() - x)) {
                        sum = std::numeric_limits<typename T::elementType>::max();
                    } else if ((x < 0) && (y < std::numeric_limits<typename T::elementType>::min() - x)) {
                        sum = std::numeric_limits<typename T::elementType>::min();
                    } else {
                        sum = x + y;
                    }
                    auto part = reinterpret_cast<typename R::elementType*>(&sum)[1];
                    result.template at<typename R::elementType>(i) = part;
                }
                return result;
            }

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
                    if((y > 0) && (x < std::numeric_limits<typename T::elementType>::min() + y)) {
                        result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::min();
                    } else if ((y < 0) && (x > std::numeric_limits<typename T::elementType>::max() + y)) {
                        result.template at<typename T::elementType>(i) = std::numeric_limits<typename T::elementType>::max();
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

            template<typename T>
            T __vmul_lane(T v1, T v2, int32_t x) {
                T p = __vdup_lane<T,typename T::elementType>(v2,x);
                return __vmul(v1, p);
            }

            // ARM NEON - Multiplication-Accumulate /////////////////////////////////////

            template<typename T>
            T __vmla(T v1, T v2, T v3) {
                return __vadd(v3, __vmul(v1, v2));
            }

            template<typename T, typename R>
            R __vmlal(T v1, T v2, T v3) {
                R result = __vmull<T,R>(v1,v2);
                return __vaddw(result,v3);
            }

            template<typename T>
            T __vmla_n(T v1, T v2, typename T::elementType x) {
                auto p = __vdup<T,typename T::elementType>(x);
                return __vadd(v1, __vmul(v2, p));
            }

            template<typename T>
            T __vmla_lane(T v1, T v2, T v3, int32_t x) {
                auto p = __vdup_lane<T,typename T::elementType>(v3,x);
                return __vadd(v1, __vmul(v2, p));
            }

            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - Multiplication-Subtract ///////////////////////////////////////

            template<typename T>
            T __vmls(T v1, T v2, T v3) {
                return __vsub(v3, __vmul(v1, v2));
            }

            template<typename T>
            T __vmls_n(T v1, T v2, typename T::elementType x) {
                auto p = __vdup<T,typename T::elementType>(x);
                return __vsub(v1, __vmul(v2, p));
            }

            template<typename T>
            T __vmls_lane(T v1, T v2, T v3, int32_t x) {
                auto p = __vdup_lane<T,typename T::elementType>(v3,x);
                return __vsub(v1, __vmul(v2, p));
            }

            template<typename T, typename R>
            R __vmlsl(T v1, T v2, T v3) {
                R result = __vmull<T,R>(v1,v2);
                return __vsubw(result,v3);
            }
            /////////////////////////////////////////////////////////////////////////////

            template <typename T>
            T __vmul_n(T v, typename T::elementType x) {
                return __vmul(v,__vdup<T,typename T::elementType>(x));
            }

            template<typename T>
            T __vmin(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) < v2.template at<typename T::elementType>(i) ? v1.template at<typename T::elementType>(i) : v2.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T>
            T __vmax(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) > v2.template at<typename T::elementType>(i) ? v1.template at<typename T::elementType>(i) : v2.template at<typename T::elementType>(i);
                }
                return result;
            }



            template<typename T, typename R>
            typename std::enable_if<sizeof(T)/2 == sizeof(R),R>::type __vget_high(T v) {
                R result;
                for(size_t i = T::length/2, j = 0; i < T::length; i++, j++) {
                    result.template at<typename R::elementType>(j) = v.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T, typename R>
            typename std::enable_if<sizeof(T)/2 == sizeof(R),R>::type __vget_low(T v) {
                R result;
                for(size_t i = 0; i < R::length; i++) {
                    result.template at<typename R::elementType>(i) = v.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T, typename R>
            typename std::enable_if<sizeof(T)*2 == sizeof(R),R>::type __vcombine(T v1, T v2) {
                R result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<typename R::elementType>(i) = v1.template at<typename T::elementType>(i);
                }
                for(size_t i = 0, j = T::length; i < T::length; i++, j++) {
                    result.template at<typename R::elementType>(j) = v2.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T>
            T __vrev64(typename std::enable_if<sizeof(typename T::elementType) < 8,T>::type v) {
                T result;
                const size_t packs = (T::length * sizeof(typename T::elementType))/8;
                const size_t elementsPerPack = T::length/packs;
                for(size_t j = 0; j < packs; j++) {
                    for(size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j+1) ; i++, k++) {
                        result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>((elementsPerPack * (j+1)) - (k + 1));
                    }
                }
                return result;
            }

            template<typename T>
            T __vrev32(typename std::enable_if<sizeof(typename T::elementType) < 4,T>::type v) {
                T result;
                const size_t packs = (T::length * sizeof(typename T::elementType))/4;
                const size_t elementsPerPack = T::length/packs;
                for(size_t j = 0; j < packs; j++) {
                    for(size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j+1) ; i++, k++) {
                        result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>((elementsPerPack * (j+1)) - (k + 1));
                    }
                }
                return result;
            }

            template<typename T>
            T __vrev16(typename std::enable_if<sizeof(typename T::elementType) < 2,T>::type v) {
                T result;
                const size_t packs = (T::length * sizeof(typename T::elementType))/2;
                const size_t elementsPerPack = T::length/packs;
                for(size_t j = 0; j < packs; j++) {
                    for(size_t i = elementsPerPack * j, k = 0; i < elementsPerPack * (j+1) ; i++, k++) {
                        result.template at<typename T::elementType>(i) = v.template at<typename T::elementType>((elementsPerPack * (j+1)) - (k + 1));
                    }
                }
                return result;
            }

            template<typename T>
            T __vext(T v1, T v2, int32_t n) {
                T result;
                for(int32_t i = 0; i <= n; i++) {
                    result.template at<typename T::elementType>(i) = v2.template at<typename T::elementType>(i);
                }
                for(int32_t i = n+1, j = T::length - 1; (size_t)i < T::length; i++, j--) {
                    result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(j);
                }
                return result;
            }

            template<typename T>
            T __vand(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T>
            T __vorr(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) | v2.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T>
            T __veor(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    result.template at<typename T::elementType>(i) = v1.template at<typename T::elementType>(i) ^ v2.template at<typename T::elementType>(i);
                }
                return result;
            }

            template<typename T>
            T __vbic(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = ~(v1.template at<typename T::elementType>(i) & v2.template at<typename T::elementType>(i));
                    result.template at<typename T::elementType>(i) = x;
                }
                return result;
            }

            template<typename T>
            T __vorn(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = ~(v1.template at<typename T::elementType>(i) | v2.template at<typename T::elementType>(i));
                    result.template at<typename T::elementType>(i) = x;
                }
                return result;
            }

            template<typename T>
            T __vneg(T v) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = v.template at<typename T::elementType>(i);
                    result.template at<typename T::elementType>(i) = -x;
                }
                return result;
            }
            
            template<typename T>
            T __vqneg(T v) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType x = v.template at<typename T::elementType>(i);
                    if(x == std::numeric_limits<typename T::elementType>::min()) {
                        x = -std::numeric_limits<typename T::elementType>::max();
                    } else {
                        x = -x;
                    }
                    result.template at<typename T::elementType>(i) = x;
                }
                return result;
            }

            template<typename T>
            T __vshl(T v1, T v2) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType value = v1.template at<typename T::elementType>(i);
                    typename T::elementType shift = v2.template at<typename T::elementType>(i);
                    if(std::numeric_limits<typename T::elementType>::is_signed && shift < 0) {
                        result.template at<typename T::elementType>(i) = value >> -shift;
                    } else {
                        result.template at<typename T::elementType>(i) = value << shift;
                    }
                }
                return result;
            }

            template<typename T>
            T __vshl_n(T v, uint32_t shift) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType value = v.template at<typename T::elementType>(i);
                    result.template at<typename T::elementType>(i) = value << shift;
                }
                return result;
            
            }

            template<typename T>
            T __vshr_n(T v, uint32_t shift) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType value = v.template at<typename T::elementType>(i);
                    result.template at<typename T::elementType>(i) = value >> shift;
                }
                return result;
            }
            
            template<typename T>
            T __vrshr_n(T v, uint32_t shift) {
                T result;
                for(size_t i = 0; i < T::length; i++) {
                    typename T::elementType value = v.template at<typename T::elementType>(i);
                    if(value % 2 != 0) {
                        value = value + 1;
                    }
                    typename T::elementType part = value >> shift;
                    result.template at<typename T::elementType>(i) = part;
                }
                return result;
            }


            template <typename T, typename R>
            typename std::enable_if<T::length == R::length,R>::type __vcvt(T v) {
                R result;
                for(size_t i = 0; i < R::length; i++) {
                    result.template at<typename R::elementType>(i) = static_cast<typename R::elementType>(v.template at<typename T::elementType>(i));
                }
                return result;
            }

            template <typename T, typename R>
            typename std::enable_if<T::length == R::length,R>::type __vcvt_n(T v, int32_t x) {
                T p = __vdup_lane<T,typename T::elementType>(v,x);
                return __vcvt<T,R>(p);
            }

            // ARM NEON - Types - 64-bit

            using int8x8_t  = common::vector<int8_t,8>;
            using int8x8x2_t = common::multi_vector<int8x8_t,2>;
            using int8x8x3_t = common::multi_vector<int8x8_t,3>;
            using int8x8x4_t = common::multi_vector<int8x8_t,4>;

            using int16x4_t = common::vector<int16_t,4>;
            using int16x4x2_t = common::multi_vector<int16x4_t,2>;
            using int16x4x3_t = common::multi_vector<int16x4_t,3>;
            using int16x4x4_t = common::multi_vector<int16x4_t,4>;

            using int32x2_t = common::vector<int32_t,2>;
            using int32x2x2_t = common::multi_vector<int32x2_t,2>;
            using int32x2x3_t = common::multi_vector<int32x2_t,3>;
            using int32x2x4_t = common::multi_vector<int32x2_t,4>;

            using int64x1_t = common::vector<int64_t,1>;
            using int64x1x2_t = common::multi_vector<int64x1_t,2>;
            using int64x1x3_t = common::multi_vector<int64x1_t,3>;
            using int64x1x4_t = common::multi_vector<int64x1_t,4>;

            using uint8x8_t  = common::vector<uint8_t,8>;
            using uint8x8x2_t = common::multi_vector<uint8x8_t,2>;
            using uint8x8x3_t = common::multi_vector<uint8x8_t,3>;
            using uint8x8x4_t = common::multi_vector<uint8x8_t,4>;

            using uint16x4_t = common::vector<uint16_t,4>;
            using uint16x4x2_t = common::multi_vector<uint16x4_t,2>;
            using uint16x4x3_t = common::multi_vector<uint16x4_t,3>;
            using uint16x4x4_t = common::multi_vector<uint16x4_t,4>;

            using uint32x2_t = common::vector<uint32_t,2>;
            using uint32x2x2_t = common::multi_vector<uint32x2_t,2>;
            using uint32x2x3_t = common::multi_vector<uint32x2_t,3>;
            using uint32x2x4_t = common::multi_vector<uint32x2_t,4>;

            using uint64x1_t = common::vector<uint64_t,1>;
            using uint64x1x2_t = common::multi_vector<uint64x1_t,2>;
            using uint64x1x3_t = common::multi_vector<uint64x1_t,3>;
            using uint64x1x4_t = common::multi_vector<uint64x1_t,4>;

            using float32x2_t = common::vector<float,2>;
            using float32x2x2_t = common::multi_vector<float32x2_t,2>;
            using float32x2x3_t = common::multi_vector<float32x2_t,3>;
            using float32x2x4_t = common::multi_vector<float32x2_t,4>;

            // ARM NEON - Types - 128-bit

            using int8x16_t = common::vector<int8_t,16>;
            using int8x16x2_t = common::multi_vector<int8x16_t,2>;
            using int8x16x3_t = common::multi_vector<int8x16_t,3>;
            using int8x16x4_t = common::multi_vector<int8x16_t,4>;

            using int16x8_t = common::vector<int16_t,8>;
            using int16x8x2_t = common::multi_vector<int16x8_t,2>;
            using int16x8x3_t = common::multi_vector<int16x8_t,3>;
            using int16x8x4_t = common::multi_vector<int16x8_t,4>;

            using int32x4_t = common::vector<int32_t,4>;
            using int32x4x2_t = common::multi_vector<int32x4_t,2>;
            using int32x4x3_t = common::multi_vector<int32x4_t,3>;
            using int32x4x4_t = common::multi_vector<int32x4_t,4>;

            using int64x2_t = common::vector<int64_t,2>;
            using int64x2x2_t = common::multi_vector<int64x2_t,2>;
            using int64x2x3_t = common::multi_vector<int64x2_t,3>;
            using int64x2x4_t = common::multi_vector<int64x2_t,4>;

            using uint8x16_t = common::vector<uint8_t,16>;
            using uint8x16x2_t = common::multi_vector<uint8x16_t,2>;
            using uint8x16x3_t = common::multi_vector<uint8x16_t,3>;
            using uint8x16x4_t = common::multi_vector<uint8x16_t,4>;

            using uint16x8_t = common::vector<uint16_t,8>;
            using uint16x8x2_t = common::multi_vector<uint16x8_t,2>;
            using uint16x8x3_t = common::multi_vector<uint16x8_t,3>;
            using uint16x8x4_t = common::multi_vector<uint16x8_t,4>;

            using uint32x4_t = common::vector<uint32_t,4>;
            using uint32x4x2_t = common::multi_vector<uint32x4_t,2>;
            using uint32x4x3_t = common::multi_vector<uint32x4_t,3>;
            using uint32x4x4_t = common::multi_vector<uint32x4_t,4>;

            using uint64x2_t = common::vector<uint64_t,2>;
            using uint64x2x2_t = common::multi_vector<uint64x2_t,2>;
            using uint64x2x3_t = common::multi_vector<uint64x2_t,3>;
            using uint64x2x4_t = common::multi_vector<uint64x2_t,4>;

            using float32x4_t = common::vector<float,4>;
            using float32x4x2_t = common::multi_vector<float32x4_t,2>;
            using float32x4x3_t = common::multi_vector<float32x4_t,3>;
            using float32x4x4_t = common::multi_vector<float32x4_t,4>;


            const auto& vcvt_f32_u32 = __vcvt<float32x2_t,uint32x2_t>;
            const auto& vcvt_f32_s32 = __vcvt<float32x2_t, int32x2_t>;
            const auto& vcvt_s32_f32 = __vcvt< int32x2_t,float32x2_t>;
            const auto& vcvt_u32_f32 = __vcvt<uint32x2_t,float32x2_t>;

            const auto& vcvtq_f32_u32 = __vcvt<float32x4_t,uint32x4_t>;
            const auto& vcvtq_f32_s32 = __vcvt<float32x4_t, int32x4_t>;
            const auto& vcvtq_s32_f32 = __vcvt< int32x4_t,float32x4_t>;
            const auto& vcvtq_u32_f32 = __vcvt<uint32x4_t,float32x4_t>;

            const auto& vcvt_n_f32_u32 = __vcvt_n<float32x2_t,uint32x2_t>;
            const auto& vcvt_n_f32_s32 = __vcvt_n<float32x2_t, int32x2_t>;
            const auto& vcvt_n_s32_f32 = __vcvt_n< int32x2_t,float32x2_t>;
            const auto& vcvt_n_u32_f32 = __vcvt_n<uint32x2_t,float32x2_t>;

            const auto& vcvtq_n_f32_u32 = __vcvt_n<float32x4_t,uint32x4_t>;
            const auto& vcvtq_n_f32_s32 = __vcvt_n<float32x4_t, int32x4_t>;
            const auto& vcvtq_n_s32_f32 = __vcvt_n< int32x4_t,float32x4_t>;
            const auto& vcvtq_n_u32_f32 = __vcvt_n<uint32x4_t,float32x4_t>;

            // ARM NEON - vmul_n - 64-bit vector ///////////////////////////////////
            const auto& vmul_n_s16 = __vmul_n<int16x4_t>;
            const auto& vmul_n_s32 = __vmul_n<int32x2_t>;

            const auto& vmul_n_u16 = __vmul_n<uint16x4_t>;
            const auto& vmul_n_u32 = __vmul_n<uint32x2_t>;

            const auto& vmul_n_f32 = __vmul_n<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmul_n - 128-bit vector ///////////////////////////////////
            const auto& vmulq_n_s16 = __vmul_n<int16x8_t>;
            const auto& vmulq_n_s32 = __vmul_n<int32x4_t>;

            const auto& vmulq_n_u16 = __vmul_n<uint16x8_t>;
            const auto& vmulq_n_u32 = __vmul_n<uint32x4_t>;

            const auto& vmulq_n_f32 = __vmul_n<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmul_lane - 64-bit vector ///////////////////////////////////
            const auto& vmul_lane_s16 = __vmul_lane<int16x4_t>;
            const auto& vmul_lane_s32 = __vmul_lane<int32x2_t>;

            const auto& vmul_lane_u16 = __vmul_lane<uint16x4_t>;
            const auto& vmul_lane_u32 = __vmul_lane<uint32x2_t>;

            const auto& vmul_lane_f32 = __vmul_lane<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmul_lane - 128-bit vector ///////////////////////////////////
            const auto& vmulq_lane_s16 = __vmul_lane<int16x8_t>;
            const auto& vmulq_lane_s32 = __vmul_lane<int32x4_t>;

            const auto& vmulq_lane_u16 = __vmul_lane<uint16x8_t>;
            const auto& vmulq_lane_u32 = __vmul_lane<uint32x4_t>;

            const auto& vmulq_lane_f32 = __vmul_lane<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////


            // ARM NEON - vorr - 64-bit vector /////////////////////////////////////
            const auto& vorr_s8  = __vorr<int8x8_t>;
            const auto& vorr_s16 = __vorr<int16x4_t>;
            const auto& vorr_s32 = __vorr<int32x2_t>;
            const auto& vorr_s64 = __vorr<int64x1_t>;

            const auto& vorr_u8  = __vorr<uint8x8_t>;
            const auto& vorr_u16 = __vorr<uint16x4_t>;
            const auto& vorr_u32 = __vorr<uint32x2_t>;
            const auto& vorr_u64 = __vorr<uint64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vorr - 128-bit vector /////////////////////////////////////
            const auto& vorrq_s8  = __vorr<int8x16_t>;
            const auto& vorrq_s16 = __vorr<int16x8_t>;
            const auto& vorrq_s32 = __vorr<int32x4_t>;
            const auto& vorrq_s64 = __vorr<int64x2_t>;

            const auto& vorrq_u8  = __vorr<uint8x16_t>;
            const auto& vorrq_u16 = __vorr<uint16x8_t>;
            const auto& vorrq_u32 = __vorr<uint32x4_t>;
            const auto& vorrq_u64 = __vorr<uint64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vand - 64-bit vector /////////////////////////////////////
            const auto& vand_s8  = __vand<int8x8_t>;
            const auto& vand_s16 = __vand<int16x4_t>;
            const auto& vand_s32 = __vand<int32x2_t>;
            const auto& vand_s64 = __vand<int64x1_t>;

            const auto& vand_u8  = __vand<uint8x8_t>;
            const auto& vand_u16 = __vand<uint16x4_t>;
            const auto& vand_u32 = __vand<uint32x2_t>;
            const auto& vand_u64 = __vand<uint64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vand - 128-bit vector /////////////////////////////////////
            const auto& vandq_s8  = __vand<int8x16_t>;
            const auto& vandq_s16 = __vand<int16x8_t>;
            const auto& vandq_s32 = __vand<int32x4_t>;
            const auto& vandq_s64 = __vand<int64x2_t>;

            const auto& vandq_u8  = __vand<uint8x16_t>;
            const auto& vandq_u16 = __vand<uint16x8_t>;
            const auto& vandq_u32 = __vand<uint32x4_t>;
            const auto& vandq_u64 = __vand<uint64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - veor - 64-bit vector /////////////////////////////////////
            const auto& veor_s8  = __veor<int8x8_t>;
            const auto& veor_s16 = __veor<int16x4_t>;
            const auto& veor_s32 = __veor<int32x2_t>;
            const auto& veor_s64 = __veor<int64x1_t>;

            const auto& veor_u8  = __veor<uint8x8_t>;
            const auto& veor_u16 = __veor<uint16x4_t>;
            const auto& veor_u32 = __veor<uint32x2_t>;
            const auto& veor_u64 = __veor<uint64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - veor - 128-bit vector /////////////////////////////////////
            const auto& veorq_s8  = __veor<int8x16_t>;
            const auto& veorq_s16 = __veor<int16x8_t>;
            const auto& veorq_s32 = __veor<int32x4_t>;
            const auto& veorq_s64 = __veor<int64x2_t>;

            const auto& veorq_u8  = __veor<uint8x16_t>;
            const auto& veorq_u16 = __veor<uint16x8_t>;
            const auto& veorq_u32 = __veor<uint32x4_t>;
            const auto& veorq_u64 = __veor<uint64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vbic - 64-bit vector /////////////////////////////////////
            const auto& vbic_s8  = __vbic<int8x8_t>;
            const auto& vbic_s16 = __vbic<int16x4_t>;
            const auto& vbic_s32 = __vbic<int32x2_t>;
            const auto& vbic_s64 = __vbic<int64x1_t>;

            const auto& vbic_u8  = __vbic<uint8x8_t>;
            const auto& vbic_u16 = __vbic<uint16x4_t>;
            const auto& vbic_u32 = __vbic<uint32x2_t>;
            const auto& vbic_u64 = __vbic<uint64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vbic - 128-bit vector /////////////////////////////////////
            const auto& vbicq_s8  = __vbic<int8x16_t>;
            const auto& vbicq_s16 = __vbic<int16x8_t>;
            const auto& vbicq_s32 = __vbic<int32x4_t>;
            const auto& vbicq_s64 = __vbic<int64x2_t>;

            const auto& vbicq_u8  = __vbic<uint8x16_t>;
            const auto& vbicq_u16 = __vbic<uint16x8_t>;
            const auto& vbicq_u32 = __vbic<uint32x4_t>;
            const auto& vbicq_u64 = __vbic<uint64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vorn - 64-bit vector /////////////////////////////////////
            const auto& vorn_s8  = __vorn<int8x8_t>;
            const auto& vorn_s16 = __vorn<int16x4_t>;
            const auto& vorn_s32 = __vorn<int32x2_t>;
            const auto& vorn_s64 = __vorn<int64x1_t>;

            const auto& vorn_u8  = __vorn<uint8x8_t>;
            const auto& vorn_u16 = __vorn<uint16x4_t>;
            const auto& vorn_u32 = __vorn<uint32x2_t>;
            const auto& vorn_u64 = __vorn<uint64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vorn - 128-bit vector /////////////////////////////////////
            const auto& vornq_s8  = __vorn<int8x16_t>;
            const auto& vornq_s16 = __vorn<int16x8_t>;
            const auto& vornq_s32 = __vorn<int32x4_t>;
            const auto& vornq_s64 = __vorn<int64x2_t>;

            const auto& vornq_u8  = __vorn<uint8x16_t>;
            const auto& vornq_u16 = __vorn<uint16x8_t>;
            const auto& vornq_u32 = __vorn<uint32x4_t>;
            const auto& vornq_u64 = __vorn<uint64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vneg - 64-bit vector /////////////////////////////////////
            const auto& vneg_s8  = __vneg<int8x8_t>;
            const auto& vneg_s16 = __vneg<int16x4_t>;
            const auto& vneg_s32 = __vneg<int32x2_t>;
            const auto& vneg_f32 = __vneg<float32x2_t>;

            const auto& vnegq_s8  = __vneg<int8x16_t>;
            const auto& vnegq_s16 = __vneg<int16x8_t>;
            const auto& vnegq_s32 = __vneg<int32x4_t>;
            const auto& vnegq_f32 = __vneg<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////
            
            // ARM NEON - vqneg - 64-bit vector ////////////////////////////////////
            const auto& vqneg_s8  = __vqneg<int8x8_t>;
            const auto& vqneg_s16 = __vqneg<int16x4_t>;
            const auto& vqneg_s32 = __vqneg<int32x2_t>;
            ////////////////////////////////////////////////////////////////////////
            
            // ARM NEON - vqneg - 64-bit vector ////////////////////////////////////
            const auto& vqnegq_s8  = __vqneg<int8x16_t>;
            const auto& vqnegq_s16 = __vqneg<int16x8_t>;
            const auto& vqnegq_s32 = __vqneg<int32x4_t>;
            ////////////////////////////////////////////////////////////////////////
            
            // ARM NEON - vext - 64-bit vector /////////////////////////////////////
            const auto& vext_s8  = __vext<int8x8_t>;
            const auto& vext_s16 = __vext<int16x4_t>;
            const auto& vext_s32 = __vext<int32x2_t>;
            const auto& vext_s64 = __vext<int64x1_t>;

            const auto& vext_u8  = __vext<uint8x8_t>;
            const auto& vext_u16 = __vext<uint16x4_t>;
            const auto& vext_u32 = __vext<uint32x2_t>;
            const auto& vext_u64 = __vext<uint64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vext - 128-bit vector /////////////////////////////////////
            const auto& vextq_s8  = __vext<int8x16_t>;
            const auto& vextq_s16 = __vext<int16x8_t>;
            const auto& vextq_s32 = __vext<int32x4_t>;
            const auto& vextq_s64 = __vext<int64x2_t>;

            const auto& vextq_u8  = __vext<uint8x16_t>;
            const auto& vextq_u16 = __vext<uint16x8_t>;
            const auto& vextq_u32 = __vext<uint32x4_t>;
            const auto& vextq_u64 = __vext<uint64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrev64 - 64-bit vector /////////////////////////////////////
            const auto& vrev64_s8  = __vrev64< int8x8_t>;
            const auto& vrev64_s16 = __vrev64<int16x4_t>;
            const auto& vrev64_s32 = __vrev64<int32x2_t>;

            const auto& vrev64_u8  = __vrev64< uint8x8_t>;
            const auto& vrev64_u16 = __vrev64<uint16x4_t>;
            const auto& vrev64_u32 = __vrev64<uint32x2_t>;

            const auto& vrev64_f32 = __vrev64<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrev64 - 128-bit vector //////////////////////////////////
            const auto& vrev64q_s8  = __vrev64<int8x16_t>;
            const auto& vrev64q_s16 = __vrev64<int16x8_t>;
            const auto& vrev64q_s32 = __vrev64<int32x4_t>;

            const auto& vrev64q_u8  = __vrev64<uint8x16_t>;
            const auto& vrev64q_u16 = __vrev64<uint16x8_t>;
            const auto& vrev64q_u32 = __vrev64<uint32x4_t>;

            const auto& vrev64q_f32 = __vrev64<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrev32 - 64-bit vector ///////////////////////////////////
            const auto& vrev32_s8  = __vrev32< int8x8_t>;
            const auto& vrev32_s16 = __vrev32<int16x4_t>;

            const auto& vrev32_u8  = __vrev32< uint8x8_t>;
            const auto& vrev32_u16 = __vrev32<uint16x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrev32 - 128-bit vector ///////////////////////////////////
            const auto& vrev32q_s8  = __vrev32<int8x16_t>;
            const auto& vrev32q_s16 = __vrev32<int16x8_t>;

            const auto& vrev32q_u8  = __vrev32<uint8x16_t>;
            const auto& vrev32q_u16 = __vrev32<uint16x8_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrev16 - 64-bit vector ///////////////////////////////////
            const auto& vrev16_s8  = __vrev16< int8x8_t>;
            const auto& vrev16_u8  = __vrev16< uint8x8_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrev16 - 128-bit vector ///////////////////////////////////
            const auto& vrev16q_s8  = __vrev16<int8x16_t>;
            const auto& vrev16q_u8  = __vrev16<uint8x16_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM_NEON - vcombine /////////////////////////////////////////////////
            const auto& vcombine_s8  = __vcombine< int8x8_t,int8x16_t>;
            const auto& vcombine_s16 = __vcombine<int16x4_t,int16x8_t>;
            const auto& vcombine_s32 = __vcombine<int32x2_t,int32x4_t>;
            const auto& vcombine_s64 = __vcombine<int64x1_t,int64x2_t>;

            const auto& vcombine_u8  = __vcombine< uint8x8_t,uint8x16_t>;
            const auto& vcombine_u16 = __vcombine<uint16x4_t,uint16x8_t>;
            const auto& vcombine_u32 = __vcombine<uint32x2_t,uint32x4_t>;
            const auto& vcombine_u64 = __vcombine<uint64x1_t,uint64x2_t>;

            const auto& vcombine_f32 = __vcombine<float32x2_t,float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vget_low /////////////////////////////////////////////////
            const auto& vget_low_s8  = __vget_low<int8x16_t,int8x8_t>;
            const auto& vget_low_s16 = __vget_low<int16x8_t,int16x4_t>;
            const auto& vget_low_s32 = __vget_low<int32x4_t,int32x2_t>;
            const auto& vget_low_s64 = __vget_low<int64x2_t,int64x1_t>;

            const auto& vget_low_u8  = __vget_low<uint8x16_t,uint8x8_t>;
            const auto& vget_low_u16 = __vget_low<uint16x8_t,uint16x4_t>;
            const auto& vget_low_u32 = __vget_low<uint32x4_t,uint32x2_t>;
            const auto& vget_low_u64 = __vget_low<uint64x2_t,uint64x1_t>;

            const auto& vget_low_f32 = __vget_low<float32x4_t,float32x2_t>;
            /////////////////////////////////////////////////////////////////////////

            // ARM NEON - vget_high /////////////////////////////////////////////////
            const auto& vget_high_s8  = __vget_high<int8x16_t,int8x8_t>;
            const auto& vget_high_s16 = __vget_high<int16x8_t,int16x4_t>;
            const auto& vget_high_s32 = __vget_high<int32x4_t,int32x2_t>;
            const auto& vget_high_s64 = __vget_high<int64x2_t,int64x1_t>;

            const auto& vget_high_u8  = __vget_high<uint8x16_t,uint8x8_t>;
            const auto& vget_high_u16 = __vget_high<uint16x8_t,uint16x4_t>;
            const auto& vget_high_u32 = __vget_high<uint32x4_t,uint32x2_t>;
            const auto& vget_high_u64 = __vget_high<uint64x2_t,uint64x1_t>;

            const auto& vget_high_f32 = __vget_high<float32x4_t,float32x2_t>;
            /////////////////////////////////////////////////////////////////////////

            // ARM_NEON - vabs - 64-bit vector //////////////////////////////////////
            const auto& vabs_s8 = __vabs<int8x8_t>;
            const auto& vabs_s16 = __vabs<int16x4_t>;
            const auto& vabs_s32 = __vabs<int32x2_t>;
            const auto& vabs_f32 = __vabs<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM_NEON - vabs - 64-bit vector /////////////////////////////////////
            const auto& vabsq_s8  = __vabs<int8x16_t>;
            const auto& vabsq_s16 = __vabs<int16x8_t>;
            const auto& vabsq_s32 = __vabs<int32x4_t>;
            const auto& vabsq_f32 = __vabs<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM_NEON - vqabs - 64-bit vector /////////////////////////////////////
            const auto& vqabs_s8 = __vqabs<int8x8_t>;
            const auto& vqabs_s16 = __vqabs<int16x4_t>;
            const auto& vqabs_s32 = __vqabs<int32x2_t>;
            const auto& vqabs_f32 = __vqabs<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM_NEON - vqabs - 64-bit vector /////////////////////////////////////
            const auto& vqabsq_s8  = __vqabs<int8x16_t>;
            const auto& vqabsq_s16 = __vqabs<int16x8_t>;
            const auto& vqabsq_s32 = __vqabs<int32x4_t>;
            const auto& vqabsq_f32 = __vqabs<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld1 - 64-bit vector //////////////////////////////////////////
            const auto& vld1_u8  = __vld1<uint8x8_t>;
            const auto& vld1_u16 = __vld1<uint16x4_t>;
            const auto& vld1_u32 = __vld1<uint32x2_t>;
            const auto& vld1_u64 = __vld1<uint64x1_t>;

            const auto& vld1_s8  = __vld1<int8x8_t>;
            const auto& vld1_s16 = __vld1<int16x4_t>;
            const auto& vld1_s32 = __vld1<int32x2_t>;
            const auto& vld1_s64 = __vld1<int64x1_t>;

            const auto& vld1_f32 = __vld1<float32x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld1 - 128-bit vector //////////////////////////////////////////
            const auto& vld1q_u8  = __vld1<uint8x16_t>;
            const auto& vld1q_u16 = __vld1<uint16x8_t>;
            const auto& vld1q_u32 = __vld1<uint32x4_t>;
            const auto& vld1q_u64 = __vld1<uint64x2_t>;

            const auto& vld1q_s8  = __vld1<int8x16_t>;
            const auto& vld1q_s16 = __vld1<int16x8_t>;
            const auto& vld1q_s32 = __vld1<int32x4_t>;
            const auto& vld1q_s64 = __vld1<int64x2_t>;

            const auto& vld1q_f32 = __vld1<float32x4_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld1_lane - 64-bit vector //////////////////////////////////////////
            const auto& vld1_lane_u8  = __vld1_lane<uint8x8_t>;
            const auto& vld1_lane_u16 = __vld1_lane<uint16x4_t>;
            const auto& vld1_lane_u32 = __vld1_lane<uint32x2_t>;
            const auto& vld1_lane_u64 = __vld1_lane<uint64x1_t>;

            const auto& vld1_lane_s8  = __vld1_lane<int8x8_t>;
            const auto& vld1_lane_s16 = __vld1_lane<int16x4_t>;
            const auto& vld1_lane_s32 = __vld1_lane<int32x2_t>;
            const auto& vld1_lane_s64 = __vld1_lane<int64x1_t>;

            const auto& vld1_lane_f32 = __vld1_lane<float32x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld1_lane - 128-bit vector //////////////////////////////////////////
            const auto& vld1q_lane_u8  = __vld1_lane<uint8x16_t>;
            const auto& vld1q_lane_u16 = __vld1_lane<uint16x8_t>;
            const auto& vld1q_lane_u32 = __vld1_lane<uint32x4_t>;
            const auto& vld1q_lane_u64 = __vld1_lane<uint64x2_t>;

            const auto& vld1q_lane_s8  = __vld1_lane<int8x16_t>;
            const auto& vld1q_lane_s16 = __vld1_lane<int16x8_t>;
            const auto& vld1q_lane_s32 = __vld1_lane<int32x4_t>;
            const auto& vld1q_lane_s64 = __vld1_lane<int64x2_t>;

            const auto& vld1q_lane_f32 = __vld1_lane<float32x4_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld1_dup - 64-bit vector //////////////////////////////////////////
            const auto& vld1_dup_u8  = __vld1_dup<uint8x8_t>;
            const auto& vld1_dup_u16 = __vld1_dup<uint16x4_t>;
            const auto& vld1_dup_u32 = __vld1_dup<uint32x2_t>;
            const auto& vld1_dup_u64 = __vld1_dup<uint64x1_t>;

            const auto& vld1_dup_s8  = __vld1_dup<int8x8_t>;
            const auto& vld1_dup_s16 = __vld1_dup<int16x4_t>;
            const auto& vld1_dup_s32 = __vld1_dup<int32x2_t>;
            const auto& vld1_dup_s64 = __vld1_dup<int64x1_t>;

            const auto& vld1_dup_f32 = __vld1_dup<float32x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld1_dup - 128-bit vector //////////////////////////////////////////
            const auto& vld1q_dup_u8  = __vld1_dup<uint8x16_t>;
            const auto& vld1q_dup_u16 = __vld1_dup<uint16x8_t>;
            const auto& vld1q_dup_u32 = __vld1_dup<uint32x4_t>;
            const auto& vld1q_dup_u64 = __vld1_dup<uint64x2_t>;

            const auto& vld1q_dup_s8  = __vld1_dup<int8x16_t>;
            const auto& vld1q_dup_s16 = __vld1_dup<int16x8_t>;
            const auto& vld1q_dup_s32 = __vld1_dup<int32x4_t>;
            const auto& vld1q_dup_s64 = __vld1_dup<int64x2_t>;

            const auto& vld1q_dup_f32 = __vld1_dup<float32x4_t>;
            /////////////////////////////////////////////////////////////////////////////


            // ARM NEON - vst1 - 64-bit vector //////////////////////////////////////////
            const auto& vst1_u8  = __vst1<uint8x8_t>;
            const auto& vst1_u16 = __vst1<uint16x4_t>;
            const auto& vst1_u32 = __vst1<uint32x2_t>;
            const auto& vst1_u64 = __vst1<uint64x1_t>;

            const auto& vst1_s8  = __vst1<int8x8_t>;
            const auto& vst1_s16 = __vst1<int16x4_t>;
            const auto& vst1_s32 = __vst1<int32x2_t>;
            const auto& vst1_s64 = __vst1<int64x1_t>;

            const auto& vst1_f32 = __vst1<float32x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vst1 - 128-bit vector //////////////////////////////////////////
            const auto& vst1q_u8  = __vst1<uint8x16_t>;
            const auto& vst1q_u16 = __vst1<uint16x8_t>;
            const auto& vst1q_u32 = __vst1<uint32x4_t>;
            const auto& vst1q_u64 = __vst1<uint64x2_t>;

            const auto& vst1q_s8  = __vst1<int8x16_t>;
            const auto& vst1q_s16 = __vst1<int16x8_t>;
            const auto& vst1q_s32 = __vst1<int32x4_t>;
            const auto& vst1q_s64 = __vst1<int64x2_t>;

            const auto& vst1q_f32 = __vst1<float32x4_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vst1_lane - 64-bit vector //////////////////////////////////////////
            const auto& vst1_lane_u8  = __vst1_lane<uint8x8_t>;
            const auto& vst1_lane_u16 = __vst1_lane<uint16x4_t>;
            const auto& vst1_lane_u32 = __vst1_lane<uint32x2_t>;
            const auto& vst1_lane_u64 = __vst1_lane<uint64x1_t>;

            const auto& vst1_lane_s8  = __vst1_lane<int8x8_t>;
            const auto& vst1_lane_s16 = __vst1_lane<int16x4_t>;
            const auto& vst1_lane_s32 = __vst1_lane<int32x2_t>;
            const auto& vst1_lane_s64 = __vst1_lane<int64x1_t>;

            const auto& vst1_lane_f32 = __vst1_lane<float32x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vst1 - 128-bit vector //////////////////////////////////////////
            const auto& vst1q_lane_u8  = __vst1_lane<uint8x16_t>;
            const auto& vst1q_lane_u16 = __vst1_lane<uint16x8_t>;
            const auto& vst1q_lane_u32 = __vst1_lane<uint32x4_t>;
            const auto& vst1q_lane_u64 = __vst1_lane<uint64x2_t>;

            const auto& vst1q_lane_s8  = __vst1_lane<int8x16_t>;
            const auto& vst1q_lane_s16 = __vst1_lane<int16x8_t>;
            const auto& vst1q_lane_s32 = __vst1_lane<int32x4_t>;
            const auto& vst1q_lane_s64 = __vst1_lane<int64x2_t>;

            const auto& vst1q_lane_f32 = __vst1_lane<float32x4_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON vld2 - 64-bit vectors ///////////////////////////////////////////
            const auto& vld2_s8  = __vld<int8x8x2_t>;
            const auto& vld2_s16 = __vld<int16x4x2_t>;
            const auto& vld2_s32 = __vld<int32x2x2_t>;
            const auto& vld2_s64 = __vld<int64x1x2_t>;

            const auto& vld2_u8  = __vld<uint8x8x2_t>;
            const auto& vld2_u16 = __vld<uint16x4x2_t>;
            const auto& vld2_u32 = __vld<uint32x2x2_t>;
            const auto& vld2_u64 = __vld<uint64x1x2_t>;

            const auto& vld2_f32 = __vld<float32x2x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON vld2 - 128-bit vectors ///////////////////////////////////////////
            const auto& vld2q_s8  = __vld<int8x16x2_t>;
            const auto& vld2q_s16 = __vld<int16x8x2_t>;
            const auto& vld2q_s32 = __vld<int32x4x2_t>;
            const auto& vld2q_s64 = __vld<int64x2x2_t>;

            const auto& vld2q_u8  = __vld<uint8x16x2_t>;
            const auto& vld2q_u16 = __vld<uint16x8x2_t>;
            const auto& vld2q_u32 = __vld<uint32x4x2_t>;
            const auto& vld2q_u64 = __vld<uint64x2x2_t>;

            const auto& vld2q_f32 = __vld<float32x4x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld2_lane - 64-bit vector //////////////////////////////////////////
            const auto& vld2_lane_u8  = __vld_lane<uint8x8x2_t>;
            const auto& vld2_lane_u16 = __vld_lane<uint16x4x2_t>;
            const auto& vld2_lane_u32 = __vld_lane<uint32x2x2_t>;

            const auto& vld2_lane_s8  = __vld_lane<int8x8x2_t>;
            const auto& vld2_lane_s16 = __vld_lane<int16x4x2_t>;
            const auto& vld2_lane_s32 = __vld_lane<int32x2x2_t>;

            const auto& vld2_lane_f32 = __vld_lane<float32x2x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld2_lane - 128-bit vector //////////////////////////////////////////
            const auto& vld2q_lane_u8  = __vld_lane<uint8x16x2_t>;
            const auto& vld2q_lane_u16 = __vld_lane<uint16x8x2_t>;
            const auto& vld2q_lane_u32 = __vld_lane<uint32x4x2_t>;

            const auto& vld2q_lane_s8  = __vld_lane<int8x16x2_t>;
            const auto& vld2q_lane_s16 = __vld_lane<int16x8x2_t>;
            const auto& vld2q_lane_s32 = __vld_lane<int32x4x2_t>;

            const auto& vld2q_lane_f32 = __vld_lane<float32x4x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld2_dup - 64-bit vector //////////////////////////////////////////
            const auto& vld2_dup_u8  = __vld_dup<uint8x8x2_t>;
            const auto& vld2_dup_u16 = __vld_dup<uint16x4x2_t>;
            const auto& vld2_dup_u32 = __vld_dup<uint32x2x2_t>;
            const auto& vld2_dup_u64 = __vld_dup<uint64x1x2_t>;

            const auto& vld2_dup_s8  = __vld_dup<int8x8x2_t>;
            const auto& vld2_dup_s16 = __vld_dup<int16x4x2_t>;
            const auto& vld2_dup_s32 = __vld_dup<int32x2x2_t>;
            const auto& vld2_dup_s64 = __vld_dup<int64x1x2_t>;

            const auto& vld2_dup_f32 = __vld_dup<float32x2x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld2_dup - 128-bit vector //////////////////////////////////////////
            const auto& vld2q_dup_u8  = __vld_dup<uint8x16x2_t>;
            const auto& vld2q_dup_u16 = __vld_dup<uint16x8x2_t>;
            const auto& vld2q_dup_u32 = __vld_dup<uint32x4x2_t>;
            const auto& vld2q_dup_u64 = __vld_dup<uint64x2x2_t>;

            const auto& vld2q_dup_s8  = __vld_dup<int8x16x2_t>;
            const auto& vld2q_dup_s16 = __vld_dup<int16x8x2_t>;
            const auto& vld2q_dup_s32 = __vld_dup<int32x4x2_t>;
            const auto& vld2q_dup_s64 = __vld_dup<int64x2x2_t>;

            const auto& vld2q_dup_f32 = __vld_dup<float32x4x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON vld3 - 64-bit vectors ///////////////////////////////////////////
            const auto& vld3_s8  = __vld<int8x8x3_t>;
            const auto& vld3_s16 = __vld<int16x4x3_t>;
            const auto& vld3_s32 = __vld<int32x2x3_t>;
            const auto& vld3_s64 = __vld<int64x1x3_t>;

            const auto& vld3_u8  = __vld<uint8x8x3_t>;
            const auto& vld3_u16 = __vld<uint16x4x3_t>;
            const auto& vld3_u32 = __vld<uint32x2x3_t>;
            const auto& vld3_u64 = __vld<uint64x1x3_t>;

            const auto& vld3_f32 = __vld<float32x2x3_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON vld3 - 128-bit vectors ///////////////////////////////////////////
            const auto& vld3q_s8  = __vld<int8x16x3_t>;
            const auto& vld3q_s16 = __vld<int16x8x3_t>;
            const auto& vld3q_s32 = __vld<int32x4x3_t>;
            const auto& vld3q_s64 = __vld<int64x2x3_t>;

            const auto& vld3q_u8  = __vld<uint8x16x3_t>;
            const auto& vld3q_u16 = __vld<uint16x8x3_t>;
            const auto& vld3q_u32 = __vld<uint32x4x3_t>;
            const auto& vld3q_u64 = __vld<uint64x2x3_t>;

            const auto& vld3q_f32 = __vld<float32x4x3_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld3_lane - 64-bit vector //////////////////////////////////////////
            const auto& vld3_lane_u8  = __vld_lane<uint8x8x3_t>;
            const auto& vld3_lane_u16 = __vld_lane<uint16x4x3_t>;
            const auto& vld3_lane_u32 = __vld_lane<uint32x2x3_t>;

            const auto& vld3_lane_s8  = __vld_lane<int8x8x3_t>;
            const auto& vld3_lane_s16 = __vld_lane<int16x4x3_t>;
            const auto& vld3_lane_s32 = __vld_lane<int32x2x3_t>;

            const auto& vld3_lane_f32 = __vld_lane<float32x2x3_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld3_lane - 128-bit vector //////////////////////////////////////////
            const auto& vld3q_lane_u8  = __vld_lane<uint8x16x3_t>;
            const auto& vld3q_lane_u16 = __vld_lane<uint16x8x3_t>;
            const auto& vld3q_lane_u32 = __vld_lane<uint32x4x3_t>;

            const auto& vld3q_lane_s8  = __vld_lane<int8x16x3_t>;
            const auto& vld3q_lane_s16 = __vld_lane<int16x8x3_t>;
            const auto& vld3q_lane_s32 = __vld_lane<int32x4x3_t>;

            const auto& vld3q_lane_f32 = __vld_lane<float32x4x3_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld3_dup - 64-bit vector //////////////////////////////////////////
            const auto& vld3_dup_u8  = __vld_dup<uint8x8x2_t>;
            const auto& vld3_dup_u16 = __vld_dup<uint16x4x2_t>;
            const auto& vld3_dup_u32 = __vld_dup<uint32x2x2_t>;
            const auto& vld3_dup_u64 = __vld_dup<uint64x1x2_t>;

            const auto& vld3_dup_s8  = __vld_dup<int8x8x2_t>;
            const auto& vld3_dup_s16 = __vld_dup<int16x4x2_t>;
            const auto& vld3_dup_s32 = __vld_dup<int32x2x2_t>;
            const auto& vld3_dup_s64 = __vld_dup<int64x1x2_t>;

            const auto& vld3_dup_f32 = __vld_dup<float32x2x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld3_dup - 128-bit vector //////////////////////////////////////////
            const auto& vld3q_dup_u8  = __vld_dup<uint8x16x2_t>;
            const auto& vld3q_dup_u16 = __vld_dup<uint16x8x2_t>;
            const auto& vld3q_dup_u32 = __vld_dup<uint32x4x2_t>;
            const auto& vld3q_dup_u64 = __vld_dup<uint64x2x2_t>;

            const auto& vld3q_dup_s8  = __vld_dup<int8x16x2_t>;
            const auto& vld3q_dup_s16 = __vld_dup<int16x8x2_t>;
            const auto& vld3q_dup_s32 = __vld_dup<int32x4x2_t>;
            const auto& vld3q_dup_s64 = __vld_dup<int64x2x2_t>;

            const auto& vld3q_dup_f32 = __vld_dup<float32x4x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON vld4 - 64-bit vectors ///////////////////////////////////////////
            const auto& vld4_s8  = __vld<int8x8x4_t>;
            const auto& vld4_s16 = __vld<int16x4x4_t>;
            const auto& vld4_s32 = __vld<int32x2x4_t>;
            const auto& vld4_s64 = __vld<int64x1x4_t>;

            const auto& vld4_u8  = __vld<uint8x8x4_t>;
            const auto& vld4_u16 = __vld<uint16x4x4_t>;
            const auto& vld4_u32 = __vld<uint32x2x4_t>;
            const auto& vld4_u64 = __vld<uint64x1x4_t>;

            const auto& vld4_f32 = __vld<float32x2x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON vld4 - 128-bit vectors ///////////////////////////////////////////
            const auto& vld4q_s8  = __vld<int8x16x4_t>;
            const auto& vld4q_s16 = __vld<int16x8x4_t>;
            const auto& vld4q_s32 = __vld<int32x4x4_t>;
            const auto& vld4q_s64 = __vld<int64x2x4_t>;

            const auto& vld4q_u8  = __vld<uint8x16x4_t>;
            const auto& vld4q_u16 = __vld<uint16x8x4_t>;
            const auto& vld4q_u32 = __vld<uint32x4x4_t>;
            const auto& vld4q_u64 = __vld<uint64x2x4_t>;

            const auto& vld4q_f32 = __vld<float32x4x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld4_lane - 64-bit vector //////////////////////////////////////////
            const auto& vld4_lane_u8  = __vld_lane<uint8x8x4_t>;
            const auto& vld4_lane_u16 = __vld_lane<uint16x4x4_t>;
            const auto& vld4_lane_u32 = __vld_lane<uint32x2x4_t>;

            const auto& vld4_lane_s8  = __vld_lane<int8x8x4_t>;
            const auto& vld4_lane_s16 = __vld_lane<int16x4x4_t>;
            const auto& vld4_lane_s32 = __vld_lane<int32x2x4_t>;

            const auto& vld4_lane_f32 = __vld_lane<float32x2x4_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld4_lane - 128-bit vector //////////////////////////////////////////
            const auto& vld4q_lane_u8  = __vld_lane<uint8x16x4_t>;
            const auto& vld4q_lane_u16 = __vld_lane<uint16x8x4_t>;
            const auto& vld4q_lane_u32 = __vld_lane<uint32x4x4_t>;

            const auto& vld4q_lane_s8  = __vld_lane<int8x16x4_t>;
            const auto& vld4q_lane_s16 = __vld_lane<int16x8x4_t>;
            const auto& vld4q_lane_s32 = __vld_lane<int32x4x4_t>;

            const auto& vld4q_lane_f32 = __vld_lane<float32x4x4_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld4_dup - 64-bit vector //////////////////////////////////////////
            const auto& vld4_dup_u8  = __vld_dup<uint8x8x2_t>;
            const auto& vld4_dup_u16 = __vld_dup<uint16x4x2_t>;
            const auto& vld4_dup_u32 = __vld_dup<uint32x2x2_t>;
            const auto& vld4_dup_u64 = __vld_dup<uint64x1x2_t>;

            const auto& vld4_dup_s8  = __vld_dup<int8x8x2_t>;
            const auto& vld4_dup_s16 = __vld_dup<int16x4x2_t>;
            const auto& vld4_dup_s32 = __vld_dup<int32x2x2_t>;
            const auto& vld4_dup_s64 = __vld_dup<int64x1x2_t>;

            const auto& vld4_dup_f32 = __vld_dup<float32x2x2_t>;
            /////////////////////////////////////////////////////////////////////////////

            // ARM NEON - vld4_dup - 128-bit vector //////////////////////////////////////////
            const auto& vld4q_dup_u8  = __vld_dup<uint8x16x2_t>;
            const auto& vld4q_dup_u16 = __vld_dup<uint16x8x2_t>;
            const auto& vld4q_dup_u32 = __vld_dup<uint32x4x2_t>;
            const auto& vld4q_dup_u64 = __vld_dup<uint64x2x2_t>;

            const auto& vld4q_dup_s8  = __vld_dup<int8x16x2_t>;
            const auto& vld4q_dup_s16 = __vld_dup<int16x8x2_t>;
            const auto& vld4q_dup_s32 = __vld_dup<int32x4x2_t>;
            const auto& vld4q_dup_s64 = __vld_dup<int64x2x2_t>;

            const auto& vld4q_dup_f32 = __vld_dup<float32x4x2_t>;
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

            // ARM NEON - vset_lane - 64-bit vectors //////////////////////////////////
            const auto& vset_lane_s8  = __vset_lane<int8x8_t>;
            const auto& vset_lane_s16 = __vset_lane<int16x4_t>;
            const auto& vset_lane_s32 = __vset_lane<int32x2_t>;
            const auto& vset_lane_s64 = __vset_lane<int64x1_t>;

            const auto& vset_lane_u8  = __vset_lane<uint8x8_t>;
            const auto& vset_lane_u16 = __vset_lane<uint16x4_t>;
            const auto& vset_lane_u32 = __vset_lane<uint32x2_t>;
            const auto& vset_lane_u64 = __vset_lane<uint64x1_t>;

            const auto& vset_lane_f32 = __vset_lane<float32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vset_lane - 128-bit vectors //////////////////////////////////
            const auto& vsetq_lane_s8  = __vset_lane<int8x16_t>;
            const auto& vsetq_lane_s16 = __vset_lane<int16x8_t>;
            const auto& vsetq_lane_s32 = __vset_lane<int32x4_t>;
            const auto& vsetq_lane_s64 = __vset_lane<int64x2_t>;

            const auto& vsetq_lane_u8  = __vset_lane<uint8x16_t>;
            const auto& vsetq_lane_u16 = __vset_lane<uint16x8_t>;
            const auto& vsetq_lane_u32 = __vset_lane<uint32x4_t>;
            const auto& vsetq_lane_u64 = __vset_lane<uint64x2_t>;

            const auto& vsetq_lane_f32 = __vset_lane<float32x4_t>;
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

            const auto& vget_lane_f32 = __vget_lane<float32x2_t, float>;
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

            const auto& vgetq_lane_f32 = __vget_lane<float32x4_t, float>;
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

            const auto& vdup_lane_f32 = __vdup_lane<float32x2_t, float>;
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

            const auto& vdupq_lane_f32 = __vdup_lane<float32x4_t, float>;
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

            // ARM NEON - vaddhn ///////////////////////////////////////////////////////
            const auto& vaddhn_s16  = __vaddhn<int16x8_t, int8x8_t>;
            const auto& vaddhn_s32 = __vaddhn<int32x4_t, int16x4_t>;
            const auto& vaddhn_s64 = __vaddhn<int64x2_t, int32x2_t>;
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

            // ARM NEON - vrhadd - 64-bit vectors ///////////////////////////////////////////////////////
            const auto& vrhadd_u8  = __vrhadd<uint8x8_t>;
            const auto& vrhadd_u16 = __vrhadd<uint16x4_t>;
            const auto& vrhadd_u32 = __vrhadd<uint32x2_t>;

            const auto& vrhadd_s8  = __vrhadd<int16x8_t>;
            const auto& vrhadd_s16 = __vrhadd<int32x4_t>;
            const auto& vrhadd_s32 = __vrhadd<int64x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vrhadd - 128-bit vectors ///////////////////////////////////////////////////////
            const auto& vrhaddq_u8  = __vrhadd<uint8x16_t>;
            const auto& vrhaddq_u16 = __vrhadd<uint16x8_t>;
            const auto& vrhaddq_u32 = __vrhadd<uint32x4_t>;

            const auto& vrhaddq_s8  = __vrhadd<int8x16_t>;
            const auto& vrhaddq_s16 = __vrhadd<int16x8_t>;
            const auto& vrhaddq_s32 = __vrhadd<int32x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vraddhn - 128-bit vectors ///////////////////////////////////////////////////////
            const auto& vraddhn_u16  = __vraddhn<uint16x8_t,uint8x8_t>;
            const auto& vraddhn_u32 = __vraddhn<uint32x4_t,uint16x4_t>;
            const auto& vraddhn_u64 = __vraddhn<uint64x2_t,uint32x2_t>;

            const auto& vraddhn_s16  = __vraddhn<int16x8_t,int8x8_t>;
            const auto& vraddhn_s32 = __vraddhn<int32x4_t,int16x4_t>;
            const auto& vraddhn_s64 = __vraddhn<int64x2_t,int32x2_t>;
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

            // ARM NEON - vqsub - 64-bit vectors ///////////////////////////////////////////////////////
            const auto& vqsub_u8  = __vqsub<uint8x8_t>;
            const auto& vqsub_u16 = __vqsub<uint16x4_t>;
            const auto& vqsub_u32 = __vqsub<uint32x2_t>;
            const auto& vqsub_u64 = __vqsub<uint64x1_t>;

            const auto& vqsub_s8  = __vqsub<int8x8_t>;
            const auto& vqsub_s16 = __vqsub<int16x4_t>;
            const auto& vqsub_s32 = __vqsub<int32x2_t>;
            const auto& vqsub_s64 = __vqsub<int64x1_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vqsub - 128-bit vectors ///////////////////////////////////////////////////////
            const auto& vqsubq_u8  = __vqsub<uint8x16_t>;
            const auto& vqsubq_u16 = __vqsub<uint16x8_t>;
            const auto& vqsubq_u32 = __vqsub<uint32x4_t>;
            const auto& vqsubq_u64 = __vqsub<uint64x2_t>;

            const auto& vqsubq_s8  = __vqsub<int8x16_t>;
            const auto& vqsubq_s16 = __vqsub<int16x8_t>;
            const auto& vqsubq_s32 = __vqsub<int32x4_t>;
            const auto& vqsubq_s64 = __vqsub<int64x2_t>;
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

            // ARM_NEON - vfma - 64-bit vector
            const auto& vfma_f32 = vmla_f32;
            //

            // ARM_NEON - vfma - 128-bit vector
            const auto& vfmaq_f32 = vmlaq_f32;
            //

            // ARM NEON - vmlal ///////////////////////////////////////////////////////
            const auto& vmlal_s8  = __vmlal< int8x8_t,int16x8_t>;
            const auto& vmlal_s16 = __vmlal<int16x4_t,int32x4_t>;
            const auto& vmlal_s32 = __vmlal<int32x2_t,int64x2_t>;

            const auto& vmlal_u8  = __vmlal< uint8x8_t,uint16x8_t>;
            const auto& vmlal_u16 = __vmlal<uint16x4_t,uint32x4_t>;
            const auto& vmlal_u32 = __vmlal<uint32x2_t,uint64x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmla_lane - 64-bit vector ///////////////////////////////////////////////////////
            const auto& vmla_lane_s16 = __vmla_lane<int16x4_t>;
            const auto& vmla_lane_s32 = __vmla_lane<int32x2_t>;

            const auto& vmla_lane_u16 = __vmla_lane<uint16x4_t>;
            const auto& vmla_lane_u32 = __vmla_lane<uint32x2_t>;

            const auto& vmla_lane_f32 = __vmla_lane<float32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmla_lane - 128-bit vector ///////////////////////////////////////////////////////
            const auto& vmlaq_lane_s16 = __vmla_lane<int16x8_t>;
            const auto& vmlaq_lane_s32 = __vmla_lane<int32x4_t>;

            const auto& vmlaq_lane_u16 = __vmla_lane<uint16x8_t>;
            const auto& vmlaq_lane_u32 = __vmla_lane<uint32x4_t>;

            const auto& vmlaq_lane_f32 = __vmla_lane<float32x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmla_n - 64-bit vector ///////////////////////////////////////////////////////
            const auto& vmla_n_s16 = __vmla_n<int16x4_t>;
            const auto& vmla_n_s32 = __vmla_n<int32x2_t>;

            const auto& vmla_n_u16 = __vmla_n<uint16x4_t>;
            const auto& vmla_n_u32 = __vmla_n<uint32x2_t>;

            const auto& vmla_n_f32 = __vmla_n<float32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmla_n - 128-bit vector ///////////////////////////////////////////////////////
            const auto& vmlaq_n_s16 = __vmla_n<int16x8_t>;
            const auto& vmlaq_n_s32 = __vmla_n<int32x4_t>;

            const auto& vmlaq_n_u16 = __vmla_n<uint16x8_t>;
            const auto& vmlaq_n_u32 = __vmla_n<uint32x4_t>;

            const auto& vmlaq_n_f32 = __vmla_n<float32x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmls - 64-bit vector ///////////////////////////////////////////////////////
            const auto& vmls_s8  = __vmls< int8x8_t>;
            const auto& vmls_s16 = __vmls<int16x4_t>;
            const auto& vmls_s32 = __vmls<int32x2_t>;

            const auto& vmls_u8  = __vmls<uint8x8_t>;
            const auto& vmls_u16 = __vmls<uint16x4_t>;
            const auto& vmls_u32 = __vmls<uint32x2_t>;

            const auto& vmls_f32 = __vmls<float32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmls - 128-bit vector ///////////////////////////////////////////////////////
            const auto& vmlsq_s8  = __vmls<int8x16_t>;
            const auto& vmlsq_s16 = __vmls<int16x8_t>;
            const auto& vmlsq_s32 = __vmls<int32x4_t>;

            const auto& vmlsq_u8  = __vmls<uint8x16_t>;
            const auto& vmlsq_u16 = __vmls<uint16x8_t>;
            const auto& vmlsq_u32 = __vmls<uint32x4_t>;

            const auto& vmlsq_f32 = __vmls<float32x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM_NEON - vfma - 64-bit vector
            const auto& vfms_f32 = vmls_f32;
            //

            // ARM_NEON - vfma - 128-bit vector
            const auto& vfmsq_f32 = vmlsq_f32;
            //

            // ARM NEON - vmlsl ///////////////////////////////////////////////////////
            const auto& vmlsl_s8  = __vmlsl< int8x8_t,int16x8_t>;
            const auto& vmlsl_s16 = __vmlsl<int16x4_t,int32x4_t>;
            const auto& vmlsl_s32 = __vmlsl<int32x2_t,int64x2_t>;

            const auto& vmlsl_u8  = __vmlsl< uint8x8_t,uint16x8_t>;
            const auto& vmlsl_u16 = __vmlsl<uint16x4_t,uint32x4_t>;
            const auto& vmlsl_u32 = __vmlsl<uint32x2_t,uint64x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmls_lane - 64-bit vector ///////////////////////////////////////////////////////
            const auto& vmls_lane_s16 = __vmls_lane<int16x4_t>;
            const auto& vmls_lane_s32 = __vmls_lane<int32x2_t>;

            const auto& vmls_lane_u16 = __vmls_lane<uint16x4_t>;
            const auto& vmls_lane_u32 = __vmls_lane<uint32x2_t>;

            const auto& vmls_lane_f32 = __vmls_lane<float32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmls_lane - 128-bit vector ///////////////////////////////////////////////////////
            const auto& vmlsq_lane_s16 = __vmls_lane<int16x8_t>;
            const auto& vmlsq_lane_s32 = __vmls_lane<int32x4_t>;

            const auto& vmlsq_lane_u16 = __vmls_lane<uint16x8_t>;
            const auto& vmlsq_lane_u32 = __vmls_lane<uint32x4_t>;

            const auto& vmlsq_lane_f32 = __vmls_lane<float32x4_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmls_n - 64-bit vector ///////////////////////////////////////////////////////
            const auto& vmls_n_s16 = __vmls_n<int16x4_t>;
            const auto& vmls_n_s32 = __vmls_n<int32x2_t>;

            const auto& vmls_n_u16 = __vmls_n<uint16x4_t>;
            const auto& vmls_n_u32 = __vmls_n<uint32x2_t>;

            const auto& vmls_n_f32 = __vmls_n<float32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmls_n - 128-bit vector ///////////////////////////////////////////////////////
            const auto& vmlsq_n_s16 = __vmls_n<int16x8_t>;
            const auto& vmlsq_n_s32 = __vmls_n<int32x4_t>;

            const auto& vmlsq_n_u16 = __vmls_n<uint16x8_t>;
            const auto& vmlsq_n_u32 = __vmls_n<uint32x4_t>;

            const auto& vmlsq_n_f32 = __vmls_n<float32x4_t>;
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

            // ARM NEON - vtst - 64-bit vectors ///////////////////////////////////////
            const auto& vtst_u8  = __vtst<   uint8x8_t,  uint8x8_t>;
            const auto& vtst_u16 = __vtst<  uint16x4_t, uint16x4_t>;
            const auto& vtst_u32 = __vtst<  uint32x2_t, uint32x2_t>;

            const auto& vtst_s8  = __vtst<    int8x8_t,  uint8x8_t>;
            const auto& vtst_s16 = __vtst<   int16x4_t, uint16x4_t>;
            const auto& vtst_s32 = __vtst<   int32x2_t, uint32x2_t>;
            ///////////////////////////////////////////////////////////////////////////

            // ARM NEON - vtst - 128-bit vectors ///////////////////////////////////////
            const auto& vtstq_u8  = __vtst<  uint8x16_t, uint8x16_t>;
            const auto& vtstq_u16 = __vtst<  uint16x8_t, uint16x8_t>;
            const auto& vtstq_u32 = __vtst<  uint32x4_t, uint32x4_t>;

            const auto& vtstq_s8  = __vtst<   int8x16_t, uint8x16_t>;
            const auto& vtstq_s16 = __vtst<   int16x8_t, uint16x8_t>;
            const auto& vtstq_s32 = __vtst<   int32x4_t, uint32x4_t>;
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

            // ARM NEON - vcagt - 64-bit vectors ////////////////////////////////////
            const auto& vcagt_f32 = __vcagt< float32x2_t, uint32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcagt - 128-bit vectors ///////////////////////////////////
            const auto& vcagtq_f32 = __vcagt< float32x4_t, uint32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcage - 64-bit vectors ////////////////////////////////////
            const auto& vcage_f32 = __vcage< float32x2_t, uint32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcage - 128-bit vectors ///////////////////////////////////
            const auto& vcageq_f32 = __vcage< float32x4_t, uint32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcalt - 64-bit vectors ////////////////////////////////////
            const auto& vcalt_f32 = __vcalt< float32x2_t, uint32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcalt - 128-bit vectors ///////////////////////////////////
            const auto& vcaltq_f32 = __vcalt< float32x4_t, uint32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcale - 64-bit vectors ////////////////////////////////////
            const auto& vcale_f32 = __vcale< float32x2_t, uint32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vcale - 128-bit vectors ///////////////////////////////////
            const auto& vcaleq_f32 = __vcale< float32x4_t, uint32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmax - 64-bit vectors ////////////////////////////////////
            const auto& vmax_u8  = __vmax< uint8x8_t>;
            const auto& vmax_u16 = __vmax<uint16x4_t>;
            const auto& vmax_u32 = __vmax<uint32x2_t>;

            const auto& vmax_s8  = __vmax< int8x8_t>;
            const auto& vmax_s16 = __vmax<int16x4_t>;
            const auto& vmax_s32 = __vmax<int32x2_t>;

            const auto& vmax_f32 = __vmax<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmax - 128-bit vectors ///////////////////////////////////
            const auto& vmaxq_u8  = __vmax<uint8x16_t>;
            const auto& vmaxq_u16 = __vmax<uint16x8_t>;
            const auto& vmaxq_u32 = __vmax<uint32x4_t>;

            const auto& vmaxq_s8  = __vmax<int8x16_t>;
            const auto& vmaxq_s16 = __vmax<int16x8_t>;
            const auto& vmaxq_s32 = __vmax<int32x4_t>;

            const auto& vmaxq_f32 = __vmax<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmin - 64-bit vectors ////////////////////////////////////
            const auto& vmin_u8  = __vmin< uint8x8_t>;
            const auto& vmin_u16 = __vmin<uint16x4_t>;
            const auto& vmin_u32 = __vmin<uint32x2_t>;

            const auto& vmin_s8  = __vmin< int8x8_t>;
            const auto& vmin_s16 = __vmin<int16x4_t>;
            const auto& vmin_s32 = __vmin<int32x2_t>;

            const auto& vmin_f32 = __vmin<float32x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vmin - 128-bit vectors ///////////////////////////////////
            const auto& vminq_u8  = __vmin<uint8x16_t>;
            const auto& vminq_u16 = __vmin<uint16x8_t>;
            const auto& vminq_u32 = __vmin<uint32x4_t>;

            const auto& vminq_s8  = __vmin<int8x16_t>;
            const auto& vminq_s16 = __vmin<int16x8_t>;
            const auto& vminq_s32 = __vmin<int32x4_t>;

            const auto& vminq_f32 = __vmin<float32x4_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshl - 64-bit vectors ////////////////////////////////////
            const auto& vshl_u8  = __vshl<uint8x8_t>;
            const auto& vshl_u16 = __vshl<uint16x4_t>;
            const auto& vshl_u32 = __vshl<uint32x2_t>;
            const auto& vshl_u64 = __vshl<uint64x1_t>;
            
            const auto& vshl_s8  = __vshl<int8x8_t>;
            const auto& vshl_s16 = __vshl<int16x4_t>;
            const auto& vshl_s32 = __vshl<int32x2_t>;
            const auto& vshl_s64 = __vshl<int64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshl - 128-bit vectors ////////////////////////////////////
            const auto& vshlq_u8  = __vshl<uint8x16_t>;
            const auto& vshlq_u16 = __vshl<uint16x8_t>;
            const auto& vshlq_u32 = __vshl<uint32x4_t>;
            const auto& vshlq_u64 = __vshl<uint64x2_t>;
            
            const auto& vshlq_s8  = __vshl<int8x16_t>;
            const auto& vshlq_s16 = __vshl<int16x8_t>;
            const auto& vshlq_s32 = __vshl<int32x4_t>;
            const auto& vshlq_s64 = __vshl<int64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshl_n - 64-bit vectors ////////////////////////////////////
            const auto& vshl_n_u8  = __vshl_n<uint8x8_t>;
            const auto& vshl_n_u16 = __vshl_n<uint16x4_t>;
            const auto& vshl_n_u32 = __vshl_n<uint32x2_t>;
            const auto& vshl_n_u64 = __vshl_n<uint64x1_t>;
            
            const auto& vshl_n_s8  = __vshl_n<int8x8_t>;
            const auto& vshl_n_s16 = __vshl_n<int16x4_t>;
            const auto& vshl_n_s32 = __vshl_n<int32x2_t>;
            const auto& vshl_n_s64 = __vshl_n<int64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshl - 128-bit vectors ////////////////////////////////////
            const auto& vshlq_n_u8  = __vshl_n<uint8x16_t>;
            const auto& vshlq_n_u16 = __vshl_n<uint16x8_t>;
            const auto& vshlq_n_u32 = __vshl_n<uint32x4_t>;
            const auto& vshlq_n_u64 = __vshl_n<uint64x2_t>;
            
            const auto& vshlq_n_s8  = __vshl_n<int8x16_t>;
            const auto& vshlq_n_s16 = __vshl_n<int16x8_t>;
            const auto& vshlq_n_s32 = __vshl_n<int32x4_t>;
            const auto& vshlq_n_s64 = __vshl_n<int64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshr_n - 64-bit vectors ////////////////////////////////////
            const auto& vshr_n_u8  = __vshr_n<uint8x8_t>;
            const auto& vshr_n_u16 = __vshr_n<uint16x4_t>;
            const auto& vshr_n_u32 = __vshr_n<uint32x2_t>;
            const auto& vshr_n_u64 = __vshr_n<uint64x1_t>;
            
            const auto& vshr_n_s8  = __vshr_n<int8x8_t>;
            const auto& vshr_n_s16 = __vshr_n<int16x4_t>;
            const auto& vshr_n_s32 = __vshr_n<int32x2_t>;
            const auto& vshr_n_s64 = __vshr_n<int64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshr - 128-bit vectors ////////////////////////////////////
            const auto& vshrq_n_u8  = __vshr_n<uint8x16_t>;
            const auto& vshrq_n_u16 = __vshr_n<uint16x8_t>;
            const auto& vshrq_n_u32 = __vshr_n<uint32x4_t>;
            const auto& vshrq_n_u64 = __vshr_n<uint64x2_t>;
            
            const auto& vshrq_n_s8  = __vshr_n<int8x16_t>;
            const auto& vshrq_n_s16 = __vshr_n<int16x8_t>;
            const auto& vshrq_n_s32 = __vshr_n<int32x4_t>;
            const auto& vshrq_n_s64 = __vshr_n<int64x2_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshr_n - 64-bit vectors ////////////////////////////////////
            const auto& vrshr_n_u8  = __vrshr_n<uint8x8_t>;
            const auto& vrshr_n_u16 = __vrshr_n<uint16x4_t>;
            const auto& vrshr_n_u32 = __vrshr_n<uint32x2_t>;
            const auto& vrshr_n_u64 = __vrshr_n<uint64x1_t>;
            
            const auto& vrshr_n_s8  = __vrshr_n<int8x8_t>;
            const auto& vrshr_n_s16 = __vrshr_n<int16x4_t>;
            const auto& vrshr_n_s32 = __vrshr_n<int32x2_t>;
            const auto& vrshr_n_s64 = __vrshr_n<int64x1_t>;
            ////////////////////////////////////////////////////////////////////////

            // ARM NEON - vshr - 128-bit vectors ////////////////////////////////////
            const auto& vrshrq_n_u8  = __vrshr_n<uint8x16_t>;
            const auto& vrshrq_n_u16 = __vrshr_n<uint16x8_t>;
            const auto& vrshrq_n_u32 = __vrshr_n<uint32x4_t>;
            const auto& vrshrq_n_u64 = __vrshr_n<uint64x2_t>;
            
            const auto& vrshrq_n_s8  = __vrshr_n<int8x16_t>;
            const auto& vrshrq_n_s16 = __vrshr_n<int16x8_t>;
            const auto& vrshrq_n_s32 = __vrshr_n<int32x4_t>;
            const auto& vrshrq_n_s64 = __vrshr_n<int64x2_t>;
            ////////////////////////////////////////////////////////////////////////

        }

        using namespace arm_neon;

}

using namespace iris::arm_neon;