#include "PhysicsSystem.h"

namespace kiko
{
	bool PhysicsSystem::Initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);

		m_contactListener = std::make_unique<ContactListener>();
		m_world->SetContactListener(m_contactListener.get());

		return true;
	}
	void PhysicsSystem::Update(float dt)
	{
		//
	}

	void PhysicsSystem::DestroyBody(b2Body* body)
	{
		m_world->DestroyBody(body);
	}

	/*void PhysicsSystem::SetCollisionBox(b2Body* body, const CollisionData& data, Actor)
	{
		b2PolygonShape shape;
		Vector2 worldSize = ScreenToWorld(data.size * 0.5f);
		shape.SetAsBox(worldSize.x, worldSize.y);
		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.isTrigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);
		body->CreateFixture(&fixtureDef);
	}*/

	/*void PhysicsSystem::SetCollisionBoxStatic(b2Body* body, const CollisionData& data, Actor)
	{
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);
	}*/
	
}
