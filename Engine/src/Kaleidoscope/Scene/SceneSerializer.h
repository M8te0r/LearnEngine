#pragma once
#include "Kaleidoscope/Scene/Scene.h"

namespace Kaleidoscope
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);//yaml格式
		void SerializeRuntime(const std::string& filepath);//binary格式

		bool Deserialize(const std::string& filepath);//yaml格式
		bool DeserializeRuntime(const std::string& filepath);//binary格式

	private:
		Ref<Scene> m_Scene;
	};
}