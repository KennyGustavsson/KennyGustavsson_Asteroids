#pragma once
#include "player.h"
#include "stateMachine.h"
#include "objectHandler.h"
#include "objectPool.h"
#include "resourcePool.h"
#include <string>
#include "gameManager.h"

#include "asteroid.h"
#include "Bullet.h"
#include "alien.h"
#include "bulletAlien.h"

class game : public State
{
public:
	game();
	~game();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Enter() override;
	virtual void Exit() override;
	void Clean();

private:
	void UpdateText();

	player* _player;
	alien* _alien;

	vector2 _playerPos;

	const int asteroidBigAmount = 10;
	const int asteroidMediumAmount = 30;
	const int asteroidSmallAmount = 60;
	const int bulletAmount = 50;
	const int alienBulletAmount = 8;

	Audio _deathAudio = Audio("Assets/player_death.wav", 20);

	float _timer = 0;
	int _score = 0;
	bool _spawned = false;
	int _enemiesToSpawn = 3;

	float _alienTimer = 0;
	float _alienTime = 10;
	float _alienSpawned = false;

	// Score
	TTF_Font* font = nullptr;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect = { 0, 0, 60, 60 };

	std::string scoreText = "0";
};
