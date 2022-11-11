#pragma once
#include "XuanWu.h"

class Sandbox2D : public XuanWu::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(XuanWu::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(XuanWu::Event& event) override;
private:
	XuanWu::Ref<XuanWu::Shader> m_Shader;
	XuanWu::Ref<XuanWu::Texture2D> m_Texture;
	XuanWu::OrthographicCameraController m_CameraController;

	XuanWu::Ref<XuanWu::VertexArray> m_SquareVA;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};