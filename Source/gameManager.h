#pragma once
#include <string>
#include <iostream>
#include <fstream>  
#include <strstream>

class GameManager
{
public:
	static GameManager* GetInstance();

	int GetScore();
	void AddScore(int score);
	void Reset();

	int GetAsteroidAmount();
	void AddToAsteroidAmount();
	void SubtractToAsteroidAmount();
	void ResetAsteroidAmount();

	bool IsGameOver();
	void SetGameOver(bool gameOver);

	void Save(std::string& name);
	std::pair<std::string, int> Load();

private:
	GameManager(){}
	static GameManager* instance;

	int _score = 0;
	int _asteroids = 0;
	bool _gameOver = false;
};

