#pragma once

#include <glm/glm.hpp>

//#include "Cameras/OrthographicCamera.h"
//#include "Cameras/Camera.h"
#include "Cameras/SceneCamera.h"
#include "ScriptableEntity.h"

namespace GE {

	struct TransformComponent
	{
		glm::mat4 Transform {1.0f};

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; } // Done so u can do DoMath(transform) instead of DoMath(transform.Transform)
		operator const glm::mat4& () const { return Transform; }
	}; 

	struct SpriteRendererComponent
	{
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4 & color)
			: Color(color) {}


	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // move to scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		std::function<void()> InstanciateFunction;
		std::function<void()> DestroyInstanceFunction;


		std::function<void(ScriptableEntity*)> OnCreateFunction;
		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;
		std::function<void(ScriptableEntity*)> OnDestroyFunction;


		template<typename T>
		void Bind()
		{
			InstanciateFunction = [&]() { Instance = new T(); };
			DestroyInstanceFunction = [&]() {delete (T*)Instance; Instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* Instance) { ((T*)Instance)->OnCreate(); };
			OnUpdateFunction = [](ScriptableEntity* Instance, Timestep ts) { ((T*)Instance)->OnUpdate(ts); };
			OnDestroyFunction = [](ScriptableEntity* Instance) { ((T*)Instance)->OnDestroy(); };
		}
	};
}
