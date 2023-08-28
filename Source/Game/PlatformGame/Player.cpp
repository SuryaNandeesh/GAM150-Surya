#include "Player.h"
#include "PlatformGame.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Renderer/Renderer.h"
#include <memory>
#include <Framework/Components/RenderComponent.h>
#include <Framework/Components/CollisionComponent.h>

namespace kiko
{
    bool Player::Initialize()
    {
        Actor::Initialize();
        //cache off
        m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

        return true;
    }

    void Player::Update(float dt) {

        Actor::Update(dt);

        bool sprint = kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT);

        float direction = 0;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction = -1;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction = 1;

        vec2 forward = vec2{ 1, 0 };

        //physics engine
        m_physicsComponent->ApplyForce(forward * m_speed * direction);

        //jump
        bool onGround = (groundCount > 0);


        if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
        {
            vec2 up = vec2{ 0, -1 };
            m_physicsComponent->SetVelocity(up * jump);
        }

    }

    void Player::OnCollisionEnter(Actor* other)
    {
        if (other->tag == "Enemy")
        {
            m_destroyed = true;
            //EVENT_DISPATCH("OnPlayerDead", 0);
        }

        if (other->tag == "Ground") groundCount++;
    }
    void Player::OnCollisionExit(Actor* other)
    {
        if (other->tag == "Ground") groundCount--;
    }


    void Player::Read(const json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, m_speed);
    }
}