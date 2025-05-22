#include "UI/UISizeableNode.h"

void UISizeableNode::SetWidth(float width)
{
    m_Bounds.w = width;
    if (m_Bounds.w < 0.0F)
    {
        m_Bounds.w = 0.0F;
    }
}

void UISizeableNode::SetHeight(float height)
{
    m_Bounds.h = height;
    if (m_Bounds.h < 0.0F)
    {
        m_Bounds.h = 0.0F;
    }
}

void UISizeableNode::SetSize(float width, float height)
{
    SetWidth(width);
    SetHeight(height);
}
