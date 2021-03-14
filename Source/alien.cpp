#include "alien.h"

alien::alien(vector2* target)
{
	_target = target;
	_pos = vector2(0, 0);
	CollisionHandler::GetInstance()->AddCollider(*this);

	_emitter = new FollowingParticleEmitter(50, &_pos, { 200, 100, 50, 255 }, 0.0f, 50.0f, DisplayManager::screenSize);
	ObjectHandler::GetInstance()->AddEmitter(_emitter);

	_alienMesh = ResourcePool::GetInstance()->GetAlienMesh();
}

void alien::OnEnable()
{
}

void alien::OnDisable()
{
}

void alien::Update()
{
	if (!_active)
		return;

	_vel = (*_target - _pos);
	_rot = _vel.Normalize();
	_vel *= _speed;
	_pos += _vel * Time::deltaTime;

	_pos = WindowDimensions::WrapCoordinates(_pos);

	_timer += Time::deltaTime;

	if (_timer > _shootTimer)
		Shot();
}

void alien::Render(SDL_Renderer* renderer)
{
	if (!_active)
		return;

	_alienMesh.DrawModel(renderer, 0, _pos);
}

void alien::Clean()
{
	delete this;
}

void alien::OnCollide(GameObject& obj)
{
	if (obj.GetLayer() == 5) 
	{
		_deathAudio.Play();
		SetActive(false);
		GameManager::GetInstance()->AddScore(5);
		_emitter->Emitt();
	}
}

vector2 alien::GetPos()
{
	return _pos;
}

float alien::GetRadius()
{
	return _radius;
}

int alien::GetLayer()
{
	return _layer;
}

void alien::SetActive(bool active)
{
	if (active && !_active)
		OnEnable();

	if (!active && _active)
		OnDisable();

	_active = active;
}

bool alien::IsActive()
{
	return _active;
}

void alien::SetPos(vector2 pos)
{
	_pos = pos;
}

vector2 alien::GetVel()
{
	return _vel;
}

void alien::SetVel(vector2 vel)
{
	_vel = vel;
}

void alien::Shot()
{
	GameObject* obj = ObjectPool::GetInstance()->GetAlienBullet();

	if (obj == nullptr)
		return;

	ObjectHandler::GetInstance()->Add(obj);

	obj->SetPos(_pos);
	obj->SetVel(_rot);
	obj->SetActive(true);

	_timer = 0;

	_fireAudio.Play();
}
