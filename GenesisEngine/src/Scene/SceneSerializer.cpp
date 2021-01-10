#include "PCH.h"
#include "SceneSerializer.h"
#include "Component.h"
#include "Entity.h"
#include <fstream>

#include "yaml-cpp/yaml.h"



namespace GE {


	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{

	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity";
		out << YAML::Value << "12837192831273"; // Update to take unique entity id in the future

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent
		}

		//if (entity.HasComponent<TransformComponent>())
		//{
		//	out << YAML::Key << "TransformComponent";
		//	out << YAML::BeginMap; // TransformComponent
		//
		//	auto& tc = entity.GetComponent<TransformComponent>();
		//	out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
		//	out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
		//	out << YAML::Key << "Scale" << YAML::Value << tc.Scale;
		//
		//	out << YAML::EndMap; // TransformComponent
		//}
		//
		//if (entity.HasComponent<CameraComponent>())
		//{
		//	out << YAML::Key << "CameraComponent";
		//	out << YAML::BeginMap; // CameraComponent
		//
		//	auto& cameraComponent = entity.GetComponent<CameraComponent>();
		//	auto& camera = cameraComponent.Camera;
		//
		//	out << YAML::Key << "Camera" << YAML::Value;
		//	out << YAML::BeginMap; // Camera
		//	out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
		//	out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
		//	out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
		//	out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
		//	out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
		//	out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
		//	out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
		//	out << YAML::EndMap; // Camera
		//
		//	out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
		//	out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;
		//}
			out << YAML::EndMap; // CameraComponent
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
		{
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const const std::string& filepath)
	{

	}

	bool SceneSerializer::DeSerialize(const std::string& filepath)
	{
		return false;
	}

	bool SceneSerializer::DeSerializeRuntime(const std::string& filepath)
	{
		//Not Implemented
		//GS_CORE_ASSERT(false);

		return false;
	}

}