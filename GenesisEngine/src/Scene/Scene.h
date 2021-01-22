#pragma once

#include "main/TimeStep.h"
#include "Cameras/EditorCamera.h"
#include "Renderer/Framebuffer.h"

#include "entt.hpp"

namespace GE {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);

		void OnViewportResize(uint32_t width, uint32_t height);
		void DrawIDBuffer(Ref<FrameBuffer> target, EditorCamera& camera);
		int Pixel(int x, int y);
		

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		//friend class Quad;
		friend class Renderer2D;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};


}