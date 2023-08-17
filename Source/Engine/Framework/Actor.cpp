#include "Actor.h"
#include "Object.h"
#include "Components/RenderComponent.h"
#include "Components/CircleCollisionComponent.h"
#include "Components/PhysicsComponent.h"

namespace kiko {

	CLASS_DEF(Actor)

	bool Actor::Initialize()
	{
		for (auto& component : m_components) {
			component->Initialize();
		}

		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (collisionComponent && renderComponent)
			collisionComponent->m_radius = renderComponent->GetRadius() * m_transform.scale;

		return true;
	}
	void Actor::OnDestroy()
	{
		for (auto& component : m_components) {
			component->OnDestroy();
		}
	}
	void Actor::Update(float dt){

		if (m_lifespan != -1.0f)
			(m_lifespan > 0) ? m_lifespan -= dt : m_destroyed = true;

		if (m_health <= 0 && m_health != -1.0f) {
			m_destroyed = true;	
		}

		if ((GetComponent<PhysicsComponent>()))
			GetComponent<PhysicsComponent>()->Update(dt);

		/*for (auto& component : m_components) {
			component->Update(dt);
		}*/

	}

	void Actor::Draw(kiko::Renderer& renderer) {

		//if(m_model) m_model->Draw(renderer, m_transform);
		for (auto& compontent : m_components)
		{
			if (dynamic_cast<RenderComponent*>(compontent.get()))
			{
				RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(compontent.get());
				if (renderComponent) renderComponent->Draw(renderer);
			}
		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));

	}
	bool Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, m_tag);
		READ_DATA(value, m_lifespan);

		if (HAS_DATA(value, m_transform)) m_transform.Read(GET_DATA(value, m_transform));
		if (HAS_DATA(value, m_components) && GET_DATA(value, m_components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, m_components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);
				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}


		
	}

}