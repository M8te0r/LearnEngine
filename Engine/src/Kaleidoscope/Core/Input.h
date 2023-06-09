#pragma once

#include "Kaleidoscope/Core/Base.h"
#include "Kaleidoscope/Core/KeyCodes.h"
#include "Kaleidoscope/Core/MouseCodes.h"

namespace Kaleidoscope
{
	class Input
	{
	public:

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode  button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();


	
	};

} // namespace Kaleidoscope
