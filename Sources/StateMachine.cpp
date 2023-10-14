#include "StateMachine.h"
#include "Log.h"
#include <vector>

StateMachine::StateMachine()
{
}

void StateMachine::Update(float deltaTime)
{
    if (!m_stack.empty())
    {
        if (IState* topState = m_stack.top())
        {
            topState->OnUpdate(deltaTime);
        }
    }
}

void StateMachine::Render()
{
    if (!m_stack.empty())
    {
        if (IState* topState = m_stack.top())
        {
            topState->OnRender();
        }
    }
}

void StateMachine::PushState(const std::string& state)
{
    if (m_states.count(state) > 0)
    {
        IState* stateInstance = m_states[state];
        m_stack.push(stateInstance);
        stateInstance->OnEnter();
    }
}

void StateMachine::PopState()
{
    if (m_stack.size() > 0)
    {
        IState* stateInstance = m_stack.top();
        m_stack.pop();
        stateInstance->OnExit();
    }
}

void StateMachine::SetState(const std::string& state)
{
    ClearStack();
    PushState(state);
}

void StateMachine::Add(const std::string& state, IState* stateInstance)
{
    if (m_states.count(state) == 0)
    {
        m_states[state] = stateInstance;
    }
}

void StateMachine::Clear()
{
    ClearStack();
    for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
    {
        itr->second->OnExit();
        delete itr->second;
    }

    m_states.clear();
}

void StateMachine::ClearStack()
{
    while (!m_stack.empty())
    {
        IState* stateInstance = m_stack.top();
        m_stack.pop();
        stateInstance->OnExit();
    }
}

void StateMachine::Reset()
{
    std::vector<IState*> statesToAdd;
    while (!m_stack.empty())
    {
        IState* stateInstance = m_stack.top();
        m_stack.pop();
        stateInstance->OnExit();
        statesToAdd.push_back(stateInstance);
    }

    for (IState* state : statesToAdd)
    {
        m_stack.push(state);
        state->OnEnter();
    }
}