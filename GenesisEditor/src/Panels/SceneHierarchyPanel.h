#pragma once

#include "main/Core.h"
#include "main/Log.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

namespace GE {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);


		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);

		Ref<Scene> m_Cotext;
		Entity m_SelectionContext;
	};

}