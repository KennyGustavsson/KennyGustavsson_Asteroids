#include "objectPool.h"

ObjectPool* ObjectPool::instance = 0;

ObjectPool* ObjectPool::GetInstance()
{
	if (instance == 0)
		instance = new ObjectPool;

	return instance;
}

GameObject* ObjectPool::GetAsteroidBig()
{
	if (_asteroidBig.empty())
	{
		return nullptr;
	}
	else
	{
		GameObject* obj = _asteroidBig.front();
		_asteroidBig.pop_front();
		return obj;
	}
}

GameObject* ObjectPool::GetAsteroidMedium()
{
	if (_asteroidMedium.empty())
	{
		return nullptr;
	}
	else
	{
		GameObject* obj = _asteroidMedium.front();
		_asteroidMedium.pop_front();
		return obj;
	}
}

GameObject* ObjectPool::GetAsteroidSmall()
{
	if (_asteroidSmall.empty())
	{
		return nullptr;
	}
	else
	{
		GameObject* obj = _asteroidSmall.front();
		_asteroidSmall.pop_front();
		return obj;
	}
}

GameObject* ObjectPool::GetAlienBullet()
{
	if (_alienBullet.empty())
	{
		return nullptr;
	}
	else
	{
		GameObject* obj = _alienBullet.front();
		_alienBullet.pop_front();
		_alienBullet.push_back(obj);
		return obj;
	}
}

GameObject* ObjectPool::GetBullet()
{
	if (_bullet.empty())
	{
		return nullptr;
	}
	else
	{
		GameObject* obj = _bullet.front();
		_bullet.pop_front();
		_bullet.push_back(obj);
		return obj;
	}
}

void ObjectPool::AddAsteroidBig(GameObject* obj)
{
	obj->SetActive(false);
	_asteroidBig.push_back(obj);
	_allBigAsteroids.push_back(obj);
}

void ObjectPool::AddAsteroidMedium(GameObject* obj)
{
	obj->SetActive(false);
	_asteroidMedium.push_back(obj);
	_allMediumAsteroids.push_back(obj);
}

void ObjectPool::AddAsteroidSmall(GameObject* obj)
{
	obj->SetActive(false);
	_asteroidSmall.push_back(obj);
	_allSmallAsteroids.push_back(obj);
}

void ObjectPool::AddBullet(GameObject* obj)
{
	obj->SetActive(false);
	_bullet.push_back(obj);
}

void ObjectPool::AddAlienBullet(GameObject* obj)
{
	obj->SetActive(false);
	_alienBullet.push_back(obj);
}

void ObjectPool::Clean()
{
	for (int i = 0; i < _allBigAsteroids.size(); i++)
	{
		if (_allBigAsteroids[i] != nullptr) 
		{
			_allBigAsteroids[i]->Clean();
		}
	}

	for (int i = 0; i < _allMediumAsteroids.size(); i++)
	{
		if (_allMediumAsteroids[i] != nullptr) 
		{
			_allMediumAsteroids[i]->Clean();
		}
	}

	for (int i = 0; i < _allSmallAsteroids.size(); i++)
	{
		if (_allSmallAsteroids[i] != nullptr) 
		{
			_allSmallAsteroids[i]->Clean();
		}
	}

	while (!_alienBullet.empty())
	{
		GameObject* obj = _alienBullet.front();
		_alienBullet.pop_front();

		if (obj != nullptr)
		{
			obj->Clean();
		}
	}

	while(!_bullet.empty())
	{
		GameObject* obj = _bullet.front();
		_bullet.pop_front();

		if (obj != nullptr)
		{
			obj->Clean();
		}
	}

	_allBigAsteroids.clear();
	_allMediumAsteroids.clear();
	_allSmallAsteroids.clear();
	_bullet.clear();

	_asteroidBig.clear();
	_asteroidMedium.clear();
	_asteroidSmall.clear();
	_alienBullet.clear();
}

void ObjectPool::Reset()
{
	_asteroidBig.clear();
	_asteroidMedium.clear();
	_asteroidSmall.clear();

	for (int i = 0; i < _allBigAsteroids.size(); i++)
	{
		_asteroidBig.push_back(_allBigAsteroids[i]);
		_allBigAsteroids[i]->SetActive(false);
	}

	for (int i = 0; i < _allMediumAsteroids.size(); i++)
	{
		_asteroidMedium.push_back(_allMediumAsteroids[i]);
		_allMediumAsteroids[i]->SetActive(false);
	}

	for (int i = 0; i < _allSmallAsteroids.size(); i++)
	{
		_asteroidSmall.push_back(_allSmallAsteroids[i]);
		_allSmallAsteroids[i]->SetActive(false);
	}

	for (int i = 0; i < _alienBullet.size(); i++)
	{
		GameObject* obj = _alienBullet.front();
		_alienBullet.pop_front();

		if (obj != nullptr)
		{
			obj->SetActive(false);
			_alienBullet.push_back(obj);
		}
	}

	for (int i = 0; i < _bullet.size(); i++)
	{
		GameObject* obj = _bullet.front();
		_bullet.pop_front();

		if (obj != nullptr)
		{
			obj->SetActive(false);
			_bullet.push_back(obj);
		}
	}
}

ObjectPool::~ObjectPool()
{
	Clean();
}
