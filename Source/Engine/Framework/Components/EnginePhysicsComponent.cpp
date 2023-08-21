#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(EnginePhysicsComponent) 
		
	void kiko::EnginePhysicsComponent::Update(float dt)
	{

		m_owner->m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}
	void kiko::EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}

	void EnginePhysicsComponent::Read(const json_t& value)
	{
		//
	}
}

