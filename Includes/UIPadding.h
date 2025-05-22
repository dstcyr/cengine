#pragma once

struct UIPadding
{
    float left = 0.0F;
    float right = 0.0F;
    float top = 0.0F;
    float bottom = 0.0F;

    UIPadding();
    explicit UIPadding(float padding);
    UIPadding(float left, float right, float top, float bottom);
    void Set(float padding);
    void Set(float left, float right, float top, float bottom);
};