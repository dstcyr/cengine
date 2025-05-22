#pragma once
#include "UI/UISizeableNode.h"
#include <memory>
#include <string>

class UIImage final : public UISizeableNode
{
public:
    static std::shared_ptr<UIImage> Create(const std::string& filename);

    void Draw(float x, float y) override;
    float GetWidth() override;
    float GetHeight() override;
    void SetTexture(const std::string& filename);

private:
    UIImage() = default;
    explicit UIImage(const std::string& filename);
    UIImage(const UIImage& other) = default;
    UIImage& operator=(const UIImage&) = default;

    size_t m_TextureId = 0;
};
