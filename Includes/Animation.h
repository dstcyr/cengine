#pragma once
#include "Rect.h"
#include <map>
#include <string>

struct AnimationClip
{
    int start;
    int count;
    float delay;
};

class Animation
{
public:
    virtual ~Animation() = default;
    Animation();
    Animation(const Animation& other)
    {
        m_Clips.clear();
        for (const auto& clip : other.m_Clips)
        {
            AddClip(clip.first, clip.second.start, clip.second.count, clip.second.delay);
        }

        m_Texture = other.m_Texture;
        m_FrameInRowCount = other.m_FrameInRowCount;
        m_FrameWidth = other.m_FrameWidth;
        m_FrameHeight = other.m_FrameHeight;
        m_FirstFrame = other.m_FirstFrame;
        m_LastFrame = other.m_LastFrame;
        m_Delay = other.m_Delay;
        m_Elapsed = other.m_Elapsed;
        m_Playing = other.m_Playing;
        m_Loop = other.m_Loop;
        m_CurrentFrame = other.m_CurrentFrame;
        m_CurrentClip = other.m_CurrentClip;
        m_Source = other.m_Source;
    }

    bool Update(float dt);
    void Render(const Rect<float> destination);
    void Init(const std::string& filename, int frameInRows, int frameWidth, int frameHeight);
    void AddClip(const std::string& name, int start, int count, float delay);
    void Stop();
    void Play(const std::string& name, bool loop);

private:
    void UpdateFrame();

    std::map<std::string, AnimationClip> m_Clips;

    size_t m_Texture;
    int m_FrameInRowCount = 0;
    int m_FrameWidth = 0;
    int m_FrameHeight = 0;
    int m_FirstFrame = 0;
    int m_LastFrame = 0;
    float m_Delay = 0.0f;
    float m_Elapsed = 0.0f;
    bool m_Playing = false;
    bool m_Loop = false;
    int m_CurrentFrame = 0;
    std::string m_CurrentClip;
    Rect<int> m_Source;
};