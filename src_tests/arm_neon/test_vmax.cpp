#include <iris.h>
#include <cassert>

using namespace iris;

int main() {
    auto v1 = vdup_n_s32(1);
    auto v2 = vdup_n_s32(2);
    auto temp = vmax_s32(v1,v2);
    for(int i = 0; i < decltype(temp)::length; i++) {
        assert(temp.at<decltype(temp)::elementType>(i) == v2.at<decltype(temp)::elementType>(i));
    }
    temp = vmax_s32(v2,v1);
    for(int i = 0; i < decltype(temp)::length; i++) {
        assert(temp.at<decltype(temp)::elementType>(i) == v2.at<decltype(temp)::elementType>(i));
    }
}
