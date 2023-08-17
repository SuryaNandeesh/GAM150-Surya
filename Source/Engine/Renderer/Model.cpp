#include "Model.h"
#include "Renderer.h"
#include <sstream>

namespace kiko{

	bool Model::Create(std::string filename, ...)
	{
		return Load(filename);
	}

	bool Model::Load(const std::string& filename) {

		std::string buffer;
		kiko::readFile(filename, buffer);

		std::istringstream stream(buffer);

		stream >> m_color;

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);
		for (int i = 0; i < numPoints; i++) {

			vec2 point;
			stream >> point;
			m_points.push_back(point);

		}

		return true;

	}

	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale) {

		if (m_points.empty()) return;

		renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < m_points.size() - 1; i++) {

			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}

	}

	void Model::Draw(Renderer& renderer, const Transform& transform) {
		//Draw(renderer, transform.position, transform.rotation, transform.scale);
		if (m_points.empty()) return;

		mat2 mx = transform.GetMartix();
		
		renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i]) + transform.position;
			vec2 p2 = (m_points[i + 1]) + transform.position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);

		}
	}

	float Model::GetRadius() {

		if (m_radius) return m_radius;

		for (auto point : m_points)
			m_radius = Max(m_radius, point.Length());

		return m_radius;

	}


}
