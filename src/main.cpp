#include "vector.hpp"
using namespace hls;

int main()
{
    StaticVector<float, 4> vec1(1);
    StaticVector<float, 4> vec2(2);
    StaticVector<float, 4> vec3;
    vec3 = vec1 + vec2;
    return 0;
}