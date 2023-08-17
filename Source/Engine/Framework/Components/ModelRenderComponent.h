#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace kiko
{

	class ModelRenderComponent : public RenderComponent
	{
		CLASS_DEC(ModelRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }
		res_t<Model> m_model;

		std::string ModelName;
	};
	
}