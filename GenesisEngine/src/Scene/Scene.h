#pragma once
#include "entt.hpp"

#include "main/TimeStep.h"

namespace GE {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);


	private:
		entt::registry m_Registry;
	};


}