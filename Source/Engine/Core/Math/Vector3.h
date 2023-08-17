#pragma once
#include <cmath>
#include <sstream>

namespace kiko {

	class Vector3 {

	public:

		float x, y, z;

	public:

		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 operator - () const { return Vector3(-x, -y, -z); }

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }

		Vector3 operator + (const float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (const float s) const { return Vector3(x - s, y - s, z - s); }
		Vector3 operator * (const float s) const { return Vector3(x * s, y * s, z * s); }
		Vector3 operator / (const float s) const { return Vector3(x / s, y / s, z / s); }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }

		Vector3& operator += (const float s) { x += s; y += s; z += s; return *this; }
		Vector3& operator -= (const float s) { x -= s; y -= s; z -= s; return *this; }
		Vector3& operator *= (const float s) { x *= s; y *= s; z *= s; return *this; }
		Vector3& operator /= (const float s) { x /= s; y /= s; z /= s; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return std::sqrt(LengthSqr()); }

		float DistanceSqr(const Vector3& v) const { return (v - *this).LengthSqr(); }
		float Distance(const Vector3& v) const { return (v - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		static float Dot(const Vector3& v1, const Vector3& v2);

		Vector3 Rotate(float radians) const;

	};

	inline Vector3 Vector3::Rotate(float radians) const {

		float _x = x * std::cos(radians) - y * std::sin(radians);
		float _y = x * std::sin(radians) + y * std::cos(radians);

		return { _x, _y, 0.0f };

	}

	inline float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	using vec3 = Vector3;

}