#include "Projectile.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace kiko
{
    CLASS_DEFINITION(Projectile)

    void Projectile::Update(float dt) {

        Actor::Update(dt);

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
        m_transform.position += forward * speed * kiko::g_time.GetDeltaTime();
        m_transform.position.x = kiko::Wrap(m_transform.position.x, kiko::g_renderer.GetWidth());
        m_transform.position.y = kiko::Wrap(m_transform.position.y, kiko::g_renderer.GetHeight());
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
        READ_DATA(value, speed);
        READ_DATA(value, damage);

    }

}
