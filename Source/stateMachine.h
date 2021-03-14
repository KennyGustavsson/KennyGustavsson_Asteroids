#pragma once
#include <iostream>
#include <vector>

class State {
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

class StateMachine
{
public:
	StateMachine(State* state)
	{
		_states.push_back(state);
		_states[_currentStateID]->Enter();
	}

	StateMachine()
	{
		
	}

	void Start()
	{
		_states[_currentStateID]->Enter();
	}

	~StateMachine()
	{
		
	}

	void ChangeState(int stateID)
	{
		if (stateID < 0 || stateID >= _states.size())
			return;

		_states[_currentStateID]->Exit();
		_currentStateID = stateID;
		_states[_currentStateID]->Enter();
	}

	void Update()
	{
		_states[_currentStateID]->Update();
	}

	void Render()
	{
		_states[_currentStateID]->Render();
	}

	int CurrentStateID()
	{
		return _currentStateID;
	}

	int AddState(State* state)
	{
		_states.push_back(state);
		return _states.size() - 1;
	}

private:
	std::vector<State*> _states;
	int _currentStateID = 0;
};