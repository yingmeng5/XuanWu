#include <XuanWu.h>

#include <glm/glm.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public XuanWu::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//XW_INFO("ExampleLayer:Update");
		if (XuanWu::Input::IsKeyPressed(XW_KEY_TAB))
			XW_TRACE("Tab Key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(XuanWu::Event& event) override
	{
		//XW_TRACE("{0}", event);
		if (event.GetEventType() == XuanWu::EventType::KeyPressed)
		{
			XuanWu::KeyPressedEvent& e = (XuanWu::KeyPressedEvent&)event;
			XW_INFO("{0}", (char)e.GetKeyCode());
		}
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