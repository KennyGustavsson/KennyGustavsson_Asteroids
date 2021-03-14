#include "game.h"

game::game()
{
	font = ResourcePool::GetInstance()->GetFont();
	textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, textSurface);

	_score = GameManager::GetInstance()->GetScore();
	UpdateText();
}

game::~game()
{
	// Clean up text
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void game::Update()
{
	if (!_spawned)
	{
		GameManager::GetInstance()->ResetAsteroidAmount();
		ObjectHandler::GetInstance()->ResetAsteroids();
		ObjectHandler::GetInstance()->SpawnAsteroid(0, _enemiesToSpawn);
		_spawned = true;
	}

	if (_alienTimer > _alienTime && !_alienSpawned) 
	{
		_alien->SetPos(vector2(0, 0));
		_alien->SetActive(true);
		_alienSpawned = true;
	}

	if (_score != GameManager::GetInstance()->GetScore())
	{
		_score = GameManager::GetInstance()->GetScore();
		UpdateText();
	}

	_player->Update();
	_playerPos = _player->GetPos();

	_alien->Update();

	ObjectHandler::GetInstance()->Update();
	CollisionHandler::GetInstance()->Update();

	if (GameManager::GetInstance()->GetAsteroidAmount() == 0)
	{
		_enemiesToSpawn++;
		_spawned = false;
		_player->SetKillable(false);
		ObjectHandler::GetInstance()->ResetAsteroids();
		_alienSpawned = false;
		_alienTimer = 0;
	}

	_alienTimer += Time::deltaTime;
}

void game::Render()
{
	SDL_SetRenderDrawColor(DisplayManager::renderer, 0, 0, 0, 255);
	SDL_RenderClear(DisplayManager::renderer);

	ObjectHandler::GetInstance()->Render();

	if (font != nullptr) {
		SDL_RenderCopy(DisplayManager::renderer, textTexture, NULL, &textRect);
	}

	_player->Render(DisplayManager::renderer);
	_alien->Render(DisplayManager::renderer);

	SDL_RenderPresent(DisplayManager::renderer);
}

void game::Enter()
{
	GameManager::GetInstance()->Reset();

	for (int i = 0; i < asteroidBigAmount; i++)
	{
		ObjectPool::GetInstance()->AddAsteroidBig(new asteroid(40, 0));
	}

	for (int i = 0; i < asteroidMediumAmount; i++)
	{
		ObjectPool::GetInstance()->AddAsteroidMedium(new asteroid(20, 1));
	}

	for (int i = 0; i < asteroidSmallAmount; i++)
	{
		ObjectPool::GetInstance()->AddAsteroidSmall(new asteroid(10, 2));
	}

	for (int i = 0; i < bulletAmount; i++)
	{
		ObjectPool::GetInstance()->AddBullet(new Bullet());
	}

	for (int i = 0; i < alienBulletAmount; i++)
	{
		ObjectPool::GetInstance()->AddAlienBullet(new BulletAlien());
	}

	vector2 pPos = *DisplayManager::screenSize;
	pPos = pPos / 2;

	_player = new player(pPos.x, pPos.y, DisplayManager::screenSize);
	_player->SetPos(pPos);
	_player->SetVel(vector2(0, 0));
	_player->SetActive(true);
	CollisionHandler::GetInstance()->AddCollider(*_player);

	_alien = new alien(&_playerPos);

	_score = GameManager::GetInstance()->GetScore();
	UpdateText();

	_alienSpawned = false;
}

void game::Exit()
{
	ObjectPool::GetInstance()->Reset();
	GameManager::GetInstance()->ResetAsteroidAmount();
	ObjectPool::GetInstance()->Clean();
	CollisionHandler::GetInstance()->Clean();
	ObjectHandler::GetInstance()->Clean();

	_deathAudio.Play();

	_score = 0;
	_spawned = false;
	_enemiesToSpawn = 3;

	_player->Clean();
	_alien->Clean();
}

void game::Clean()
{
	
}

void game::UpdateText()
{
	if (_score > 999)
		scoreText = std::to_string(_score);
	else if (_score < 1000 && _score > 99)
		scoreText = "0" + std::to_string(_score);
	else if (_score < 100 && _score > 9)
		scoreText = "00" + std::to_string(_score);
	else
		scoreText = "000" + std::to_string(_score);

	// Clean up text
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(DisplayManager::renderer, textSurface);
}
