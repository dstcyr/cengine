#pragma once

#include <vector>
#include <algorithm>

namespace Engine
{
    template<typename T>
    bool Contains(const std::vector<T*>& v, T* object)
    {
        return std::count(v.begin(), v.end(), object) > 0;
    }
}