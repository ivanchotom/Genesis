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

		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		Ref<Scene> m_Cotext;
		Entity m_SelectionContext;
	};

}