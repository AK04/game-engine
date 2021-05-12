#pragma once

#include "Carrot/Layer.h"

#include "Carrot/Events/ApplicationEvent.h"
#include "Carrot/Events/KeyEvent.h"
#include "Carrot/Events/MouseEvent.h"

namespace Carrot {
	
	class CARROT_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}