#include "highscoreInput.h"

HighscoreInput::HighscoreInput(StateMachine* sm)
{
	_sm = sm;
	_font = ResourcePool::GetInstance()->GetFont();

	_titleSurface = TTF_RenderText_Solid(_font, _titleText, _textColor);
	_titleTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, _titleSurface);

	UpdateText();
}

HighscoreInput::~HighscoreInput()
{
	SDL_FreeSurface(_titleSurface);
	SDL_DestroyTexture(_titleTexture);
}

void HighscoreInput::Enter()
{
	SDL_StartTextInput();
}

void HighscoreInput::Update()
{
	while (SDL_PollEvent(&e) != 0) 
	{
		if (e.type == SDL_TEXTINPUT && text.length() < maxTextLength)
		{
			text += e.text.text;
			UpdateText();
		}
	}

	if (_currentKeyStates[SDL_SCANCODE_BACKSPACE] && text.length() > 0 && _timer > backSpaceTime)
	{
		text.pop_back();
		_timer = 0;
		UpdateText();
	}

	if (_currentKeyStates[SDL_SCANCODE_RETURN]) 
	{
		SDL_StopTextInput();

		GameManager::GetInstance()->Save(text);
		GameManager::GetInstance()->Reset();

		_sm->ChangeState(0);
	}

	_timer += Time::deltaTime;
}

void HighscoreInput::Render()
{
	SDL_SetRenderDrawColor(DisplayManager::renderer, 0, 0, 0, 255);
	SDL_RenderClear(DisplayManager::renderer);

	if (_font != nullptr) 
	{
		SDL_RenderCopy(DisplayManager::renderer, _titleTexture, NULL, &_titleRect);

		if(_nameTexture != nullptr)
			SDL_RenderCopy(DisplayManager::renderer, _nameTexture, NULL, &_nameRect);
	}

	SDL_RenderPresent(DisplayManager::renderer);
}

void HighscoreInput::Exit()
{
	
}

void HighscoreInput::UpdateText()
{
	SDL_FreeSurface(_nameSurface);
	SDL_DestroyTexture(_nameTexture);

	_nameSurface = TTF_RenderText_Solid(_font, text.c_str(), _textColor);
	_nameTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, _nameSurface);
}
