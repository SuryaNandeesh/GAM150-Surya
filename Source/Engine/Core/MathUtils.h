#pragma once

#include <cmath>
#include <utility>

namespace kiko {

	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 6.28318530718f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadToDeg(float radians) { return radians * 180.0f / Pi;  }
	constexpr float DegToRad(float radians) { return radians * Pi / 180.0f;  }

	constexpr int Wrap(int value, int max) { return (value % max) + ((value < 0) ? max : 0); }
	inline float Wrap(float value, float max) { return std::fmod(value, max) + ((value < 0) ? max : 0); }
	inline float Wrap(float value, int max) { return Wrap(value, (float)max); }
	inline float Wrap(int value, float max) { return Wrap((float) value, max); }

	template <typename T>
	inline T Max(T a, T b) { return (a > b) ? a : b; }

	template <typename T>
	inline T Min(T a, T b) { return (a < b) ? a : b; }

	template <typename T>
	inline T Clamp(T value, T min, T max) {

		if (min > max) std::swap(min, max);
		return (value < min) ? min : (value > max) ? max : value;

	}

}