#include<Aurora/Math.hpp>

float Math::lerp(const float& start, const float& end, const float& t)
{
    return (end - start) * t + start;
}
