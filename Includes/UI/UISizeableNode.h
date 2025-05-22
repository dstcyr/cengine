#pragma once
#include "UINode.h"
#include "Rect.h"

class UISizeableNode : public UINode
{
public:
    virtual void SetWidth(float width);
    virtual void SetHeight(float height);
    virtual void SetSize(float width, float height);

protected:
    UISizeableNode() = default;
    UISizeableNode(const UISizeableNode& other) = default;
    UISizeableNode& operator=(const UISizeableNode&) = default;

    Rect<float> m_Bounds;
};