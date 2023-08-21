#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace kiko
{

	CLASS_DEFINITION(SpriteRenderComponent);

	bool kiko::SpriteRenderComponent::Initialize()
	{
		//if (!textureName.empty()) {
		//	m_texture = GET_RESOURCE(Texture, textureName, g_renderer)
		//}

		return true;
	}

	void kiko::SpriteRenderComponent::Update(float dt)
	{

	}
	void kiko::SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, RadToDeg(m_owner->m_transform.rotation));
	}

	void SpriteRenderComponent::Read(const json_t& value)
	{
		//
	}

}



