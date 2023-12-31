#pragma once
#include "Framework/Resource/Resource.h"
#include "Core/Core.h"
#include <vector>

namespace kiko {

	class Renderer;

	class Model : public Resource
	{
	public:

		Model() = default;
		Model(std::vector<vec2> points) : m_points{ points } {}
		Model(const std::string& filename) { Load(filename); }

		bool Create(std::string filename, ...);
		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();


	private:

		std::vector<vec2> m_points;
		float m_radius{};
		Color m_color;

	};

}