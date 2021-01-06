#include "PCH.h"
#include "Scene.h"

#include "Component.h"
#include "Renderer/Renderer2D.h"

#include "glm/glm.hpp"

#include "Entity.h"

namespace GE {

	Scene::Scene()
	{
		//entt::entity is literally an id of type uint32_t
		entt::entity entity = m_Registry.create();

	    m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));


		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{

		//Render 
		Camera* mainCamera = nullptr;
		{
			auto group = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					break;
				}
			}
		}

		if (mainCamera)
		{
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}
		}
	}

}