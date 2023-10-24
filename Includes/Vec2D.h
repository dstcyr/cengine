#pragma once
#include <string>

struct Vec2D
{
    Vec2D();
    Vec2D(float x, float y);
    Vec2D(const Vec2D& other);
    Vec2D& operator=(const Vec2D& other);
    bool operator==(const Vec2D& other) const;
    bool operator!=(const Vec2D& other) const;
    Vec2D operator+(const Vec2D& other) const;
    Vec2D& operator+=(const Vec2D& other);
    Vec2D operator-(const Vec2D& other) const;
    Vec2D& operator-=(const Vec2D& other);
    Vec2D operator*(float scalar) const;
    Vec2D operator/(float scalar) const;
    Vec2D operator*(const Vec2D& other) const;
    Vec2D& operator*=(const Vec2D& other);
    Vec2D operator/(const Vec2D& other) const;
    Vec2D& operator/=(const Vec2D& other);
    Vec2D operator-() const;
    Vec2D operator+() const;
    bool operator<=(const Vec2D& other) const;
    bool operator>=(const Vec2D& other) const;
    Vec2D& operator*=(float scalar);
    Vec2D& operator/=(float scalar);
    std::string ToString() const;
    void Set(float x, float y);
    float Length() const;
    float Distance(const Vec2D& other);
    void Normalize();
    Vec2D GetNormalized() const;
    void CW();
    void CCW();
    void Reverse();
    void South();
    void East();
    void West();
    void North();
    void SouthEast();
    void SouthWest();
    void NorthEast();
    void NorthWest();
    void Rotate(float angle);
    Vec2D GetRotated(float angle) const;
    void SetRotation(float angle);
    float GetAngle() const;
    static float Dot(const Vec2D& a, const Vec2D& b);
    float Dot(const Vec2D& other);

    float x;
    float y;
};

Vec2D operator*(const Vec2D& other, float scalar);
Vec2D operator*(Vec2D& other, float scalar);
Vec2D operator*(float scalar, const Vec2D& other);