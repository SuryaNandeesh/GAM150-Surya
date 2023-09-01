#pragma once
#include "Framework/Framework.h"

namespace kiko
{
	class Player : public kiko::Actor {

	public:
		CLASS_DECLARATION(Player)

			//Player(float health, float speed, float turnRate, const kiko::Transform& transform, std::string tag) :
			//	Actor{ transform },
			//	m_speed{ speed },
			//	m_turnRate{ turnRate }
			//{}
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);
		void OnCollisionExit(Actor* other);

	private:

		float m_speed = 10;
		float jump = 0;
		float groundCount = 0;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimationRenderComponent* m_spriteAnimationRenderComponent = nullptr;
	};
}
