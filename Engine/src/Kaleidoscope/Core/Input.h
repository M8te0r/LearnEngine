#pragma once

#include "glm/glm.hpp"
#include "Kaleidoscope/Core/KeyCodes.h"
#include "Kaleidoscope/Core/MouseCodes.h"

namespace Kaleidoscope
{
	class Input
	{
	public:

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode  button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

} // namespace Kaleidoscope
