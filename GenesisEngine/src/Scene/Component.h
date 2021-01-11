#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Cameras/SceneCamera.h"
#include "ScriptableEntity.h"

//TODO : ADD MATERIAL COMPONENT


namespace GE {

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}
		//TransformComponent(const glm::vec3& rotation)
		//	: Rotation(rotation) {}
		//TransformComponent(const glm::vec3& scale)
		//	: Scale(scale) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), Translation);

			// Legacy rotation calculations without quatonions
			//glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
			//	* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
			//	* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });

			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

			glm::mat4 transform = translation * rotation * scale;

			return transform;

		}

		// Done so u can do Example(Translate) instead of Example(translate.Translate)
		//operator glm::vec3& () { return Translation; } 
		//operator const glm::vec3& () const { return Translation; }
		//operator glm::vec3& () { return Rotation; }
		//operator const glm::vec3& () const { return Rotation; }
		//operator glm::vec3& () { return Scale; }
		//operator const glm::vec3& () const { return Scale; }
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

		ScriptableEntity*(*InstanciateScript)();
		void (*DestroyScript)(NativeScriptComponent*);


		template<typename T>
		void Bind()
		{
			InstanciateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}
