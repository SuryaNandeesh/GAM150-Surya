#pragma once
#include "Component.h"

namespace kiko
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision);
		// Inherited via Component
		virtual void Update(float dt) override;

	public:
		float m_radius = 0;

	};
}