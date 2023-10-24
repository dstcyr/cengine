#include "Vec2D.h"
#include "MathUtils.h"
#include <cmath>

Vec2D::Vec2D() : Vec2D(0.0f, 0.0f)
{
}

Vec2D::Vec2D(float x, float y) : x(x), y(y)
{
}

Vec2D::Vec2D(const Vec2D& other)
{
    x = other.x;
    y = other.y;
}

Vec2D& Vec2D::operator=(const Vec2D& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

bool Vec2D::operator==(const Vec2D& other) const
{
    return x == other.x && y == other.y;
}

bool Vec2D::operator!=(const Vec2D& other) const
{
    return !(*this == other);
}

Vec2D Vec2D::operator+(const Vec2D& other) const
{
    return { x + other.x, y + other.y };
}

Vec2D& Vec2D::operator+=(const Vec2D& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2D Vec2D::operator-(const Vec2D& other) const
{
    return { x - other.x, y - other.y };
}

Vec2D& Vec2D::operator-=(const Vec2D& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2D Vec2D::operator*(float scalar) const
{
    return { x * scalar, y * scalar };
}

Vec2D Vec2D::operator/(float scalar) const
{
    return { x / scalar, y / scalar };
}

Vec2D Vec2D::operator*(const Vec2D& other) const
{
    return { x * other.x, y * other.y };
}

Vec2D& Vec2D::operator*=(const Vec2D& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vec2D Vec2D::operator/(const Vec2D& other) const
{
    return { x / other.x, y / other.y };
}

Vec2D& Vec2D::operator/=(const Vec2D& other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

Vec2D Vec2D::operator-() const
{
    return { -x, -y };
}

float Vec2D::Length() const
{
    return std::sqrt(x * x + y * y);
}

float Vec2D::Distance(const Vec2D& other)
{
    float diffX = x - other.x;
    float diffY = y - other.y;
    float tLen = diffX * diffX + diffY * diffY;
    return std::sqrtf(tLen);
}

void Vec2D::Normalize()
{
    float invLen = 1.0f / Length();
    x *= invLen;
    y *= invLen;
}

Vec2D Vec2D::GetNormalized() const
{
    Vec2D other = *this;
    other.Normalize();
    return other;
}

void Vec2D::CW()
{
    x = x;
    y = -y;
}

void Vec2D::CCW()
{
    x = -x;
    y = y;
}

void Vec2D::Reverse()
{
    x = -x;
    y = -y;
}

void Vec2D::South()
{
    x = 0.0f;
    y = std::abs(y);
}

void Vec2D::East()
{
    x = std::abs(x);
    y = 0.0f;
}

void Vec2D::West()
{
    x = -std::abs(x);
    y = 0.0f;
}

void Vec2D::North()
{
    x = 0.0f;
    y = -std::abs(y);
}

void Vec2D::SouthEast()
{
    x = std::abs(x);
    y = std::abs(y);
}

void Vec2D::SouthWest()
{
    x = -std::abs(x);
    y = std::abs(y);
}

void Vec2D::NorthEast()
{
    x = std::abs(x);
    y = -std::abs(y);
}

void Vec2D::NorthWest()
{
    x = -std::abs(x);
    y = -std::abs(y);
}

void Vec2D::Rotate(float angle)
{
    float len = Length();
    Vec2D normal = GetNormalized();
    float s = std::sinf(angle);
    float c = std::cosf(angle);
    float x = normal.x;
    float y = normal.y;
    normal.x = x * c - y * s;
    normal.y = y * c + x * s;
    *this = normal * len;
}

Vec2D Vec2D::GetRotated(float angle) const
{
    float s = std::sinf(angle);
    float c = std::cosf(angle);
    return { x * c - y * s, y * c + x * s };
}

void Vec2D::SetRotation(float angle)
{
    float angleInRadians = angle * Engine::PI / 180.0f;
    float magnitude = Length();
    x = magnitude * std::cosf(angleInRadians);
    y = magnitude * std::sinf(angleInRadians);
}

float Vec2D::GetAngle() const
{
    return (std::atan2f(y, x) / Engine::PI) * 180.0f;
}

float Vec2D::Dot(const Vec2D& a, const Vec2D& b)
{
    return a.x * b.x + a.y * b.y;
}

float Vec2D::Dot(const Vec2D& other)
{
    return x * other.x + y * other.y;
}

bool Vec2D::operator<=(const Vec2D& other) const
{
    if (x <= other.x && y <= other.y)
    {
        return true;
    }

    return false;
}

bool Vec2D::operator>=(const Vec2D& other) const
{
    if (x >= other.x && y >= other.y)
    {
        return true;
    }

    return false;
}

Vec2D& Vec2D::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vec2D& Vec2D::operator/=(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

//Vec2D operator+(const Vec2D& a, const Vec2D& b)
//{
//    Vec2D v = a;
//    v += b;
//    return v;
//}
//
//Vec2D operator-(const Vec2D& a, const Vec2D& b)
//{
//    Vec2D v = a;
//    v -= b;
//    return v;
//}

Vec2D operator*(const Vec2D& other, float scalar)
{
    Vec2D v = other;
    v *= scalar;
    return v;
}

Vec2D operator*(Vec2D& other, float scalar)
{
    Vec2D v = other;
    v *= scalar;
    return v;
}

//Vec2D operator/(const Vec2D& other, float scalar)
//{
//    Vec2D v = other;
//    v /= scalar;
//    return v;
//}

Vec2D operator*(float scalar, const Vec2D& other)
{
    Vec2D v = other;
    v *= scalar;
    return v;
}

std::string Vec2D::ToString() const
{
    return "{x = " + std::to_string(x) + ", y = " + std::to_string(y) + "}";
}

void Vec2D::Set(float x, float y)
{
    this->x = x;
    this->y = y;
}
