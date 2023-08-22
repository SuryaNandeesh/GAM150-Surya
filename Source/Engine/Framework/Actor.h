#pragma once
#include "Object.h"
#include "Audio/AudioSystem.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace kiko {

	class Actor : public Object{

	public:

		CLASS_DECLARATION(Actor);

		Actor() = default;
		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}
		Actor(const Actor& other);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		template<typename T>
		T* GetComponent();
		void AddComponent(std::unique_ptr<Component> component);

		virtual void OnCollision(Actor* other) {};

		float GetRadius() { return 30; }
		float GetHealth() { return m_health; }

		std::string GetTag() { return m_tag; }
		Transform GetTransform() { return m_transform; }

		void SetLifespan(float lifespan) { m_lifespan = lifespan; }

		virtual void Damage(float damage) { m_health -= damage; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;
		bool persistent = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
		float m_health = -1.0f;

	};

	template<typename T>
	inline T* Actor::GetComponent() {

		for (auto& component : m_components) {

			T* result = dynamic_cast<T*> (component.get());
			if (result) return result;
		}

		return nullptr;

	}

}