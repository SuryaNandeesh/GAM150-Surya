#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	

	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		CLASS_DEF(CircleCollisionComponent);
		bool CheckCollision(CollisionComponent* collision) override;
		inline void Update(float dt) override;
	};
}