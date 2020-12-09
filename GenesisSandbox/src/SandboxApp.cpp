#include "PCH.h"

#include "main/Engine.h"

#include "ImGui/imgui.h"


class ExampleLayer : public GE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	    {
		m_VertexArray.reset(GE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};



		std::shared_ptr<GE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GE::VertexBuffer::Create(vertices, sizeof(vertices)));
		GE::BufferLayout layout = {
			{ GE::ShaderDataType::Float3, "a_Position" },
			{ GE::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<GE::IndexBuffer> indexBuffer;
		indexBuffer.reset(GE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(GE::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<GE::VertexBuffer> squareVB;
		squareVB.reset(GE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		GE::BufferLayout squareVBlayout = {
			{ GE::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareVBlayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<GE::IndexBuffer> squareIB;
		squareIB.reset(GE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
		
		#version 330 core

		layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        
		
		out vec3 v_Position;
        out vec4 v_Color; 
        
		
		void main() 
		{
			v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			
		}  

		)";

		std::string fragmentSrc = R"(
		
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
        in vec4 v_Color; 
		
		void main() 
		{
			color = vec4(v_Position, 1.0);
            color = v_Color;
			
		}  

		)";



		m_Shader.reset(new GE::Shader(vertexSrc, fragmentSrc));

		std::string blueShadervertexSrc = R"(
		
		#version 330 core

		layout(location = 0) in vec3 a_Position;
       
        uniform mat4 u_ViewProjection;
		
		out vec3 v_Position;
        
		
		void main() 
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			
		}  

		)";

		std::string blueShaderfragmentSrc = R"(
		
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		
		void main() 
		{
			color = vec4(0.2, 0.3, 0.8, 1.0);
            
			
		}  

		)";



		m_BlueShader.reset(new GE::Shader(blueShadervertexSrc, blueShaderfragmentSrc));
	    }

	void OnUpdate() override
	{
		if (GE::Input::IsKeyPressed  (GE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (GE::Input::IsKeyPressed  (GE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;
		 if (GE::Input::IsKeyPressed (GE_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;
		else if (GE::Input::IsKeyPressed (GE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;

		 if (GE::Input::IsKeyPressed(GE_KEY_A))
			 m_CameraRotation -= m_CameraRotationSpeed;
		 if (GE::Input::IsKeyPressed(GE_KEY_D))
			 m_CameraRotation += m_CameraRotationSpeed;
		
		

		



		GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GE::RenderCommand::Clear();

		m_Camera.SetPosition({ m_CameraPosition });
		m_Camera.SetRotation(m_CameraRotation);

		GE::Renderer::BeginScene(m_Camera);


		GE::Renderer::Submit(m_BlueShader, m_SquareVA);
		GE::Renderer::Submit(m_Shader, m_VertexArray);

		GE::Renderer::EndScene();

		//Renderer::Flush;  for multithread
		

		//if (GE::Input::IsKeyPressed(GE_KEY_TAB))
		//	GE_TRACE("Tab key is pressed");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}


	void OnEvent(GE::Event& event) override
	{

		//GE_TRACE("{0}", event);
	}

	/*bool OnKeyPressedEvent(GE::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == GE_KEY_LEFT)
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}

		if (event.GetKeyCode() == GE_KEY_RIGHT)
		{
			m_CameraPosition.x += m_CameraSpeed;
		}

		if (event.GetKeyCode() == GE_KEY_DOWN)
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}

		if (event.GetKeyCode() == GE_KEY_UP)
		{
			m_CameraPosition.y += m_CameraSpeed;
		}


		return false;
	}
	*/
private:
	std::shared_ptr<GE::Shader> m_Shader;
	std::shared_ptr<GE::VertexArray> m_VertexArray;

	std::shared_ptr<GE::Shader> m_BlueShader;
	std::shared_ptr<GE::VertexArray> m_SquareVA;

	GE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;


	float m_CameraSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.1f;
};

class Sandbox : public GE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new GE::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

GE::Application* GE::CreateApplication()
{
	return new Sandbox;
}