#include "Animation.h"
#include "Engine.h"

Animation::Animation()
{
    m_Texture = 0;
    m_FrameInRowCount = 0;
    m_FrameWidth = 0;
    m_FrameHeight = 0;
    m_FirstFrame = 0;
    m_LastFrame = 0;
    m_Delay = 0.0f;
    m_Elapsed = 0.0f;
    m_Playing = false;
    m_Loop = false;
    m_CurrentFrame = 0;
    m_CurrentClip = "";
}

bool Animation::Update(float dt)
{
    if (m_Playing)
    {
        m_Elapsed += dt;
        if (m_Elapsed >= m_Delay)
        {
            m_Elapsed = 0.0f;
            m_CurrentFrame++;

            if (m_CurrentFrame > m_LastFrame)
            {
                m_CurrentFrame = m_FirstFrame;
                if (!m_Loop)
                {
                    m_CurrentClip = "";
                    m_Playing = false;

                    return false;
                }
            }

            UpdateFrame();
        }
    }

    return true;
}

void Animation::Render(const Rect<float> destination)
{
    Engine::DrawTexture(m_Texture, m_Source, destination, 0.0f, false, false, NColor::White);
}

void Animation::Init(const std::string& filename, int frameInRows, int frameWidth, int frameHeight)
{
    m_Texture = Engine::LoadTexture(filename);

    m_FrameInRowCount = frameInRows;
    m_FrameWidth = frameWidth;
    m_FrameHeight = frameHeight;

    m_Source.x = 0;
    m_Source.y = 0;
    m_Source.w = m_FrameWidth;
    m_Source.h = m_FrameHeight;

    m_CurrentClip.clear();
}

void Animation::AddClip(const std::string& name, int start, int count, float delay)
{
    m_Clips.emplace(name, AnimationClip{ start, count, delay });
}

void Animation::Stop()
{
    m_Playing = false;
    m_CurrentFrame = 0;
    m_FirstFrame = 0;
    m_LastFrame = 0;
    m_Delay = 0.0f;
    m_Loop = false;
    m_CurrentClip.clear();
}

void Animation::Play(const std::string& name, bool loop)
{
    if (name != m_CurrentClip)
    {
        const AnimationClip _clip = m_Clips[name];
        m_CurrentFrame = _clip.start;
        m_FirstFrame = _clip.start;
        m_LastFrame = _clip.start + _clip.count - 1;
        m_Delay = _clip.delay;
        m_Loop = loop;

        UpdateFrame();
        m_Playing = true;
        m_CurrentClip = name;
    }
}

void Animation::UpdateFrame()
{
    const int _row = m_CurrentFrame / m_FrameInRowCount;
    const int _col = m_CurrentFrame - m_FrameInRowCount * _row;
    const int _x = m_FrameWidth * _col;
    const int _y = m_FrameHeight * _row;

    m_Source.x = _x;
    m_Source.y = _y;
    m_Source.w = m_FrameWidth;
    m_Source.h = m_FrameHeight;
}
