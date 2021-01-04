#pragma once

#include "main/Layer.h"

#include "Events/AppEvent.h"
#include "Events/Keyboard.h"
#include "Events/Mouse.h"

namespace GE {

	class GENESIS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
	    virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
	
		void SetBlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}
