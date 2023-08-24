#include "Projectile.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include <Framework/Components/EnginePhysicsComponent.h>

namespace kiko
{
    CLASS_DEFINITION(Projectile)

    void Projectile::Update(float dt) {

        Actor::Update(dt);

        //m_physicsComponent = GetComponent<PhysicsComponent>();

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
        transform.position += forward * speed * kiko::g_time.GetDeltaTime();
        transform.position.x = kiko::Wrap(transform.position.x, kiko::g_renderer.GetWidth());
        transform.position.y = kiko::Wrap(transform.position.y, kiko::g_renderer.GetHeight());
    }

    void Projectile::OnCollision(Actor* other)
    {
        if (other->GetTag() != GetTag())
        {
            m_destroyed = true;
            other->Damage(damage);
        }
    }

    void Projectile::Read(const json_t& value)
    {
        Actor::Read(value);

        READ_DATA(value, speed);
        READ_DATA(value, damage);
    }

}
