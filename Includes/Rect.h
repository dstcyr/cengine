#pragma once

template<typename T>
struct Rect
{
    Rect();
    Rect(T x, T y, T w, T h);
    void Set(T x, T y, T w, T h);

    T x;
    T y;
    T w;
    T h;
};

template<typename T>
inline Rect<T>::Rect() :
    Rect(0, 0, 0, 0)
{
}

template<typename T>
inline Rect<T>::Rect(T x, T y, T w, T h) :
    x(x), y(y), w(w), h(h)
{
}

template<typename T>
inline void Rect<T>::Set(T x, T y, T w, T h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}