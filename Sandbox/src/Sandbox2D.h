#pragma once

#include "Carrot.h"

class Sandbox2D : public Carrot::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Carrot::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Carrot::Event& e) override;
private:
	Carrot::OrthographicCameraController m_CameraController;

	// Temp
	Carrot::Ref<Carrot::VertexArray> m_SquareVA;
	Carrot::Ref<Carrot::Shader> m_FlatColorShader;

	Carrot::Ref<Carrot::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};