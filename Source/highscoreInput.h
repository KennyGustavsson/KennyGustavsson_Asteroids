#pragma once
#include "stateMachine.h"
#include "SDL_ttf.h"
#include "resourcePool.h"
#include "displayManager.h"
#include "time.h"
#include "gameManager.h"

class HighscoreInput : public State
{
public:
	HighscoreInput(StateMachine* sm);
	~HighscoreInput();

	// Inherited via State
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Exit() override;

private:
	void UpdateText();

	StateMachine* _sm;

	const Uint8* _currentKeyStates = SDL_GetKeyboardState(NULL);

	TTF_Font* _font = nullptr;
	SDL_Color _textColor = { 255, 255, 255, 255 };

	// Title
	SDL_Surface* _titleSurface = nullptr;
	SDL_Texture* _titleTexture = nullptr;
	SDL_Rect _titleRect = { 300, 150, 200, 100 };
	const char* _titleText = "Enter Name";

	// Enter name
	SDL_Surface* _nameSurface = nullptr;
	SDL_Texture* _nameTexture = nullptr;
	SDL_Rect _nameRect = { 300, 250, 200, 100 };
	std::string text = "";

	int maxTextLength = 10;

	SDL_Event e;

	float _timer = 0;
	float backSpaceTime = 0.2f;
};

