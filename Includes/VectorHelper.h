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

    template<typename T>
    void Remove(std::vector<T*>& v, T* object)
    {
        auto it = v.begin();
        while (it != v.end())
        {
            if (*it == object)
            {
                it = v.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}