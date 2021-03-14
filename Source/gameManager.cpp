#include "gameManager.h"

GameManager* GameManager::instance = 0;

GameManager* GameManager::GetInstance()
{
	if (instance == 0)
		instance = new GameManager();

	return instance;
}

int GameManager::GetScore()
{
	return _score;
}

void GameManager::AddScore(int score)
{
	_score += score;
}

void GameManager::Reset()
{
	_gameOver = false;
	_score = 0;
	_asteroids = 0;
}

int GameManager::GetAsteroidAmount()
{
	return _asteroids;
}

void GameManager::AddToAsteroidAmount()
{
	_asteroids++;
}

void GameManager::SubtractToAsteroidAmount()
{
	_asteroids--;
}

void GameManager::ResetAsteroidAmount()
{
	_asteroids = 0;
}

bool GameManager::IsGameOver()
{
	return _gameOver;
}

void GameManager::SetGameOver(bool gameOver)
{
	_gameOver = gameOver;
	_asteroids = 0;
}

void GameManager::Save(std::string& name)
{
	std::pair<std::string, int> loadFile = Load();

	if (loadFile.second > _score)
		return;

	std::ofstream outfile("save.dat");
	outfile << "n" << name << std::endl;
	outfile << "s" << _score << std::endl;

	outfile.close();
}

std::pair<std::string, int> GameManager::Load()
{
	std::ifstream infile("save.dat");
	std::pair<std::string, int> out;

	if (!infile.is_open()) 
	{
		out.first = "Kenny";
		out.second = 100;
		return out;
	}

	while(!infile.eof())
	{
		char line[128];
		infile.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		// Get name
		if (line[0] == 'n') 
		{
			s >> junk >> out.first;
		}

		// Get score
		if (line[0] == 's') 
		{
			s >> junk >> out.second;
		}
	}

	return out;
}