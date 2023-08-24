#pragma once
#include "Framework/Singleton.h"
#include "Core/Math/Vector3.h"
#include "box2d/include/box2d/b2_world.h"
#include <memory>
#include "Core/Vector2.h"
#include "ContactListener.h"
namespace kiko
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);

		void DestroyBody(b2Body* body);

		//void SetCollisionBox(b2Body* body, const CollisionData& data, class Actor);
		//void SetCollisionBoxStatic(b2Body* body, const CollisionData& data, class Actor);

		vec2 WorldToScreen(const vec2& world) { return world * m_pixelsPerUnit; }
		vec2 ScreenToWorld(const vec2& screen) { return screen * (1.0f / m_pixelsPerUnit); }

		friend class Singleton;

	private:
		PhysicsSystem() = default;

	private:
		float m_pixelsPerUnit = 48.0f;

		std::unique_ptr<b2World> m_world;
		std::unique_ptr<ContactListener> m_contactListener;
	};
}