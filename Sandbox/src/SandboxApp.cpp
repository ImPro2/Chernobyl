#include "sandboxpch.hpp"

class Sandbox;

#define CH_API_ENTRY
#include "Chernobyl.hpp"


class Sandbox : public CH::Application
{
public:
	Sandbox(CH::ApplicationStartupArguments args) 
		: Application(args)
	{
	}
	~Sandbox() {}
};

CH::Application* CH::CreateApplication(CH::ApplicationStartupArguments args)
{
	return new Sandbox(args);
}