#pragma once
#include "SDL.h"
#include "vector2.h"

class GameObject {
public:
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Clean() = 0;
	virtual void OnCollide(GameObject& obj) = 0;

	virtual vector2 GetPos() = 0;
	virtual float GetRadius() = 0;
	virtual int GetLayer() = 0;
	virtual void SetActive(bool active) = 0;
	virtual bool IsActive() = 0;
	virtual void SetPos(vector2 pos) = 0;
	virtual vector2 GetVel() = 0;
	virtual void SetVel(vector2 vel) = 0;
};