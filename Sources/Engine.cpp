#define WIN32_LEAN_AND_MEAN

#include "Engine.h"
#include "Log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDL_FontCache.h"
#include <time.h>
#include <Windows.h>
#include "StateMachine.h"
#include <map>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

bool isInitialized = false;
bool isRunning = false;

#if defined(_DEBUG)
int mouseX = 0;
int mouseY = 0;
#endif

SDL_Window* window;
SDL_Renderer* renderer;
const unsigned char* keyStates = nullptr;
unsigned char* oldKeyStates = nullptr;
StateMachine* currentFSM;

std::map<size_t, SDL_Texture*> textureCache;
std::map<size_t, FC_Font*> fontCache;
std::map<size_t, Mix_Chunk*> soundCache;
std::map<size_t, Mix_Music*> musicCache;

const NColor& NColor::Red = NColor(255, 0, 0);
const NColor& NColor::Green = NColor(0, 255, 0);
const NColor& NColor::Blue = NColor(0, 0, 255);
const NColor& NColor::Black = NColor(0, 0, 0);
const NColor& NColor::White = NColor(255, 255, 255);

NColor::NColor() :
    NColor(0, 0, 0, 255)
{}

NColor::NColor(const uint8_t red, const uint8_t green, const uint8_t blue) :
    NColor(red, green, blue, 255)
{}

NColor::NColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) :
    red(red), green(green), blue(blue), alpha(alpha)
{}

void Engine::ClearTextureCache()
{
    for (auto& KeyPair : textureCache)
    {
        if (KeyPair.second)
        {
            SDL_DestroyTexture(KeyPair.second);
        }
    }

    textureCache.clear();
}

void Engine::ClearFontCache()
{
    for (auto& KeyPair : fontCache)
    {
        if (KeyPair.second)
        {
            FC_FreeFont(KeyPair.second);
        }
    }

    fontCache.clear();
}

void Engine::SetState(const std::string& state)
{
    CHECK(currentFSM);
    currentFSM->SetState(state);
}

void Engine::PushState(const std::string& state)
{
    CHECK(currentFSM);
    currentFSM->PushState(state);
}

void Engine::PopState()
{
    CHECK(currentFSM);
    currentFSM->PopState();
}

void EngineCleanup()
{
    isInitialized = false;
    Engine::ClearTextureCache();
    Engine::ClearFontCache();
    if (oldKeyStates)
    {
        free(oldKeyStates);
    }

    TTF_Quit();
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ProcessMessages()
{
    memcpy(oldKeyStates, keyStates, 512);

    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent))
    {
        switch (windowEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            keyStates = SDL_GetKeyboardState(nullptr);
            break;

#if defined(_DEBUG)
        case SDL_MOUSEMOTION:
            mouseX = windowEvent.motion.x;
            mouseY = windowEvent.motion.y;
            break;
#endif
        }
    }
}

bool Engine::Initialize(const char* title, int width, int height)
{
    if (!isInitialized)
    {
        if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        {
            LOG(LL_ERROR, SDL_GetError());
            return false;
        }

        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_TOOLTIP);

        if (window == nullptr)
        {
            LOG(LL_ERROR, SDL_GetError());
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == nullptr)
        {
            LOG(LL_ERROR, SDL_GetError());
            return false;
        }

        TTF_Init();
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 512);

        const unsigned seed = static_cast<unsigned>(SDL_GetTicks());
        srand(seed);

        keyStates = SDL_GetKeyboardState(nullptr);
        oldKeyStates = static_cast<unsigned char*>(malloc(512));

        isInitialized = true;
    }

    return true;
}

void Engine::Close()
{
    isRunning = false;
}

void Engine::EnterGameLoop(StateMachine* fsm)
{
    CHECK(fsm);
    CHECK(isInitialized);
    CHECK(!isRunning);

    currentFSM = fsm;
    isRunning = true;
    clock_t _end = clock();
    const int TARGET_FPS = 120;
    const int MS_PER_FRAME = 1000 / TARGET_FPS;
    while (isRunning)
    {
        const clock_t _start = clock();
        float _dt = (_start - _end) * 0.001f;

        ProcessMessages();

#if defined(_DEBUG)
        if (GetKeyDown(KEY_ESCAPE))
        {
            isRunning = false;
        }

        if (GetKeyDown(KEY_RESET))
        {
            ClearTextureCache();
            ClearFontCache();
            currentFSM->Reset();
        }

        if (GetKeyDown(KEY_DEBUG))
        {
            LOG(LL_DEBUG, "Mouse position: %d, %d", mouseX, mouseY);
        }
#endif

        currentFSM->Update(_dt);

        if (isRunning)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            fsm->Render();
            SDL_RenderPresent(renderer);

            int _restTime = _start + MS_PER_FRAME - clock();
            if (_restTime > 0)
            {
                Sleep(_restTime);
            }

            _end = _start;
        }
    }

    currentFSM->Clear();
    EngineCleanup();
}

bool Engine::GetKey(EKey key)
{
    if (keyStates != nullptr && oldKeyStates != nullptr)
    {
        if (oldKeyStates[key] == 1 && keyStates[key] == 1)
        {
            return true;
        }
    }

    return false;
}

bool Engine::GetKeyDown(EKey key)
{
    if (keyStates != nullptr && oldKeyStates != nullptr)
    {
        if (oldKeyStates[key] == 0 && keyStates[key] == 1)
        {
            return true;
        }
    }

    return false;
}

bool Engine::GetKeyUp(EKey key)
{
    if (keyStates != nullptr && oldKeyStates != nullptr)
    {
        if (oldKeyStates[key] == 1 && keyStates[key] == 0)
        {
            return true;
        }
    }

    return false;
}

void Engine::FillRect(float x, float y, float w, float h, const NColor& color)
{
    SDL_Rect rect = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(w),
        static_cast<int>(h)
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderFillRect(renderer, &rect);
}

void Engine::DrawRect(float x, float y, float w, float h, const NColor& color)
{
    int fx = static_cast<int>(x);
    int fy = static_cast<int>(y);
    int fw = static_cast<int>(w);
    int fh = static_cast<int>(h);
    
    DrawRect(fx, fy, fw, fh, color );
}

void Engine::DrawRect(int x, int y, int w, int h, const NColor& color)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawRect(renderer, &rect);
}

size_t Engine::LoadFont(const std::string& filename, const std::string& name, int fontSize, const NColor& color)
{
    const size_t _fntId = std::hash<std::string>()(filename + name);
    if (fontCache.count(_fntId) > 0)
    {
        return _fntId;
    }

    FC_Font* _font = FC_CreateFont();
    SDL_Color fontColor = FC_MakeColor(color.red, color.green, color.blue, color.alpha);
    FC_LoadFont(_font, renderer, filename.c_str(), fontSize, fontColor, 0);
    if (_font)
    {
        fontCache.emplace(_fntId, _font);
        return _fntId;
    }

    LOG(LL_ERROR, "Error with font: %s", filename);
    LOG(LL_ERROR, SDL_GetError());
    return 0;
}

void Engine::DrawString(const std::string& text, size_t fontId, float x, float y)
{
    FC_Font* font = fontCache[fontId];
    FC_Draw(font, renderer, x, y, text.c_str());
}

size_t Engine::LoadTexture(const std::string& filename)
{
    size_t textureId = std::hash<std::string>()(filename);
    if (textureCache.count(textureId) > 0)
    {
        return textureId;
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
    if (texture)
    {
        textureCache.emplace(textureId, texture);
        return textureId;
    }

    LOG(LL_ERROR, "Cannot load texture %s", filename.c_str());
    LOG(LL_ERROR, SDL_GetError());
    return 0;
}

void Engine::DrawTexture(size_t id, bool hflip, bool vflip, const NColor& color)
{
    int flipValue = SDL_FLIP_NONE;
    if (hflip)
    {
        flipValue = SDL_FLIP_HORIZONTAL;
    }

    if (vflip)
    {
        flipValue |= SDL_FLIP_VERTICAL;
    }

    const SDL_RendererFlip renderFlip = static_cast<SDL_RendererFlip>(flipValue);
    SDL_Texture* texture = textureCache[id];
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, color.alpha);
    SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);
    SDL_RenderCopyEx(renderer, texture, nullptr, nullptr, 0.0f, nullptr, renderFlip);
}

void Engine::DrawTexture(size_t id, const Rect<float>& dst, double angle, bool hflip, bool vflip, const NColor& color)
{
    SDL_Rect destination = {
        static_cast<int>(dst.x),
        static_cast<int>(dst.y),
        static_cast<int>(dst.w),
        static_cast<int>(dst.h)
    };

    int flipValue = SDL_FLIP_NONE;
    if (hflip)
    {
        flipValue = SDL_FLIP_HORIZONTAL;
    }

    if (vflip)
    {
        flipValue |= SDL_FLIP_VERTICAL;
    }

    const SDL_RendererFlip renderFlip = static_cast<SDL_RendererFlip>(flipValue);
    SDL_Texture* texture = textureCache[id];
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, color.alpha);
    SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);
    SDL_RenderCopyEx(renderer, texture, nullptr, &destination, angle, nullptr, renderFlip);
}

void Engine::DrawTexture(size_t id, const Rect<int>& src, const Rect<float>& dst, double angle, bool hflip, bool vflip, const NColor& color)
{
    SDL_Rect source = {
        src.x,
        src.y,
        src.w,
        src.h
    };

    SDL_Rect destination = {
        static_cast<int>(dst.x),
        static_cast<int>(dst.y),
        static_cast<int>(dst.w),
        static_cast<int>(dst.h)
    };

    int flipValue = SDL_FLIP_NONE;
    if (hflip)
    {
        flipValue = SDL_FLIP_HORIZONTAL;
    }

    if (vflip)
    {
        flipValue |= SDL_FLIP_VERTICAL;
    }

    const SDL_RendererFlip renderFlip = static_cast<SDL_RendererFlip>(flipValue);
    SDL_Texture* texture = textureCache[id];
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, color.alpha);
    SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);
    SDL_RenderCopyEx(renderer, texture, &source, &destination, angle, nullptr, renderFlip);
}

void Engine::DrawPoint(float x, float y, const NColor& color)
{
    const int _x = static_cast<int>(x);
    const int _y = static_cast<int>(y);
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawPoint(renderer, _x, _y);
}

void Engine::DrawCircle(float x, float y, float r, const NColor& color)
{
    float tx = x;
    float ty = y;
    double angle = 0.0;

    while (angle < 6.3)
    {
        tx = static_cast<float>(x + r * cos(angle));
        ty = static_cast<float>(y + r * sin(angle));
        DrawPoint(tx, ty, color);

        angle += 0.01;
    }
}

void Engine::DrawLine(float x1, float y1, float x2, float y2, const NColor& color)
{
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawLine(renderer,
        static_cast<int>(x1),
        static_cast<int>(y1),
        static_cast<int>(x2),
        static_cast<int>(y2));
}

size_t Engine::LoadMusic(const std::string& filename)
{
    const size_t _musId = std::hash<std::string>()(filename);
    if (musicCache.count(_musId) > 0)
    {
        return _musId;
    }

    Mix_Music* _mus = Mix_LoadMUS(filename.c_str());
    if (_mus)
    {
        musicCache.emplace(_musId, _mus);
        return _musId;
    }

    LOG(LL_ERROR, "Error with music: %s", filename.c_str());
    LOG(LL_ERROR, Mix_GetError());

    return 0;
}

size_t Engine::LoadSound(const std::string& filename)
{
    const size_t _sfxId = std::hash<std::string>()(filename);
    if (soundCache.count(_sfxId) > 0)
    {
        return _sfxId;
    }

    Mix_Chunk* _sfx = Mix_LoadWAV(filename.c_str());
    if (_sfx)
    {
        soundCache.emplace(_sfxId, _sfx);
        return _sfxId;
    }

    LOG(LL_ERROR, "Error with sfx: %s", filename.c_str());
    LOG(LL_ERROR, Mix_GetError());
    return 0;
}

void Engine::PlayMusic(size_t id)
{
    PlayMusic(id, -1);
}

void Engine::PlayMusic(size_t id, int loop)
{
    Mix_PlayMusic(musicCache[id], loop);
}

void Engine::PlaySFX(size_t id)
{
    PlaySFX(id, 0);
}

void Engine::PlaySFX(size_t id, int loop)
{
    Mix_PlayChannel(-1, soundCache[id], loop);
}

void Engine::PauseMusic()
{
    Mix_PauseMusic();
}

void Engine::StopMusic()
{
    Mix_HaltMusic();
}

void Engine::ResumeMusic()
{
    Mix_ResumeMusic();
}

void Engine::SetVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

void Engine::SetVolume(size_t soundId, int volume)
{
    Mix_VolumeChunk(soundCache[soundId], volume);
}
