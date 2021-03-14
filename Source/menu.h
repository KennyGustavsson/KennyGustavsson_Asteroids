#pragma once
#include "stateMachine.h"
#include "displayManager.h"
#include "resourcePool.h"
#include "gameManager.h"
#include <iostream>
#include "time.h"

class menu : public State
{
public:
	menu(StateMachine* sm);
	~menu();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Exit() override;

private:
	StateMachine* _sm;
	const Uint8* _currentKeyStates = SDL_GetKeyboardState(NULL);

	TTF_Font* _font = nullptr;
	SDL_Color _textColor = {255, 255, 255, 255};

	// Title
	SDL_Surface* _titleSurface = nullptr;
	SDL_Texture* _titleTexture = nullptr;
	SDL_Rect _titleRect = {300, 150, 200, 100};
	const char *_titleText = "Asteroids";

	// Play Button
	SDL_Surface* _playSurface = nullptr;
	SDL_Texture* _playTexture = nullptr;
	SDL_Rect _playRect = { 350, 250, 100, 100 };
	const char* _playText = "Play";

	// Highscore
	SDL_Surface* _highScoreSurface = nullptr;
	SDL_Texture* _highScoreTexture = nullptr;
	SDL_Rect _highScoreRect = { 350, 450, 100, 100 };

	int _x = -1;
	int _y = -1;

	float _timer;
	float _keyStateDelay = 1.0f;
};

