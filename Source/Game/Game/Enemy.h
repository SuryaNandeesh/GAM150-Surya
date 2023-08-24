#pragma once
#include "Framework/Actor.h"
namespace kiko
{
	class Enemy : public kiko::Actor {

	public:
		CLASS_DECLARATION(Enemy)


		//Enemy(float health, float speed, float turnRate, const kiko::Transform& transform, float firerate, std::string tag) :
		//	Actor{ transform },
		//	m_speed{ speed },
		//	m_turnRate{ turnRate }
		//{
		//	m_firerate = firerate;
		//	m_firetimer = m_firerate;
		//}

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	private:

		float m_speed = 0;
		float m_turnRate = 0;

		float m_firerate = 0;
		float m_firetimer = 0;

	};


}
