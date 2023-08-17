#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DEC(EnginePhysicsComponent)

		virtual void Update(float dt) override;

		void ApplyForce(const vec2& force) override;

	};
}