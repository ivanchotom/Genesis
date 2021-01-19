 #include "PCH.h"
#include "Renderer2D.h"

#include "Primitives/Quad.h"



namespace GE {

	

	void Renderer2D::Init()
	{
		GS_PROFILE_FUNCTION();

		Quad::Create();

	}

	void Renderer2D::Shutdown()
	{
		GS_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		GS_PROFILE_FUNCTION();

		Quad::SetQuad("u_ViewProjection", camera.GetViewProjectionMatrix());
		

		StartBatch();
	}

	void Renderer2D::BeginScene(const Camera& camera, glm::mat4& transform)
	{
		GS_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		Quad::SetQuad("u_ViewProjection", viewProj);

		StartBatch();
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		GS_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetViewProjection();

		Quad::SetQuad("u_ViewProjection", viewProj);

		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		GS_PROFILE_FUNCTION();

		Quad::QuadEndScene();

		Flush();
	}

	void Renderer2D::StartBatch()
	{
		Quad::QuadStartBatch();
	}

	void Renderer2D::Flush()
	{
		Quad::QuadFlush();
	}

    void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

}
