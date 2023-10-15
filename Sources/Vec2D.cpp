#include "Vec2D.h"
#include <cmath>

Vec2D::Vec2D() : Vec2D(0.0f, 0.0f)
{
}

Vec2D::Vec2D(float x, float y) : x(x), y(y)
{
}

void Vec2D::Normalize()
{
    float invLen = 1.0f / Magnitude();
    x *= invLen;
    y *= invLen;
}

float Vec2D::Distance(const Vec2D& other)
{
    float diffX = x - other.x;
    float diffY = y - other.y;
    float tLen = diffX * diffX + diffY * diffY;
    return std::sqrtf(tLen);
}

float Vec2D::Dot(const Vec2D& other)
{
    return x * other.x + y * other.y;
}

float Vec2D::Magnitude()
{
    return std::sqrt(x * x + y * y);
}

float Vec2D::GetAngle()
{
    return (std::atan2(y, x) / PI) * 180.0f;
}

void Vec2D::SetAngle(float angle)
{
    float angleInRadians = angle * PI / 180.0f;
    float magnitude = Magnitude();
    x = magnitude * std::cos(angleInRadians);
    y = magnitude * std::sin(angleInRadians);
}
