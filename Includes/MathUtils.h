#pragma once
#include <cmath>
#include "Vec2D.h"

namespace Engine
{
    const float PI = 4.0f * std::atanf(1.0f);
    const float TwoPI = 2.0f * PI;
    const float PIOverTwo = 0.5f * PI;
    const float PIOverFour = 0.25f * PI;
    const float TO_RADIANS = PI / 180.0f;
    const float TO_DEGREES = 180.0f / PI;

    int Clamp(int value, int min, int max);
    float Clamp(float value, float min, float max);
    float DistanceBetweenPoints(float p1x, float p1y, float p2x, float p2y);
    float DistanceBetweenRectangles(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
    float Linear(float time, float start, float end, float d);
    float CircularIn(float time, float start, float end, float d);
    float CircularInOut(float time, float start, float end, float d);
    float CircularOut(float time, float start, float end, float d);
    float CubicIn(float time, float start, float end, float d);
    float CubicInOut(float time, float start, float end, float d);
    float CubicOut(float time, float start, float end, float d);
    float ExponentialIn(float time, float start, float end, float d);
    float ExponentialInOut(float time, float start, float end, float d);
    float ExponentialOut(float time, float start, float end, float d);
    float QuadraticIn(float time, float start, float end, float d);
    float QuadraticInOut(float time, float start, float end, float d);
    float QuadraticOut(float time, float start, float end, float d);
    float QuarticIn(float time, float start, float end, float d);
    float QuarticInOut(float time, float start, float end, float d);
    float QuarticOut(float time, float start, float end, float d);
    float QuinticIn(float time, float start, float end, float d);
    float QuinticInOut(float time, float start, float end, float d);
    float QuinticOut(float time, float start, float end, float d);
    float SinusoidalIn(float time, float start, float end, float d);
    float SinusoidalInOut(float time, float start, float end, float d);
    float SinusoidalOut(float time, float start, float end, float d);
    Vec2D BezierInterp(float time, const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d);
    Vec2D BSplineInterp(float time, const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d);
    Vec2D CatmullRomInterp(float time, const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d);
}