#include "UI/UIImage.h"
#include "Engine.h"

#define DEBUG_UI

std::shared_ptr<UIImage> UIImage::Create(const std::string& filename)
{
    return std::shared_ptr<UIImage>(new UIImage(filename));
}

UIImage::UIImage(const std::string& filename)
{
    SetTexture(filename);
}

void UIImage::Draw(float x, float y)
{
    if (m_IsVisible)
    {
        m_Bounds.x = x + m_Padding.left;
        m_Bounds.y = y + m_Padding.top;
        Engine::DrawTexture(m_TextureId, m_Bounds);
    }

#if defined(DEBUG_UI)
    float totalWidth = GetWidth();
    float totalHeight = GetHeight();
    Engine::DrawRect(x, y, totalWidth, totalHeight, NColor::Yellow);
#endif
}

float UIImage::GetWidth()
{
    return m_Bounds.w + m_Padding.left + m_Padding.right;
}

float UIImage::GetHeight()
{
    return m_Bounds.h + m_Padding.top + m_Padding.bottom;
}

void UIImage::SetTexture(const std::string& filename)
{
    m_TextureId = Engine::LoadTexture(filename);

    if (m_Bounds.w == 0 || m_Bounds.h == 0)
    {
        int textureWidth = 0;
        int textureHeight = 0;
        Engine::GetTextureSize(m_TextureId, &textureWidth, &textureHeight);

        m_Bounds.w = static_cast<float>(textureWidth);
        m_Bounds.h = static_cast<float>(textureHeight);
    }
}
