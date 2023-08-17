#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Projectile : public kiko::Actor {

public:

	Projectile(float speed, const kiko::Transform& transform, std::string tag, float damage, float lifespan) :
		Actor{ transform, tag, -1.0f, lifespan },
		m_speed{ speed },
		m_damage{damage}
	{ 
		kiko::g_audioSystem.Play("laser");
	};

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:

	float m_speed = 0;
	float m_damage = 0;
};

