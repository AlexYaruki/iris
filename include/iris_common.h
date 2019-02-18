#include <cstdlib>

namespace iris::common {

    template<typename T, size_t len>
    struct vector {
        using elementType = T;
        const static auto elementSize = sizeof(T) * 8;
        const static auto length = len;

        int8_t value_s8[sizeof(T) * length];

        template<typename E>
        E& at(size_t i) {
            return reinterpret_cast<E*>(&value_s8)[i];
        }

        void setAll(T element) {
            for (size_t i = 0; i < length; i++) {
                at<T>(i) = element;
            }
        }

    };

    template<typename T, size_t len>
    struct multi_vector {
        using vectorType = T;
        const static auto lanes = len;
        T val[lanes];
    }; 

}