#pragma once
#include "gameObject.h"
#include "time.h"
#include "WindowWrapper.h"
#include "collisionHandler.h"
#include "audio.h"
#include "objectPool.h"
#include "objectHandler.h"
#include "gameManager.h"
#include "mesh.h"
#include "resourcePool.h"

class alien : public GameObject
{
public:
	alien(vector2* target);

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
	void Shot();

	Audio _deathAudio = Audio("Assets/player_death.wav", 20);
	Audio _fireAudio = Audio("Assets/player_fire.wav", 20);

	Mesh _alienMesh;

	FollowingParticleEmitter* _emitter;

	vector2* _target;

	vector2 _pos;
	vector2 _rot;
	vector2 _vel;

	float _speed = 5;
	float _radius = 10;

	bool _active = false;
	int _layer = 6;

	float _shootTimer = 3;
	float _timer = 0;
};
