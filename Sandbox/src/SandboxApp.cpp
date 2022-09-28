#include <XuanWu.h>


class ExampleLayer : public XuanWu::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		XW_INFO("ExampleLayer:Update");
	}

	void OnEvent(XuanWu::Event& event) override
	{
		XW_TRACE("{0}", event);
	}
};

class Sandbox : public XuanWu::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

XuanWu::Application* XuanWu::CreateApplication()
{
	return new Sandbox();
}