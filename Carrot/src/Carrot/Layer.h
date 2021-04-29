#pragma once

#include "Carrot/Core.h"
#include "Carrot/Events/Event.h"

namespace Carrot {

	class CARROT_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	
	};


}