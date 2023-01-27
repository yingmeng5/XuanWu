#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "XuanWu/Render/Renderer2D.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, false)
{

}

void Sandbox2D::OnAttach()
{
	XW_PROFILE_FUNCTION();

	m_Texture = XuanWu::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	XW_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(XuanWu::Timestep ts)
{
	XW_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	{
		XW_PROFILE_SCOPE("Renderer Prep");
		XuanWu::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		XuanWu::RenderCommand::Clear();
	}

	{
		XW_PROFILE_SCOPE("Renderer Draw");
		XuanWu::Renderer2D::BeginScene(m_CameraController.GetCamera());
		XuanWu::Renderer2D::DrawQuad({ -1.777f, -1.0f }, { 0.8f, 0.8f }, { 0.8f, 0.8f, 0.8f , 1.0f });
		XuanWu::Renderer2D::DrawQuad({ -1.777f, 1.0f }, { 0.5f, 0.75f }, m_SquareColor);
		//XuanWu::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, 45.0f, m_Texture, 10.0f);
		XuanWu::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	XW_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(XuanWu::Event& event)
{
	m_CameraController.OnEvent(event);
}
