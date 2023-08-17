#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public kiko::Actor {

public:

	Player(float health, float speed, float turnRate, const kiko::Transform& transform, std::string tag) :
		Actor{ transform, tag, health},
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}
	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	
	float m_speed = 0;
	float m_turnRate = 0;

	kiko::PhysicsComponent* m_physicsComponent = nullptr;
};

