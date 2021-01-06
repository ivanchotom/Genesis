#pragma once

#include "Scene.h"
#include "entt.hpp"

//#include <glm/glm.hpp>

namespace GE {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default; // just in case 

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) // Basically tells that we want theese arguments to be shoved("forwarded") to entt
		{
			GS_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			GS_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			GS_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		//glm::mat4& Transform() { return m_Scene->m_Registry.get<TransformComponent>(m_EntityHandle); }
		//const glm::mat4& Transform() const { return m_Scene->m_Registry.get<TransformComponent>(m_EntityHandle); }
		//
		//operator uint32_t () const { return (uint32_t)m_EntityHandle; }
		//operator entt::entity() const { return m_EntityHandle; }
		//operator bool() const { return (uint32_t)m_EntityHandle && m_Scene; }
		//
		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}
		
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		 

	private:

		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;

	};

}