#include "TaskManager.h"

bool CTaskManager::HasTasks() const
{
    return !m_tasks.empty();
}

void CTaskManager::Update(float dt)
{
    if (HasTasks())
    {
        auto it = m_tasks.begin();
        if (!(*it)(dt))
        {
            m_tasks.erase(it);
        }
    }
}

void CTaskManager::Clear()
{
    m_tasks.clear();
}
