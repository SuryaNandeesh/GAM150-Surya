#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(CircleCollisionComponent)

	inline void CircleCollisionComponent::Update(float dt) {}

	bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
	{
		float distance = m_owner->m_transform.position.Distance(collision->m_owner->m_transform.position);
		float radius = this->m_radius + collision->m_radius;

		return (distance <= radius);
	}

	void CircleCollisionComponent::Read(const json_t& value)
	{
		//
	}
}