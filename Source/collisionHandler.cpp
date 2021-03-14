#include "collisionHandler.h"

CollisionHandler* CollisionHandler::instance = 0;

CollisionHandler* CollisionHandler::GetInstance()
{
	if (instance == 0)
		instance = new CollisionHandler();

	return instance;
}

void CollisionHandler::Update()
{
	// Handle Collisions
	for (int i = 0; i < _colliders.size(); i++) {
		for (int j = 0; j < _colliders.size(); j++) {
			if (i == j || _colliders[i] == nullptr || _colliders[j] == nullptr)
				continue;

			if (!_colliders[i]->IsActive() || !_colliders[j]->IsActive())
				continue;

			vector2 aPos = _colliders[i]->GetPos();
			vector2 bPos = _colliders[j]->GetPos();

			float aRad = _colliders[i]->GetRadius();
			float bRad = _colliders[j]->GetRadius();

			if (DoCirclesOverlap(aPos, aRad, bPos, bRad))
			{
				_colliders[i]->OnCollide(*_colliders[j]);
				_colliders[j]->OnCollide(*_colliders[i]);

				// Asteroid vs asteroid collision
				if (_colliders[i]->GetLayer() == 10 && _colliders[j]->GetLayer() == 10) 
				{
					_collidingPairs.push_back({ _colliders[i], _colliders[j] });

					float distance = sqrtf((aPos.x - bPos.x) * (aPos.x - bPos.x) + (aPos.y - bPos.y) * (aPos.y - bPos.y));
					float overlap = 0.5f * (distance - aRad - bRad);

					_colliders[i]->SetPos(aPos - (aPos - bPos) * overlap / distance);
					_colliders[j]->SetPos(bPos + (aPos - bPos) * overlap / distance);
				}
			}
		}
	}

	HandleDynamicCollision();
}

void CollisionHandler::HandleDynamicCollision()
{
	for (size_t i = 0; i < _collidingPairs.size(); i++)
	{
		GameObject* b1 = _collidingPairs[i].first;
		GameObject* b2 = _collidingPairs[i].second;

		vector2 posA = b1->GetPos();
		vector2 posB = b2->GetPos();

		vector2 vecA = b1->GetVel();
		vector2 vecB = b2->GetVel();

		float radA = b1->GetRadius();
		float radB = b2->GetRadius();

		float distance = sqrtf((posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y));
		vector2 normal = (posB - posA) / distance;
		vector2 tangent = vector2(-normal.y, normal.x);

		float dotTanA = vecA.x * tangent.x + vecA.y * tangent.y;
		float dotTanB = vecB.x * tangent.x + vecB.y * tangent.y;

		float dotNormA = vecA.x * normal.x + vecA.y * normal.y;
		float dotNormB = vecB.x * normal.x + vecB.y * normal.y;

		// Conservation of momentum
		float m1 = (dotNormA * (1.5f * radA - 1.2f * radB) + 2.0f * (1.2f * radB) * dotNormB) / (1.5f * radA + 1.2f * radB);
		float m2 = (dotNormB * (1.2f * radA - 1.5f * radB) + 2.0f * (1.5f * radB) * dotNormA) / (1.5f * radA + 1.2f * radB);

		// Update velocities
		vector2 newAVel;
		newAVel.x = tangent.x * dotTanA + normal.x * m1;
		newAVel.y = tangent.y * dotTanA + normal.y * m1;

		vector2 newBVel;
		newBVel.x = tangent.x * dotTanB + normal.x * m2;
		newBVel.y = tangent.y * dotTanB + normal.y * m2;

		b1->SetVel(newAVel);
		b2->SetVel(newBVel);
	}

	_collidingPairs.clear();
}

void CollisionHandler::AddCollider(GameObject& obj)
{
	_colliders.push_back(&obj);
}

void CollisionHandler::RemoveCollider(GameObject* obj)
{
	std::pair<bool, int> result = findInVector(_colliders, obj);

	if (result.first) {
		_colliders.erase(_colliders.begin() + result.second);
	}
}

void CollisionHandler::Clean()
{
	_collidingPairs.clear();
	_colliders.clear();
}

template<typename T>
inline std::pair<bool, int> CollisionHandler::findInVector(const std::vector<T>& vecOfElements, const T& element)
{
	std::pair<bool, int > result;
	auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
	if (it != vecOfElements.end())
	{
		result.second = distance(vecOfElements.begin(), it);
		result.first = true;
	}
	else
	{
		result.first = false;
		result.second = -1;
	}
	return result;
}

bool CollisionHandler::DoCirclesOverlap(vector2 p1, float r1, vector2 p2, float r2)
{
	return fabs((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) <= (r1 + r2) * (r1 + r2);
}