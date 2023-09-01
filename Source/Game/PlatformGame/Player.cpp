#include "Player.h"
#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include <memory>

namespace kiko
{
    CLASS_DEFINITION(Player)

    bool Player::Initialize()
    {
        Actor::Initialize();
        //cache off
        m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
        m_spriteAnimationRenderComponent = GetComponent<kiko::SpriteAnimationRenderComponent>();

        return true;
    }

    void Player::Update(float dt) {

        Actor::Update(dt);

        //bool sprint = kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT);
        //movement

        //jump
        bool onGround = (groundCount > 0);

        //movement
        float direction = 0;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction = -1;
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction = 1;

        vec2 forward = vec2{ 1, 0 };

        //physics engine
        m_physicsComponent->ApplyForce(forward * m_speed * direction * ((onGround) ? 1 : 0.25f));


        //jump and to stop infinite flight when jump is mashed
        if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
        {
            vec2 up = vec2{ 0, -1 };
            m_physicsComponent->SetVelocity(up * jump);
        }

        //animation
        vec2 velocity = m_physicsComponent->m_velocity;
        if (std::fabs(velocity.x) > 0.2f)
        {
            m_spriteAnimationRenderComponent->flipH = (velocity.x <-0.1f);
            m_spriteAnimationRenderComponent->SetSequence("run");

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