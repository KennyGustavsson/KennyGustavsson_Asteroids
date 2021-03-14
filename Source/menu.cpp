#include "menu.h"

menu::menu(StateMachine* sm)
{
	_sm = sm;
	_font = ResourcePool::GetInstance()->GetFont();

	_titleSurface = TTF_RenderText_Solid(_font, _titleText, _textColor);
	_titleTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, _titleSurface);

	_playSurface = TTF_RenderText_Solid(_font, _playText, _textColor);
	_playTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, _playSurface);

	_titleRect = { (int)DisplayManager::screenSize->x / 2 - _titleRect.w / 2,
				(int)DisplayManager::screenSize->y / 4 - _titleRect.h / 2,
				_titleRect.w,
				_titleRect.h };

	_playRect = { (int)DisplayManager::screenSize->x / 2 - _playRect.w / 2,
				(int)DisplayManager::screenSize->y / 2 - _playRect.h / 2,
				_playRect.w,
				_playRect.h };

	_highScoreRect = { (int)DisplayManager::screenSize->x / 2 - _highScoreRect.w / 2,
				(int)DisplayManager::screenSize->y / 2 + _highScoreRect.h * 2,
				_highScoreRect.w,
				_highScoreRect.h };
}

menu::~menu()
{
	// Clean up text
	SDL_FreeSurface(_titleSurface);
	SDL_FreeSurface(_playSurface);

	SDL_DestroyTexture(_titleTexture);
	SDL_DestroyTexture(_playTexture);
}

void menu::Enter()
{
	std::pair<std::string, int> score =  GameManager::GetInstance()->Load();

	std::string text = score.first + "   " + std::to_string(score.second);

	_highScoreSurface = TTF_RenderText_Solid(_font, text.c_str(), _textColor);
	_highScoreTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, _highScoreSurface);
}

void menu::Update()
{
	if (SDL_GetMouseState(&_x, &_y) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
	{
		if (_x > _playRect.x && _x < _playRect.x + _playRect.w &&
			_y > _playRect.y && _y < _playRect.y + _playRect.h)
		{
			_sm->ChangeState(1);
		}	
	}
	else if (_currentKeyStates[SDL_SCANCODE_RETURN] && _timer > _keyStateDelay)
	{
		_timer = 0;
		_sm->ChangeState(1);
	}
	
	_timer += Time::deltaTime;
}

void menu::Render()
{
	SDL_SetRenderDrawColor(DisplayManager::renderer, 0, 0, 0, 255);
	SDL_RenderClear(DisplayManager::renderer);

	if (_font != nullptr) {
		SDL_RenderCopy(DisplayManager::renderer, _titleTexture, NULL, &_titleRect);
		SDL_RenderCopy(DisplayManager::renderer, _playTexture, NULL, &_playRect);
		SDL_RenderCopy(DisplayManager::renderer, _highScoreTexture, NULL, &_highScoreRect);
	}

	SDL_RenderPresent(DisplayManager::renderer);
}

void menu::Exit()
{

}
