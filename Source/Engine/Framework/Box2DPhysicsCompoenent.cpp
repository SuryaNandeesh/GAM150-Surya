#include "Box2DPhysicsCompoenent.h"

namespace kiko
{
	CLASS_DEFINITION(Box2DPhysicsComponent)

	bool Box2DPhysicsComponent::Initialize()
	{
		return false;
	}

	void Box2DPhysicsComponent::OnDestroy()
	{
	}

	void Box2DPhysicsComponent::Update(float dt)
	{
	}

	void Box2DPhysicsComponent::ApplyForce(const vec2& force)
	{
		//m_body->ApplyForceToCenter(VEC2_TO_B2VEC2(force), true);
	}

	//void Box2DPhysicsComponent::ApplyTorque(float torque)
	//{
		//m_body->ApplyTorque(torque, true);
	//}

	void Box2DPhysicsComponent::SetVelocity(const vec2& velocity)
	{
		//m_body->SetLinearVelocity(VEC2_TO_B2VEC2(velocity));
	}

	void Box2DPhysicsComponent::Read(const json_t& value)
	{
		//READ_NAME_DATA(value, "damping", data.damping);
		//READ_NAME_DATA(value, "angularDamping", data.angularDamping);
		//READ_NAME_DATA(value, "gravityScale", data.gravityScale);
		//READ_NAME_DATA(value, "constrainAngle", data.constrainAngle);
		//READ_NAME_DATA(value, "isDynamic", data.isDynamic);
	}
}


