#include <Header.h>


class Sandbox : public XuanWu::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

XuanWu::Application* XuanWu::CreateApplication()
{
	return new Sandbox();
}