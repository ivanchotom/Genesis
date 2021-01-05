#include "PCH.h"
#include "Scene.h"


#include "glm/glm.hpp"

namespace GE {

	static void DoMath(const glm::mat4& transform)
	{

	}





	Scene::Scene()
	{

		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}

			operator glm::mat4& () { return Transform; } // Done so u can do DoMath(transform) instead of DoMath(transform.Transform)
			operator const glm::mat4& () const { return Transform; }
		};


		//entt::entity is literally an id of type uint32_t
		entt::entity entity = m_Registry.create();

	    m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));


		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(Timestep ts)
	{

	}

}