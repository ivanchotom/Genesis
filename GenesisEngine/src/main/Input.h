#pragma once

#include "Core.h"
#include "Events/KeyCodes.h"
#include "Events/MouseCode.h"
#include <glm/glm.hpp>

namespace GE {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}

