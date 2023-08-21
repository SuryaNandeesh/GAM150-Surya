#include "Player.h"
#include "Projectile.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Renderer/Renderer.h"
#include <memory>
#include <Framework/Components/RenderComponent.h>
#include <Framework/Components/CollisionComponent.h>

bool Player::Initialize()
{
    Actor::Initialize();
    //cache off
    m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
    auto collisionComponent = GetComponent<kiko::CollisionComponent>();
    if (collisionComponent) 
    {
        auto renderComponent = GetComponent<kiko::RenderComponent>();
        if (renderComponent)
        {
            float scale = m_transform.scale;
            collisionComponent->m_radius = renderComponent->GetRadius() * scale;
        }
    }

    return true;
}

void Player::Update(float dt) {

    Actor::Update(dt);

    bool sprint = kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT);

    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
    m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

    float thrust = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
    //AddForce(forward * m_speed * thrust * ((sprint) ? 2.0f : 1.0f));

    //physics engine
    auto physicsComponent = GetComponent<kiko::PhysicsComponent>();
    physicsComponent->ApplyForce(forward * m_speed * thrust);
    
    //wrap of screen
    m_transform.position.x = kiko::Wrap(m_transform.position.x, kiko::g_renderer.GetWidth());
    m_transform.position.y = kiko::Wrap(m_transform.position.y, kiko::g_renderer.GetHeight());

    if (m_health <= 0)
    {
        dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
    }
    //fire weapon
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

        auto projectile = INSTANTIATE(Projectile, "Rocket");
        projectile->m_transform = {m_transform.position, m_transform.rotation + kiko::DegToRad(180.0f)}; // problem here with proj = empty
        projectile->Initialize();
        m_scene->Add(std::move(projectile));

        projectile = INSTANTIATE(Projectile, "Rocket");
        projectile->m_transform = { m_transform.position, m_transform.rotation + kiko::DegToRad(180) };
        projectile->Initialize();
        m_scene->Add(std::move(projectile));

       /* std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(
            400.0f, 
            kiko::Transform{m_transform.position, m_transform.rotation, 1.0f}, 
            GetTag(),
            10.0f, 
            2.0f
            );

        m_scene->Add(std::move(projectile));*/
    
    }

}

void Player::OnCollision(Actor* other)
{
    // this was placed inside of the actor.cpp
}
