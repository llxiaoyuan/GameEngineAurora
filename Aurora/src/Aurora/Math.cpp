#include<Aurora/Math.hpp>

template<typename T>
T Math::lerp(const T& start, const T& end, const T& t)
{
    return (end - start) * t + start;
}
