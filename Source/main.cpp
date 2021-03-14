#include "game.h"
#include "Time.h"
#include "Timer.h"
#include "displayManager.h"
#include "stateMachine.h"
#include "menu.h"
#include "Audio.h"
#include "highscoreInput.h"
#include "audio.h"

float Time::deltaTime = 0;
float Time::totalElapsedSeconds = 0;
float Time::timeScale = 1;

int WindowDimensions::width = 800;
int WindowDimensions::height = 600;

bool _isRunning = true;
const Uint8* _currentKeyStates = SDL_GetKeyboardState(NULL);

void HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		_isRunning = false;
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	DisplayManager::Init("Hej", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowDimensions::width, WindowDimensions::height, false);

	// Text init
	if (TTF_Init() == -1) {
		std::cout << TTF_GetError() << std::endl;
		_isRunning = false;
	}

	// Audio init
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << Mix_GetError() << std::endl;
		_isRunning = false;
	}
	Mix_AllocateChannels(128);

	Music music = Music("Assets/music.wav", 20);
	music.Play();

	StateMachine sm = StateMachine();
	menu* menuInstance = new menu(&sm);
	game* gameInstance = new game();
	HighscoreInput* highscore = new HighscoreInput(&sm);

	sm.AddState(menuInstance);
	sm.AddState(gameInstance);
	sm.AddState(highscore);

	sm.Start();

	Timer timer;
	timer.Start();

	while (_isRunning) {
		if (GameManager::GetInstance()->IsGameOver()) {
			sm.ChangeState(2);
			Time::timeScale = 1;
		}

		if (_currentKeyStates[SDL_SCANCODE_ESCAPE]) {
			sm.ChangeState(0);
			GameManager::GetInstance()->Reset();
			Time::timeScale = 1;
		}

		HandleEvents();
		sm.Update();
		sm.Render();

		Time::deltaTime = (timer.elapsedSeconds() - Time::totalElapsedSeconds) * Time::timeScale;
		Time::totalElapsedSeconds = timer.elapsedSeconds() * Time::timeScale;
	}

	gameInstance->Clean();

	delete gameInstance;
	delete menuInstance;
	delete highscore;

	return 0;
}