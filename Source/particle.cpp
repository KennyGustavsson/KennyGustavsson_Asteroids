#include "particle.h"


Particle::Particle(vector2 pos, vector2 vel, int life, SDL_Color& color, vector2* screenSize) : _pos(pos), _vel(vel)
{
	_endTime = Time::totalElapsedSeconds + life;
	_color = color;
	_screenSize = screenSize;
}

void Particle::Update()
{
	_color.r -= Time::deltaTime;
	_color.g -= Time::deltaTime;
	_color.b -= Time::deltaTime;
	_color.a -= Time::deltaTime;

	_pos += _vel * Time::deltaTime * _baseSpeed;
	_pos = WindowDimensions::WrapCoordinates(_pos);
}

/// <summary>
/// Renders the particle
/// </summary>
/// <param name="renderer"></param>
void Particle::Render(SDL_Renderer* renderer)
{
	if (isDead() || hide)
		return;

	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderDrawPoint(renderer, _pos.x, _pos.y);
}

bool Particle::isDead()
{
	return (Time::totalElapsedSeconds > _endTime);
}

void Particle::SetPos(vector2 pos)
{
	_pos = pos;
}

void Particle::SetVel(vector2 vel)
{
	_vel = vel;
}

void Particle::SetColor(SDL_Color color)
{
	_color = color;
}

void Particle::SetLifeTime(int life)
{
	_endTime = Time::totalElapsedSeconds + life;
}
