#pragma once
#include "Component.h"
#include "Core/Vector2.h"

namespace kiko
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void Update(float dt) = 0;
		virtual void ApplyForce(const vec2& force) = 0;
		CLASS_DEFINITION(PhysicsComponent)

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}