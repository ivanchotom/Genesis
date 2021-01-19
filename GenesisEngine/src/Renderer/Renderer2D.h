#pragma once

#include "Cameras/OrthographicCamera.h"
#include "Cameras/Camera.h"
#include "Cameras/EditorCamera.h"

#include "Primitives/Quad.h"
#include "Texture.h"
#include "SubTexture2D.h"

namespace GE {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();
		static void StartBatch();
		static void NextBatch();

	 	//Ref<Quad> m_Quad;
		//static void ResetStats();
		//static Statistics GetStats();
	private:  
		//QuadData m_QuadData;
		//QuadVertex m_QuadVertex;
	};

}