#include "Enemy.h"
#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include <memory>
#include "Player.h"

namespace kiko
{
    CLASS_DEFINITION(Enemy)

    bool Enemy::Initialize()
    {
        Actor::Initialize();
        //cache off
        m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

        return true;
    }

    void Enemy::Update(float dt) {

        Actor::Update(dt);

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
        Player* player = m_scene->GetActor<Player>();

        if (player)
        {
            vec2 direction = player->transform.position - transform.position;
            //turns towards player
            m_physicsComponent->ApplyForce(direction.Normalized() * m_speed);
            float turnAngle = vec2::SignedAngle(forward, direction.Normalized());
            m_physicsComponent->ApplyTorque(turnAngle);

            //check if player is in front
            if (fabs(turnAngle) < DegToRad(30.0f))
            {
                //I CAN SEE YOU
            }
        }


        //physics engine
        m_physicsComponent->ApplyForce(forward * m_speed);

        //jump
        bool onGround = (groundCount > 0);


        if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
        {
            vec2 up = vec2{ 0, -1 };
            m_physicsComponent->SetVelocity(up * jump);
        }

    }

    void Enemy::OnCollisionEnter(Actor* other)
    {
        if (other->tag == "Player")
        {
            m_destroyed = true;
            //EVENT_DISPATCH("OnPlayerDead", 0);
        }

        if (other->tag == "Ground") groundCount++;
    }
    void Enemy::OnCollisionExit(Actor* other)
    {
        if (other->tag == "Ground") groundCount--;
    }


    void Enemy::Read(const json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, m_speed);
    }
}