#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace kiko
{

	CLASS_DEFINITION(SpriteRenderComponent);

	bool kiko::SpriteRenderComponent::Initialize()
	{
		if (!textureName.empty()) {
			m_texture = GET_RESOURCE(Texture, textureName, g_renderer);
		}

		return true;
	}

	void kiko::SpriteRenderComponent::Update(float dt)
	{

	}
	void kiko::SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform.position.x, m_owner->transform.position.y, RadToDeg(m_owner->transform.rotation));
	}

	void SpriteRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
	}

}



