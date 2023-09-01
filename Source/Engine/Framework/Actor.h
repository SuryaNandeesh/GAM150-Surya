#pragma once
#include "Object.h"
#include "Audio/AudioSystem.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace kiko 
{

	class Actor : public Object{

	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

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

		std::string GetTag() { return tag; }
		Transform GetTransform() { return transform; }

		void SetLifespan(float lifespan) { lifespan = lifespan; }

		virtual void Damage(float damage) { m_health -= damage; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool persistent = false;
		bool prototype = false;

		bool m_destroyed = false;
	protected:
		std::vector<std::unique_ptr<Component>> components;

		float m_health = -1.0f;

	};

	template<typename T>
	inline T* Actor::GetComponent() {

		for (auto& component : components) {

			T* result = dynamic_cast<T*> (component.get());
			if (result) return result;
		}

		return nullptr;

	}

}