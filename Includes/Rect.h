#pragma once

template<typename T>
struct Rect
{
    Rect();
    Rect(T x, T y, T w, T h);

    void Set(T x, T y, T w, T h);
    void Center(T* x, T* y);

    T x;
    T y;
    T w;
    T h;
};

template<typename T>
void Rect<T>::Center(T* x, T* y)
{
    *x = this->x + w / 2;
    *y = this->y + h / 2;
}

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