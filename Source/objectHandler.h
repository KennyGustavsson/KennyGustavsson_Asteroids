#pragma once
#include "gameObject.h"
#include <vector>
#include "displayManager.h"
#include "particleEmitter.h"
#include "objectPool.h"

class ObjectHandler
{
public:
	static ObjectHandler* GetInstance();
	void Add(GameObject* obj);
	void Remove(GameObject* obj);

	void AddEmitter(FollowingParticleEmitter* obj);

	void SpawnAsteroid(int size, int amount);
	void SpawnAsteroid(vector2 pos, int size, int amount);
	int GetActiveAsteroidsAmount();

	void ResetAsteroids();

	void Update();
	void Render();
	void Clean();

private:
	std::vector<GameObject*> _objects = {};
	std::vector<FollowingParticleEmitter*> _emitter = {};

	std::vector<GameObject*> _activeAsteroids = {};

	static ObjectHandler* instance;
	ObjectHandler() {};
	~ObjectHandler();
};

