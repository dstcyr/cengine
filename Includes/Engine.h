#pragma once
#include <stdint.h>
#include <string>
#include "Rect.h"
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
#endif

} EKey;

struct NColor
{
    NColor();
    NColor(uint8_t red, uint8_t green, uint8_t blue);
    NColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    static const NColor& Red;
    static const NColor& Green;
    static const NColor& Blue;
    static const NColor& White;
    static const NColor& Black;

    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    uint8_t alpha = 255;
};

class StateMachine;

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
    void FillRect(float x, float y, float w, float h, const NColor& color);
    void DrawRect(float x, float y, float w, float h, const NColor& color);
    void DrawRect(int x, int y, int w, int h, const NColor& color);
    void DrawString(const std::string& text, size_t fontId, float x, float y);
    void DrawTexture(size_t id, bool hflip, bool vflip, const NColor& color);
    void DrawTexture(size_t id, const Rect<float>& dst, double angle, bool hflip, bool vflip, const NColor& color);
    void DrawTexture(size_t id, const Rect<int>& src, const Rect<float>& dst, double angle, bool hflip, bool vflip, const NColor& color);
    void DrawPoint(float x, float y, const NColor& color);
    void DrawCircle(float x, float y, float r, const NColor& color);
    void DrawLine(float x1, float y1, float x2, float y2, const NColor& color);
    void PlayMusic(size_t id);
    void PlayMusic(size_t id, int loop);
    void PlaySFX(size_t id);
    void PlaySFX(size_t id, int loop);
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
}