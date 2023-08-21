#pragma once
#include "Component.h"

namespace kiko
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision) = 0;
		virtual void Update(float dt) = 0;

	public:
		float m_radius = 0;
	};
}