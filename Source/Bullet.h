#pragma once
#include "gameObject.h"
#include "WindowWrapper.h"
#include "objectHandler.h"
#include "collisionHandler.h"
#include "objectPool.h"
#include "time.h"

class Bullet : public GameObject
{
public:
	Bullet();

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
	vector2 _pos = vector2(0, 0);
	vector2 _vel = vector2(0, 0);

	const float bulletSpeed = 300;
	float _radius = 4.0f;

	bool _active = false;
	int _layer = 5;

	float _timer = 0;
	float _lifeTime = 5;

	SDL_Color _color = { 0, 255, 0, 255 };
};

