#include "Bullet.h"

Bullet::Bullet()
{
	CollisionHandler::GetInstance()->AddCollider(*this);
}

void Bullet::OnEnable()
{
	_timer = 0;
}

void Bullet::OnDisable()
{
	
}

void Bullet::Update()
{
	if (_active)
	{
		_pos += _vel * Time::deltaTime * bulletSpeed;
		_pos = WindowDimensions::WrapCoordinates(_pos);

		if (_timer > _lifeTime)
			SetActive(false);

		_timer += Time::deltaTime;
	}
}

void Bullet::Render(SDL_Renderer* renderer)
{
	if (_active)
	{
		WindowDimensions::DrawWrapedCircle(renderer, _pos, _radius, 512, _color);
	}
}

void Bullet::Clean()
{
	delete this;
}

void Bullet::OnCollide(GameObject& obj)
{
	if (obj.GetLayer() == 10 || obj.GetLayer() == 6) 
	{
		if (_active)
		{
			_active = false;
		}
	}
}

vector2 Bullet::GetPos()
{
	return _pos;
}

float Bullet::GetRadius()
{
	return _radius;
}

int Bullet::GetLayer()
{
	return _layer;
}

void Bullet::SetActive(bool active)
{
	if (active && !_active)
		OnEnable();

	if (!active && _active)
		OnDisable();

	_active = active;
}

bool Bullet::IsActive()
{
	return _active;
}

void Bullet::SetPos(vector2 pos)
{
	_pos = pos;
}

vector2 Bullet::GetVel()
{
	return _vel;
}

void Bullet::SetVel(vector2 vel)
{
	_vel = vel;
}
