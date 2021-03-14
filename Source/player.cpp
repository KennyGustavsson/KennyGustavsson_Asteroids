#include "player.h"

player::player(vector2& pos, vector2* screenSize)
{
	_pos = pos;

	_playerMesh.t.push_back(Triangle(vector2(-5, 0), vector2(15, 0), vector2(-10, 10)));
	_playerMesh.t.push_back(Triangle(vector2(-5, 0), vector2(-10, -10), vector2(15, 0)));

	OnEnable();
}

player::player(float x, float y, vector2* screenSize)
{
	_pos.x = x;
	_pos.y = y;

	_playerMesh.t.push_back(Triangle(vector2(-5, 0), vector2(15, 0), vector2(-10, 10)));
	_playerMesh.t.push_back(Triangle(vector2(-5, 0), vector2(-10, -10), vector2(15, 0)));

	OnEnable();
}

player::~player()
{
	
}

void player::OnEnable()
{
	_killable = false;
	_emitter = new FollowingParticleEmitter(300, &_pos, &_rot, DisplayManager::screenSize);
}

void player::OnDisable()
{

}

void player::Update()
{
	if (!_active || _currentKeyStates == nullptr)
		return;

	_timer += Time::deltaTime;

	// Thurster forward
	if (_currentKeyStates[SDL_SCANCODE_W] || _currentKeyStates[SDL_SCANCODE_UP])
	{
		_velocity += _rot * _acceleration * Time::deltaTime;

		_emitter->Emitt();
	}

	_velocity.x = Clamp(_velocity.x, -_maxSpeed, _maxSpeed);
	_velocity.y = Clamp(_velocity.y, -_maxSpeed, _maxSpeed);

	_pos += _velocity * Time::deltaTime;
	_pos = WindowDimensions::WrapCoordinates(_pos);

	// Rotation
	if (_currentKeyStates[SDL_SCANCODE_A] || _currentKeyStates[SDL_SCANCODE_LEFT]) {
		_theta -= _rotSpeed * Time::deltaTime;
	}

	if (_currentKeyStates[SDL_SCANCODE_D] || _currentKeyStates[SDL_SCANCODE_RIGHT]) {
		_theta += _rotSpeed * Time::deltaTime;
	}

	_rot.x = cos(_theta);
	_rot.y = sin(_theta);

	if(_emitter != nullptr)
		_emitter->Update();

	if (_currentKeyStates[SDL_SCANCODE_SPACE] && _timer > _shootDelay) 
	{
		GameObject* obj = ObjectPool::GetInstance()->GetBullet();

		ObjectHandler::GetInstance()->Add(obj);

		obj->SetPos(_pos);
		obj->SetVel(_rot);
		obj->SetActive(true);

		_timer = 0;
		_killable = true;

		_fireAudio.Play();
	}
}

void player::Render(SDL_Renderer* renderer)
{
	if (!renderer || !_active)
		return;

	if (_emitter != nullptr)
		_emitter->Render(renderer);

	_playerMesh.DrawModel(renderer, _theta, _pos);

	// Shows collider
	WindowDimensions::DrawWrapedCircle(renderer, _pos, _collisionRadius, 20, { 255, 255, 255, 255 });
}

void player::Clean()
{
	delete _emitter;
	delete this;
}

void player::OnCollide(GameObject& obj)
{
	if (obj.GetLayer() == 10 || obj.GetLayer() == 6) 
	{
		if (_killable)
		{
			GameManager::GetInstance()->SetGameOver(true);
		}
	}
}

vector2 player::GetPos()
{
	return _pos;
}

float player::GetRadius()
{
	return _collisionRadius;
}

int player::GetLayer()
{
	return _layer;
}

void player::SetActive(bool active)
{
	if (active && !_active)
		OnEnable();

	if (!active && _active)
		OnDisable();

	_active = active;
}

bool player::IsActive()
{
	return _active;
}

void player::SetPos(vector2 pos)
{
	_pos = pos;
}

vector2 player::GetVel()
{
	return _velocity;
}

void player::SetVel(vector2 vel)
{
	_velocity = vel;
}

void player::SetKillable(bool killable)
{
	_killable = killable;
}
