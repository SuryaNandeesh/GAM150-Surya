#include "Actor.h"
#include "Components/RenderComponent.h"

namespace kiko {
	
	void Actor::Update(float dt){

		if (m_lifespan != -1.0f)
			(m_lifespan > 0) ? m_lifespan -= dt : m_destroyed = true;

		if (m_health <= 0 && m_health != -1.0f) {
			m_destroyed = true;
			
		}

		m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);

	}

	void Actor::Draw(kiko::Renderer& renderer) {

		//if(m_model) m_model->Draw(renderer, m_transform);
		for (auto& compontent : m_components)
		{
			if (dynamic_cast<RenderComponent*>(compontent.get()))
			{
				RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(compontent.get());
				if (renderComponent) {
					renderComponent->Draw(renderer);
				}
			}
		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));

	}


}