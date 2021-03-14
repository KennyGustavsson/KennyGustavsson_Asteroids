#pragma once
#include "gameObject.h"
#include <vector>
#include <iostream>

static class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();
	void Update();
	void AddCollider(GameObject& obj);
	void RemoveCollider(GameObject* obj);
	void Clean();

private:
	std::vector<GameObject*> _colliders = std::vector<GameObject*>();
	std::vector<std::pair<GameObject*, GameObject*>> _collidingPairs = std::vector<std::pair<GameObject*, GameObject*>>();
 
	void HandleDynamicCollision();

	static CollisionHandler* instance;
	CollisionHandler() {};

	template <typename T>
	std::pair<bool, int > findInVector(const std::vector<T>& vecOfElements, const T& element);
	bool DoCirclesOverlap(vector2 p1, float r1, vector2 p2, float r2);
};