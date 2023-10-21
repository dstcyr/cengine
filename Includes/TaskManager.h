#pragma once
#include <functional>
#include <vector>

class CTaskManager
{
public:
    bool HasTasks() const;
    void Update(float dt);
    void Clear();

    template<typename TObject>
    inline void Add(TObject* userObject, bool(TObject::* callback)(float));

private:
    std::vector<std::function<bool(float)>> m_tasks;
};

template<typename TObject>
inline void CTaskManager::Add(TObject* userObject, bool(TObject::* callback)(float))
{
    auto func = std::bind(callback, userObject, std::placeholders::_1);
    m_tasks.push_back(func);
}
