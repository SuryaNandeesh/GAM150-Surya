#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DEC(classname) \
	virtual const char* GetClassName() { return #classname; } \
	bool Read(const rapidjson::Value& value); \
	class Register { \
		public: \
			Register(){ \
				Factory::Instance().Register<classname>(#classname); \
			} \
		};

#define CLASS_DEF(classname) \
	classname::Register reg;

namespace kiko
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { OnDestroy(); }

		CLASS_DEC(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string name;
	};
}