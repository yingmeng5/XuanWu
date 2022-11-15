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
	m_Texture = XuanWu::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(XuanWu::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	XuanWu::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
	XuanWu::RenderCommand::Clear();

	XuanWu::Renderer2D::BeginScene(m_CameraController.GetCamera());

	XuanWu::Renderer2D::DrawQuad({ -1.0f, 1.0f }, { 0.5f, 0.5f }, { 0.8f, 0.8f, 0.8f , 1.0f });
	XuanWu::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
	XuanWu::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
	XuanWu::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(XuanWu::Event& event)
{
	m_CameraController.OnEvent(event);
}
