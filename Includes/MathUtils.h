#pragma once

namespace Engine
{
    int Clamp(int value, int min, int max);

    float DistanceBetweenPoints(float p1x, float p1y, float p2x, float p2y);
    float DistanceBetweenRectangles(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
}