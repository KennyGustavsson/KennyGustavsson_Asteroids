#include "objectHandler.h"

ObjectHandler* ObjectHandler::instance = 0;

ObjectHandler* ObjectHandler::GetInstance()
{
	if (instance == 0)
		instance = new ObjectHandler;

	return instance;
}

void ObjectHandler::Add(GameObject* obj)
{
	_objects.push_back(obj);
}

void ObjectHandler::AddEmitter(FollowingParticleEmitter* obj)
{
	_emitter.push_back(obj);
}

void ObjectHandler::SpawnAsteroid(int size, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (size == 0)
		{
			GameObject* obj = ObjectPool::GetInstance()->GetAsteroidBig();
			obj->SetPos(vector2(rand() % 400, rand() % 400));
			obj->SetActive(true);

			_activeAsteroids.push_back(obj);
		}

		if (size == 1)
		{
			GameObject* obj = ObjectPool::GetInstance()->GetAsteroidMedium();
			obj->SetPos(vector2(rand() % 400, rand() % 400));
			obj->SetActive(true);

			_activeAsteroids.push_back(obj);
		}

		if (size == 2)
		{
			GameObject* obj = ObjectPool::GetInstance()->GetAsteroidSmall();
			obj->SetPos(vector2(rand() % 400, rand() % 400));
			obj->SetActive(true);

			_activeAsteroids.push_back(obj);
		}
	}
}

void ObjectHandler::SpawnAsteroid(vector2 pos, int size, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (size == 0)
		{
			GameObject* obj = ObjectPool::GetInstance()->GetAsteroidBig();
			obj->SetPos(vector2(pos.x + rand() % 20, pos.y + rand() % 20));
			obj->SetActive(true);

			_activeAsteroids.push_back(obj);
		}

		if (size == 1)
		{
			GameObject* obj = ObjectPool::GetInstance()->GetAsteroidMedium();
			obj->SetPos(vector2(pos.x + rand() % 20, pos.y + rand() % 20));
			obj->SetActive(true);

			_activeAsteroids.push_back(obj);
		}

		if (size == 2)
		{
			GameObject* obj = ObjectPool::GetInstance()->GetAsteroidSmall();
			obj->SetPos(vector2(pos.x + rand() % 20, pos.y + rand() % 20));
			obj->SetActive(true);

			_activeAsteroids.push_back(obj);
		}
	}
}

int ObjectHandler::GetActiveAsteroidsAmount()
{
	int counter = 0;

	for (int i = 0; i < _activeAsteroids.size(); i++)
	{
		if (_activeAsteroids[i]->IsActive())
			counter++;
	}

	return counter;
}

void ObjectHandler::ResetAsteroids()
{
	for (int i = 0; i < _activeAsteroids.size(); i++)
	{
		_activeAsteroids[i]->SetActive(false);
	}

	_activeAsteroids.clear();

	ObjectPool::GetInstance()->Reset();
}

void ObjectHandler::Update()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->IsActive())
			_objects[i]->Update();
	}

	for (int i = 0; i < _emitter.size(); i++) 
	{
		if(_emitter[i] != nullptr)
			_emitter[i]->Update();
	}

	for (int i = 0; i < _activeAsteroids.size(); i++)
	{
		_activeAsteroids[i]->Update();
	}
}

void ObjectHandler::Render()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Render(DisplayManager::renderer);
	}

	for (int i = 0; i < _emitter.size(); i++)
	{
		_emitter[i]->Render(DisplayManager::renderer);
	}

	for (int i = 0; i < _activeAsteroids.size(); i++)
	{
		_activeAsteroids[i]->Render(DisplayManager::renderer);
	}
}

void ObjectHandler::Clean()
{
	_objects.clear();
	_emitter.clear();
	_activeAsteroids.clear();
}

ObjectHandler::~ObjectHandler()
{
	Clean();
	delete instance;
}