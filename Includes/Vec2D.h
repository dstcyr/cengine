#pragma once

#define PI 3.1416f

struct Vec2D
{
    Vec2D();
    Vec2D(float x, float y);
    void Normalize();
    float Distance(const Vec2D& other);
    float Dot(const Vec2D& other);
    float Magnitude();
    float GetAngle();
    void SetAngle(float angle);

    float x;
    float y;
};