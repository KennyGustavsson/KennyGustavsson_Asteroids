#include "asteroid.h"

asteroid::asteroid(float radius, int size)
{
	_size = size;
	_radius = radius;

	_emitter = new FollowingParticleEmitter(50, &_pos, {255, 20, 20, 255}, 0.0f, 20.0f, DisplayManager::screenSize);
	ObjectHandler::GetInstance()->AddEmitter(_emitter);

	if (size == 0) 
	{
		_asteroidMesh = ResourcePool::GetInstance()->GetAsteroidBigMesh();
	}
	else if(size == 1) 
	{
		_asteroidMesh = ResourcePool::GetInstance()->GetAsteroidMediumMesh();
	}
	else if(size == 2)
	{
		_asteroidMesh = ResourcePool::GetInstance()->GetAsteroidSmallMesh();
	}

	_theta = rand() / (float)RAND_MAX * 360;
	_asteroidMesh.Scale(_radius * 1.4f);
}

asteroid::~asteroid()
{
	if (_emitter != nullptr)
		delete _emitter;
}

void asteroid::OnEnable()
{
	_velocity.x = rand() / (float)RAND_MAX - 0.5f;
	_velocity.y = rand() / (float)RAND_MAX - 0.5f;

	float speed = (rand() / (float)RAND_MAX) * _randomSpeedMultiplyer;
	_velocity.x *= speed;
	_velocity.y *= speed;

	CollisionHandler::GetInstance()->AddCollider(*this);
	GameManager::GetInstance()->AddToAsteroidAmount();
}

void asteroid::OnDisable()
{
	GameManager::GetInstance()->SubtractToAsteroidAmount();
}

void asteroid::Update()
{
	if (!_active)
		return;

	if (_velocity.x > maxVelocity) 
	{
		if (_velocity.x < 0)
			_velocity.x = maxVelocity;
		else
			_velocity.x = -maxVelocity;
	}

	if (_velocity.y > maxVelocity)
	{
		if (_velocity.y < 0)
			_velocity.y = maxVelocity;
		else
			_velocity.y = -maxVelocity;
	}

	_pos += _velocity * Time::deltaTime * astroidSpeed;
	_pos = WindowDimensions::WrapCoordinates(_pos);
}

void asteroid::Render(SDL_Renderer* renderer)
{
	if (!_active)
		return;

	_asteroidMesh.DrawModel(renderer, _theta, _pos);
}

void asteroid::Clean()
{
	delete this;
}

void asteroid::OnCollide(GameObject& obj)
{
	if (obj.GetLayer() == 5 && IsActive()) 
	{
		_emitter->Emitt();
		_destroyAudio.Play();
		DestroyedByBullet();
	}
}

vector2 asteroid::GetPos()
{
	return _pos;
}

float asteroid::GetRadius()
{
	return _radius;
}

int asteroid::GetLayer()
{
	return _layer;
}

void asteroid::SetActive(bool active)
{
	if (active && !_active)
		OnEnable();

	if (!active && _active)
		OnDisable();

	_active = active;
}

bool asteroid::IsActive()
{
	return _active;
}

void asteroid::SetPos(vector2 pos)
{
	_pos = pos;
}

vector2 asteroid::GetVel()
{
	return _velocity;
}

void asteroid::SetVel(vector2 vel)
{
	_velocity = vel;
}

void asteroid::DestroyedByBullet()
{
	if (!IsActive())
		return;

	CollisionHandler::GetInstance()->RemoveCollider(this);

	ObjectHandler::GetInstance()->SpawnAsteroid(_pos, _size + 1, 3);

	if (_size == 0) 
	{
		GameManager::GetInstance()->AddScore(1);
	}
	else if (_size == 1) 
	{
		GameManager::GetInstance()->AddScore(2);
	}
	else if (_size == 2) 
	{
		GameManager::GetInstance()->AddScore(3);
	}

	SetActive(false);
}