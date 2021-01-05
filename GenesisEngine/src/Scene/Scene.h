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


	private:
		entt::registry m_Registry;
	};


}