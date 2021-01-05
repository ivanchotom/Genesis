#pragma once
#include "entt.hpp"

#include "main/TimeStep.h"

namespace GE {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		void OnUpdate(Timestep ts);

		//TODO: REMOVE
		entt::registry& Reg() { return m_Registry; }


	private:
		entt::registry m_Registry;
	};


}