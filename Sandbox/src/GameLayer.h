#pragma once

#include "Carrot.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Carrot::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Carrot::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Carrot::Event& e) override;
	bool OnMouseButtonPressed(Carrot::MouseButtonPressedEvent& e);
	bool OnWindowResize(Carrot::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Carrot::Scope<Carrot::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};