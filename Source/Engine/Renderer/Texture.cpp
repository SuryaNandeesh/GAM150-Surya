#include "Texture.h"
#include "Renderer.h"
#include "SDL2-2.28.1/include/SDL_image.h"
#include <Core/Logger.h>

namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Create(std::string filename, ...) {

		va_list args;

		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(filename, renderer);
	}

	bool Texture::Load(std::string filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load("garflied.jpg");
		if (!surface)
		{
			WARNING_LOG("Unable to load surface");
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("unable to load texture");
			return false;
		}
		return true;
	}
	vec2 Texture::GetSize()
	{
		ASSERT_LOG(m_texture, "Texture is null!");

		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture

		SDL_QueryTexture(m_texture, NULL, NULL, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}
}
