#include "UINode.h"

void UINode::SetPadding(float left, float right, float top, float bottom)
{
    m_Padding.Set(left, right, top, bottom);
}

void UINode::SetPadding(float padding)
{
    m_Padding.Set(padding);
}

void UINode::SetVisible(bool visible)
{
    m_IsVisible = visible;
}

bool UINode::IsVisible() const
{
    return m_IsVisible;
}