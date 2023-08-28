#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Framework/Emitter.h"
#include "Projectile.h"
#include "Framework/Scene.h"
#include <memory>
#include "Framework/Event/EventManager.h"

namespace kiko
{
    CLASS_DEFINITION(Enemy)

    void Enemy::Update(float dt) {

        if (m_health <= 0.0f) {

            //add points
            kiko::EventManager::Instance().DispatchEvent("AddPoints", 100);

            // make explosion
            kiko::EmitterData data;
            data.burst = true;
            data.burstCount = 100;
            data.spawnRate = 200;
            data.angle = 0;
            data.angleRange = kiko::Pi;
            data.lifetimeMin = 0.5f;
            data.lifetimeMin = 1.5f;
            data.speedMin = 50;
            data.speedMax = 250;
            data.damping = 0.5f;
            data.color = Color{ 1, (float)0.1, 0, 1 };

            kiko::Transform transform{ this->transform.position, 0, 1 };
            auto emitter = std::make_unique<kiko::Emitter>(transform, data);
            emitter->SetLifespan(1.0f);
            m_scene->Add(std::move(emitter));

        }

        Actor::Update(dt);
        Player* player = m_scene->GetActor<Player>();
        if (player) {

            kiko::vec2 direction = player->GetTransform().position - GetTransform().position;
            transform.rotation = direction.Angle() + kiko::HalfPi;

        }

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
        transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
        transform.position.x = kiko::Wrap(transform.position.x, kiko::g_renderer.GetWidth());
        transform.position.y = kiko::Wrap(transform.position.y, kiko::g_renderer.GetHeight());
        m_firetimer -= dt;
        if (m_firetimer <= 0) {

            m_firetimer = m_firerate;
            //std::unique_ptr<kiko::Projectile> projectile = std::make_unique<kiko::Projectile>(
            //    400.0f,
            //    kiko::Transform{ m_transform.position, m_transform.rotation, 1 },
            //    GetTag(),
            //    10.0f,
            //    2.0f
            //);
            //m_scene->Add(std::move(projectile));

        }

    }

    void Enemy::OnCollision(Actor* other) {}

    void Enemy::Read(const json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, m_speed);
    }
}