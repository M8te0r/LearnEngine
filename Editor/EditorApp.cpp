#include "Engine.h"

#include "Kaleidoscope/Core/EntryPoint.h"

#include "EditorLayer.h"


namespace Kaleidoscope {

	class Editor :public Application
	{
	public:
		Editor()
			:Application("Kaleidoscope Editor")
		{
			PushLayer(new EditorLayer());
		}

		~Editor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new Editor();
	}
}
