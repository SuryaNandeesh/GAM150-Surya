#pragma once
#include "Framework/Actor.h"
#include "Core/Json.h"
#include "Audio/AudioSystem.h"

namespace kiko
{
	class Projectile : public kiko::Actor 
	{
	public:
		CLASS_DECLARATION(Projectile)

		//	Projectile(float speed, const kiko::Transform& transform, std::string tag, float damage, float lifespan) :
		//	Actor{ transform },
		//	m_speed{ speed },
		//	m_damage{ damage }
		//{
		//	kiko::g_audioSystem.Play("laser");
		//};

		void Update(float dt) override;
		void OnCollision(Actor* actor) override;

	private:
		float speed = 0;
		float damage = 0;
	};
}

