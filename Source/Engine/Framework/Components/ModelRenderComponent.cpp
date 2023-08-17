#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace kiko
{
	CLASS_DEF(ModelRenderComponent)

	bool ModelRenderComponent::Initialize()
	{
		if (!ModelName.empty()) m_model = GET_RESOURCE(Model, ModelName);

		return true;
	}

	void ModelRenderComponent::Update(float dt)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
	}

	void ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, ModelName);
	}
}