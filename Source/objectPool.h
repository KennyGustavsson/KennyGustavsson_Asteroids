#pragma once
#include <list>
#include <vector>
#include "gameObject.h"
#include "displayManager.h"

class ObjectPool
{
public:
	static ObjectPool* GetInstance();

	GameObject* GetAsteroidBig();
	GameObject* GetAsteroidMedium();
	GameObject* GetAsteroidSmall();
	GameObject* GetAlienBullet();
	GameObject* GetBullet();

	void AddAsteroidBig(GameObject* obj);
	void AddAsteroidMedium(GameObject* obj);
	void AddAsteroidSmall(GameObject* obj);
	void AddBullet(GameObject* obj);
	void AddAlienBullet(GameObject* obj);

	void Clean();
	void Reset();

private:
	std::list<GameObject*> _asteroidBig = {};
	std::list<GameObject*> _asteroidMedium = {};
	std::list<GameObject*> _asteroidSmall = {};
	std::list<GameObject*> _alienBullet = {};
	std::list<GameObject*> _bullet = {};

	std::vector<GameObject*> _allBigAsteroids = {};
	std::vector<GameObject*> _allMediumAsteroids = {};
	std::vector<GameObject*> _allSmallAsteroids = {};

	ObjectPool() {}

	static ObjectPool* instance;
	~ObjectPool();
};