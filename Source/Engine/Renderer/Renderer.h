#pragma once
#include <SDL2-2.28.1/include/SDL.h>
#include <string>
#include <Core/Vector2.h>

namespace kiko {

	class Renderer {

	public:

		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& name, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(int r, int g, int b, int a);

		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(vec2& p1, vec2& p2);

		void DrawPoint(int x, int y);
		void DrawPoint(float x, float y);
		void DrawPoint(vec2& p);

		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		friend class Text;
		friend class Texture;

	private:

		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;

	};

	extern Renderer g_renderer;

}