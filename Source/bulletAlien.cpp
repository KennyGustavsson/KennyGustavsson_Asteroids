#include "bulletAlien.h"

BulletAlien::BulletAlien()
{
	CollisionHandler::GetInstance()->AddCollider(*this);
}

void BulletAlien::OnEnable()
{
	_timer = 0;
}

void BulletAlien::OnDisable()
{
}

void BulletAlien::Update()
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

void BulletAlien::Render(SDL_Renderer* renderer)
{
	if (_active)
	{
		WindowDimensions::DrawWrapedCircle(renderer, _pos, _radius, 512, color);
	}
}

void BulletAlien::Clean()
{
	delete this;
}

void BulletAlien::OnCollide(GameObject& obj)
{
	if (obj.GetLayer() == 10 && _active)
	{
		_active = false;
	}
}

vector2 BulletAlien::GetPos()
{
	return _pos;
}

float BulletAlien::GetRadius()
{
	return _radius;
}

int BulletAlien::GetLayer()
{
	return _layer;
}

void BulletAlien::SetActive(bool active)
{
	if (active && !_active)
		OnEnable();

	if (!active && _active)
		OnDisable();

	_active = active;
}

bool BulletAlien::IsActive()
{
	return _active;
}

void BulletAlien::SetPos(vector2 pos)
{
	_pos = pos;
}

vector2 BulletAlien::GetVel()
{
	return _vel;
}

void BulletAlien::SetVel(vector2 vel)
{
	_vel = vel;
}
