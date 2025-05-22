#include "UI/UIPadding.h"

UIPadding::UIPadding() :
    UIPadding(0.0F)
{
}

UIPadding::UIPadding(float padding) :
    UIPadding(padding, padding, padding, padding)
{
}

UIPadding::UIPadding(float left, float right, float top, float bottom) :
    left(left), right(right), top(top), bottom(bottom)
{
}

void UIPadding::Set(float padding)
{
    Set(padding, padding, padding, padding);
}

void UIPadding::Set(float left, float right, float top, float bottom)
{
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
}
