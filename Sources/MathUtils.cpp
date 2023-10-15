#include "MathUtils.h"
#include <cmath>

int Engine::Clamp(int value, int min, int max)
{
    if (value > max)
    {
        return max;
    }

    if (value < min)
    {
        return min;
    }

    return value;
}

float Engine::DistanceBetweenPoints(float p1x, float p1y, float p2x, float p2y)
{
    float diffX = p1x - p2x;
    float diffY = p1y - p2y;
    float tLen = diffX * diffX + diffY * diffY;
    return std::sqrtf(tLen);
}

float Engine::DistanceBetweenRectangles(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
{
    float center1x = r1x + (r1w / 2.0f);
    float center1y = r1y + (r1h / 2.0f);
    float center2x = r2x + (r2w / 2.0f);
    float center2y = r2y + (r2h / 2.0f);
    return DistanceBetweenPoints(center1x, center1y, center2x, center2y);
}
