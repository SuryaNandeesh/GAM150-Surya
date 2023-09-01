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
        m_physicsComponent = GetComponent<PhysicsComponent>();
        m_spriteAnimationRenderComponent = GetComponent<SpriteAnimationRenderComponent>();

        return true;
    }

    void Player::OnDestroy()
    {
        //
    }

    void Player::Update(float dt) {

        Actor::Update(dt);

        vec2 forward = vec2{ 1, 0 };
        vec2 velocity = m_physicsComponent->m_velocity;
        bool onGround = (groundCount > 0); //for jump stuff

        //movement
        float direction = 0;
        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction = -1;
        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction = 1;


        //jump and to stop infinite flight when jump is mashed
        if (onGround && g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
        {
            vec2 up = vec2{ 0, -1 };
            m_physicsComponent->SetVelocity(up * jump);
        }

        //animation
        if (std::fabs(velocity.x) > 0.2f)
        {
            m_spriteAnimationRenderComponent->flipH = (velocity.x <-0.1f);
            m_spriteAnimationRenderComponent->SetSequence("run");
        }
        

        //physics engine
        m_physicsComponent->ApplyForce(forward * m_speed * direction * ((onGround) ? 1 : 0.25f));
    }

    void Player::OnCollisionEnter(Actor* other)
    {
        if (other->tag == "Ground") groundCount++;
        if (other->tag == "Enemy")
        {
            kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
        }
        if (other->tag == "Coin")
        {
            kiko::EventManager::Instance().DispatchEvent("OnCoinPickup", 0);
            other->m_destroyed = true;
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
        READ_DATA(value, jump);
    }
}