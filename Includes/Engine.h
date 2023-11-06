#pragma once
#include <cstdint>
#include <string>
#include "Rect.h"
#include "Vec2D.h"
#include <map>

typedef enum
{
    KEY_UP = 82,            // up
    KEY_LEFT = 80,          // left
    KEY_DOWN = 81,          // down
    KEY_RIGHT = 79,         // right

    KEY_A = 27,             // a (X)
    KEY_B = 29,             // b (Z)
    KEY_START = 40,         // start (ENTER)
    KEY_SELECT = 229,       // select (RSHIFT)

    KEY_ESCAPE = 41,        // power off the game
    KEY_RESET  = 62,        // reset the game

#if defined(_DEBUG)
    KEY_DEBUG = 44,         // DEBUG
    KEY_1 = 30,
    KEY_2 = 31,
    KEY_3 = 32,
    KEY_4 = 33,
    KEY_5 = 34,
    KEY_6 = 35,
    KEY_7 = 36,
    KEY_8 = 37,
    KEY_9 = 38,
    KEY_0 = 39,
#endif

} EKey;

struct NColor
{
    NColor();
    NColor(uint8_t red, uint8_t green, uint8_t blue);
    NColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    static const NColor& Black;
    static const NColor& MediumBlue;
    static const NColor& DarkBlue;
    static const NColor& LightBlue;
    static const NColor& Turquoise;
    static const NColor& Purple;
    static const NColor& DarkPurple;
    static const NColor& LightPurple;
    static const NColor& DarkGreen;
    static const NColor& MediumGreen;
    static const NColor& LightGreen;
    static const NColor& DarkGray;
    static const NColor& MediumGray;
    static const NColor& LightGray;
    static const NColor& White;
    static const NColor& DarkBrown;
    static const NColor& ReddishBrown;
    static const NColor& LightBrown;
    static const NColor& DarkOrange;
    static const NColor& Orange;
    static const NColor& LightOrange;
    static const NColor& DarkYellow;
    static const NColor& LightYellow;
    static const NColor& Yellow;
    static const NColor& DarkPink;
    static const NColor& LightPink;
    static const NColor& Pink;
    static const NColor& DarkRed;
    static const NColor& LightRed;
    static const NColor& Red;
    static const NColor& LightBeige;
    static const NColor& Tan;
    static const NColor& PaleYellow;
    static const NColor& DarkCream;
    static const NColor& LightCream;
    static const NColor& DarkTurquoise;
    static const NColor& LightTurquoise;
    static const NColor& DarkSkyBlue;
    static const NColor& LightSkyBlue;
    static const NColor& DarkLavender;
    static const NColor& LightLavender;
    static const NColor& DarkPurpleBlue;
    static const NColor& LightPurpleBlue;
    static const NColor& DarkForestGreen;
    static const NColor& LightForestGreen;
    static const NColor& DarkOliveGreen;
    static const NColor& LightOliveGreen;
    static const NColor& DarkYellowGreen;
    static const NColor& LightYellowGreen;
    static const NColor& DarkLimeGreen;
    static const NColor& LightLimeGreen;
    static const NColor& DarkPeach;
    static const NColor& LightPeach;
    static const NColor& DarkBeige;

    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    uint8_t alpha = 255;
};

class StateMachine;
class IState;

namespace Engine
{
    bool Initialize(const char* title, int width, int height);
    void Close();
    void EnterGameLoop(StateMachine* fsm);
    bool GetKey(EKey key);
    bool GetKeyDown(EKey key);
    bool GetKeyUp(EKey key);
    size_t LoadFont(const std::string& filename, const std::string& name, int fontSize, const NColor& color);
    size_t LoadTexture(const std::string& filename);
    size_t LoadSound(const std::string& filename);
    size_t LoadMusic(const std::string& filename);
    void FillRect(int x, int y, int w, int h, const NColor& color);
    void FillRect(float x, float y, float w, float h, const NColor& color);
    void FillRect(const Rect<float>& rect, const NColor& color);
    void DrawRect(float x, float y, float w, float h, const NColor& color);
    void DrawRect(const Rect<float>& rect, const NColor& color);
    void DrawRect(int x, int y, int w, int h, const NColor& color);
    void DrawString(const std::string& text, size_t fontId, float x, float y);
    void DrawTexture(size_t id, bool hflip, bool vflip, const NColor& color);
    void DrawTexture(size_t id, int x, int y, int w, int h);
    void DrawTexture(size_t id, float x, float y, float w, float h);
    void DrawTexture(size_t id, int x, int y);
    void DrawTexture(size_t id, float x, float y);
    void DrawTexture(size_t id, const Rect<float>& dst, double angle, bool hflip, bool vflip, const NColor& color);
    void DrawTexture(size_t id, const Rect<float>& dst);
    void DrawTexture(size_t id, const Rect<int>& src, const Rect<float>& dst, double angle, bool hflip, bool vflip, const NColor& color);
    void DrawPoint(float x, float y, const NColor& color);
    void DrawCircle(float x, float y, float r, const NColor& color);
    void DrawLine(float x1, float y1, float x2, float y2, const NColor& color);
    void DrawBezier(const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d, const NColor& color);
    void DrawBSpline(const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d, const NColor& color);
    void DrawCatmullRom(const Vec2D& P0, const Vec2D& P1, const Vec2D& P2, const Vec2D& P3, float d, const NColor& color);
    void GetTextureSize(size_t id, int* w, int* h);
    void PlayMusic(size_t id);
    void PlayMusic(size_t id, int loop);
    void PlaySFX(size_t id);
    void PlaySFX(size_t id, int loop);
    void PlaySFX(size_t id, int channel, int loop);
    void PauseMusic();
    void StopMusic();
    void ResumeMusic();
    void SetVolume(int volume);
    void SetVolume(size_t soundId, int volume);
    void ClearTextureCache();
    void ClearFontCache();
    void SetState(const std::string& state);
    void PushState(const std::string& state);
    void PopState();
    IState* GetTopState();
}