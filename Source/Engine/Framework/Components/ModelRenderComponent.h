#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace kiko
{
	res_t<Model> m_model;
	class ModelRenderComponent : public RenderComponent
	{
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }
	};

}