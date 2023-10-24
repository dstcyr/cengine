#pragma once
#include <map>
#include <stack>
#include <string>

class StateMachine;

class IState
{
public:
    virtual ~IState() = default;
    virtual void OnEnter() = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnRender() = 0;
    virtual void OnExit() = 0;
};

class StateMachine
{
public:
    StateMachine();

    void Update(float deltaTime);
    void Render();
    void PushState(const std::string& state);
    void PopState();
    void SetState(const std::string& state);
    void Add(const std::string& state, IState* stateInstance);
    void Clear();
    void ClearStack();
    void Reset();

    IState* GetState() const;

private:
    std::map<const std::string, IState*> m_states;
    std::stack<IState*> m_stack;
};
