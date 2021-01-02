
#include "main/Engine.h"
#include "main/EntryPoint.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Layers/Sandbox2D.h"
#include "Layers/2DGameLayer.h"

/*
class ExampleLayer : public GE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	    {
		m_VertexArray = GE::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};



		GE::Ref<GE::VertexBuffer> vertexBuffer;
		vertexBuffer = GE::VertexBuffer::Create(vertices, sizeof(vertices));
		GE::BufferLayout layout = {
			{ GE::ShaderDataType::Float3, "a_Position" },
			{ GE::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		GE::Ref<GE::IndexBuffer> indexBuffer;
		indexBuffer = GE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = GE::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		GE::Ref<GE::VertexBuffer> squareVB;
		squareVB = GE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		GE::BufferLayout squareVBlayout = {
			{ GE::ShaderDataType::Float3, "a_Position" },
			{ GE::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareVBlayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		GE::Ref<GE::IndexBuffer> squareIB;
		squareIB = GE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
		
		#version 330 core

		layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;
        
		
		out vec3 v_Position;
        out vec4 v_Color; 
        
		
		void main() 
		{
			v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			
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



		m_Shader = GE::Shader::Create("VertexPosTriangle", vertexSrc, fragmentSrc);

		std::string flatColorShadervertexSrc = R"(
		
		#version 330 core

		layout(location = 0) in vec3 a_Position;
       
        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;
		
		out vec3 v_Position;
        
		
		void main() 
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			
		}  

		)";

		std::string flatColorShaderfragmentSrc = R"(
		
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
        
        uniform vec3 u_Color;
		
		void main() 
		{
			color = vec4(u_Color, 1.0);	
		}  

		)";

		m_FlatColorShader = GE::Shader::Create("FlatColor", flatColorShadervertexSrc, flatColorShaderfragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = GE::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<GE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<GE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}


	void OnUpdate(GE::Timestep ts) override
	{
		// GE_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		//Update
		m_CameraController.OnUpdate(ts);

		//Render
		GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GE::RenderCommand::Clear();

		GE::Renderer::BeginScene(m_CameraController.GetCamera());

	    glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(0.1f));

		std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				GE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		GE::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		GE::Renderer::Submit(textureShader, m_SquareVA,  glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));

		//Triangle 
		//GE::Renderer::Submit(m_Shader, m_VertexArray);

		GE::Renderer::EndScene();

		
		

		//if (GE::Input::IsKeyPressed(GE_KEY_TAB))
		//	GE_TRACE("Tab key is pressed");
	}

	virtual void OnImGuiRender() override
	{
		//Test Window
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

		//Color
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();


	}


	void OnEvent(GE::Event& e) override
	{
		m_CameraController.OnEvent(e);
		//Event test
		//GE_TRACE("{0}", event);
	}


	//Event Template
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
	
private:
	GE::ShaderLibrary m_ShaderLibrary;
	GE::Ref<GE::Shader> m_Shader;
	GE::Ref<GE::VertexArray> m_VertexArray;

	GE::Ref<GE::Shader> m_FlatColorShader;
	GE::Ref<GE::VertexArray> m_SquareVA;

	GE::Ref<GE::Texture2D> m_Texture, m_ChernoLogoTexture;

	GE::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};
*/
class Sandbox : public GE::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		//PushOverlay(new GE::ImGuiLayer());
		//PushLayer(new GameLayer());
	}

	~Sandbox()
	{

	}
};

GE::Application* GE::CreateApplication()
{
	return new Sandbox;
}