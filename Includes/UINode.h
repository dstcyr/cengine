#pragma once
#include "UIPadding.h"

class UINode
{
public:
    virtual ~UINode() = default;

    virtual void Draw(float x, float y) = 0;
    virtual float GetWidth() = 0;
    virtual float GetHeight() = 0;

    void SetPadding(float left, float right, float top, float bottom);
    void SetPadding(float padding);
    void SetVisible(bool visible);
    bool IsVisible() const;

protected:
    UINode() = default;
    UINode(const UINode& other) = default;
    UINode& operator=(const UINode&) = default;

    UIPadding m_Padding;
    bool m_IsVisible = true;
};