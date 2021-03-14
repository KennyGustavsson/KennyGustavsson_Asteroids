#pragma once
#include "gameObject.h"
#include "time.h"
#include <iostream>
#include "particleEmitter.h"
#include "WindowWrapper.h"
#include "collisionHandler.h"
#include "objectPool.h"
#include "objectHandler.h"
#include "gameManager.h"
#include "audio.h"
#include "mesh.h"

class player : public GameObject
{
public:
	player(vector2& pos, vector2* screenSize);
	player(float x, float y, vector2* screenSize);
	~player();

	// Inherited via GameObject
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void Update() override;
	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Clean() override;
	virtual void OnCollide(GameObject& obj) override;
	virtual vector2 GetPos() override;
	virtual float GetRadius() override;
	virtual int GetLayer() override;
	virtual void SetActive(bool active) override;
	virtual bool IsActive() override;
	virtual void SetPos(vector2 pos) override;
	virtual vector2 GetVel() override;
	virtual void SetVel(vector2 vel) override;

	void SetKillable(bool killable);

private:
	Audio _fireAudio = Audio("Assets/player_fire.wav", 20);
	FollowingParticleEmitter* _emitter;
	Mesh _playerMesh;

	float _collisionRadius = 10.0f;
	int _layer = 0;
	bool _active = true;

	vector2 _pos = vector2(0, 0);
	vector2 _rot = vector2(0, -1);
	float _theta = 0;

	float _maxSpeed = 200.0f;
	float _rotSpeed = 3.0f;

	float _acceleration = 50;
	vector2 _velocity = vector2(0, 0);

	float _shootDelay = 0.5f;
	float _timer = 0;
	bool _killable = false;

	const Uint8* _currentKeyStates = SDL_GetKeyboardState(NULL);

	float Clamp(float n, float lower, float upper) 
	{
		return std::max(lower, std::min(n, upper));
	}
};
