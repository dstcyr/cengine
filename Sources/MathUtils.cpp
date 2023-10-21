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

float Engine::Clamp(float value, float min, float max)
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

///-----------------------------------------------------------------------------
/// <summary>
/// Simple linear tweening - no easing, no acceleration
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::Linear(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    return c * t / d + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Circular easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::CircularIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    return -c * (std::sqrtf(1 - t * t) - 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Circular easing in/out - acceleration until halfway, then deceleration
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::CircularInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1) return -c / 2 * (std::sqrtf(1 - t * t) - 1) + b;
    t -= 2;
    return c / 2 * (std::sqrtf(1 - t * t) + 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Circular easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::CircularOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return c * std::sqrtf(1 - t * t) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Cubic easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::CubicIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t * t + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// cubic easing in/out - acceleration until halfway, then deceleration
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::CubicInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t * t + b;
    }

    t -= 2;
    return c / 2 * (t * t * t + 2) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Cubic easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::CubicOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return c * (t * t * t + 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Exponential easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::ExponentialIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    return c * std::powf(2, 10 * (t / d - 1)) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Exponential easing in/out - accelerating until halfway, then decelerating
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::ExponentialInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1) return c / 2 * std::powf(2, 10 * (t - 1)) + b;
    t--;
    return c / 2 * (-std::powf(2, -10 * t) + 2) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Exponential easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::ExponentialOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    return c * (-std::powf(2, -10 * t / d) + 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quadratic easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuadraticIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quadratic easing in/out - acceleration until halfway, then deceleration
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuadraticInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t + b;
    }

    t--;
    return -c / 2 * (t * (t - 2) - 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quadratic easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuadraticOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    return -c * t * (t - 2) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quartic easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuarticIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t * t * t + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quartic easing in/out - acceleration until halfway, then deceleration
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuarticInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1)
    {
        return c / 2 * t * t * t * t + b;
    }

    t -= 2;
    return -c / 2 * (t * t * t * t - 2) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quartic easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuarticOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return -c * (t * t * t * t - 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quintic easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuinticIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    return c * t * t * t * t * t + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quintic easing in/out - acceleration until halfway, then deceleration
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuinticInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d / 2;
    if (t < 1) return c / 2 * t * t * t * t * t + b;
    t -= 2;
    return c / 2 * (t * t * t * t * t + 2) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Quintic easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::QuinticOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    t /= d;
    t--;
    return c * (t * t * t * t * t + 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Sinusoidal easing in - accelerating from zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::SinusoidalIn(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    return -c * std::cosf(t / d * (PI / 2)) + c + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Sinusoidal easing in/out - accelerating until halfway, then decelerating
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::SinusoidalInOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    return -c / 2 * (std::cosf(PI * t / d) - 1) + b;
}

///-----------------------------------------------------------------------------
/// <summary>
/// Sinusoidal easing out - decelerating to zero velocity
/// </summary>
/// <param name="time">the current time on the curve</param>
/// <param name="start">the starting value</param>
/// <param name="end">the target value</param>
/// <param name="d">the interpolation total duration</param>
/// Ex: the interpolation from "start" to "end" in "d" time at position "time".
float Engine::SinusoidalOut(float time, float start, float end, float d)
{
    float t = Clamp(time, 0.0f, d);
    float c = end - start;
    float b = start;

    return c * std::sinf(t / d * (PI / 2)) + b;
}

Vec2D Engine::BezierInterp(float time, const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d)
{
    float t = Clamp(time, 0.0f, d);
    float u = t / d;

    Vec2D point;
    point = u * u * u * ((-1) * P0 + 3 * P1 - 3 * P2 + P3);
    point += u * u * (3 * P0 - 6 * P1 + 3 * P2);
    point += u * ((-3) * P0 + 3 * P1);
    point += P0;

    return point;
}

Vec2D Engine::BSplineInterp(float time, const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d)
{
    float t = Clamp(time, 0.0f, d);
    float u = t / d;

    Vec2D point;
    point = u * u * u * ((-1) * P0 + 3 * P1 - 3 * P2 + P3) / 6;
    point += u * u * (3 * P0 - 6 * P1 + 3 * P2) / 6;
    point += u * ((-3) * P0 + 3 * P2) / 6;
    point += (P0 + 4 * P1 + P2) / 6;

    return point;
}

Vec2D Engine::CatmullRomInterp(float time, const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d)
{
    float t = Clamp(time, 0.0f, d);
    float u = t / d;

    Vec2D point;
    point = u * u * u * ((-1) * P0 + 3 * P1 - 3 * P2 + P3) / 2;
    point += u * u * (2 * P0 - 5 * P1 + 4 * P2 - P3) / 2;
    point += u * ((-1) * P0 + P2) / 2;
    point += P1;

    return point;
}
