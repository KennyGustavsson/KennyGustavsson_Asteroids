#pragma once
#include "gameObject.h"
#include "WindowWrapper.h"
#include "collisionHandler.h"
#include "objectHandler.h"
#include "objectPool.h"
#include "time.h"
#include "gameManager.h"
#include "particleEmitter.h"
#include "audio.h"
#include "mesh.h"
#include "resourcePool.h"

class game;

class asteroid : public GameObject
{
public:
	asteroid(float radius, int size);
	~asteroid();

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

private:
	void DestroyedByBullet();
	Audio _destroyAudio = Audio("Assets/asteroid_destroy.wav", 20);
	FollowingParticleEmitter* _emitter;
	Mesh _asteroidMesh;

	float _radius;
	int _size = 0;
	float _theta = 0;

	bool _active = true;
	const int _layer = 10;

	vector2 _pos = vector2(0, 0);
	vector2 _velocity = vector2(0, 0);

	float maxVelocity = 0.5f;
	float _randomSpeedMultiplyer = 2;

	const float astroidSpeed = 100;
};

