#include <cstdlib>

#ifndef IRIS_COMMON
#define IRIS_COMMON

namespace iris::common {

    template<typename T, size_t len>
    struct vector {
        using elementType = T;
        const static auto elementSize = sizeof(T) * 8;
        const static auto length = len;

        int8_t value_s8[sizeof(T) * length];

        template<typename E = T>
        E& at(size_t i) {
            return reinterpret_cast<E*>(&value_s8)[i];
        }

        void setAll(T element) {
            for (size_t i = 0; i < length; i++) {
                at<T>(i) = element;
            }
        }

        vector<T, len> add(vector<T, len>& other) {
            vector<T, len> result;
            for(size_t i = 0; i < length; i++) {
                result.at(i) = at(i) + other.at(i);
            }
            return result;
        }

        template<typename R>
        vector<R, len> add_wider(vector<T, len>& other) {
            vector<R, len> result;
            for(size_t i = 0; i < length; i++) {
                R x = static_cast<R>(at(i));
                R y = static_cast<R>(other.at(i));
                result.at(i) = x + y; 
            }
            return result;
        }


    };

    template<typename T, size_t len>
    struct multi_vector {
        using vectorType = T;
        const static auto lanes = len;
        T val[lanes];
    }; 

}
#endif