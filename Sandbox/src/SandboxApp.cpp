#include <Carrot.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include "Carrot/Core/Timestep.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Carrot::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(Carrot::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Carrot::Ref<Carrot::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Carrot::VertexBuffer::Create(vertices, sizeof(vertices)));
		Carrot::BufferLayout layout = {
			{ Carrot::ShaderDataType::Float3, "a_Position" },
			{ Carrot::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Carrot::Ref<Carrot::IndexBuffer> indexBuffer;
		indexBuffer.reset(Carrot::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Carrot::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Carrot::Ref<Carrot::VertexBuffer> squareVB;
		squareVB.reset(Carrot::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Carrot::ShaderDataType::Float3, "a_Position" },
			{ Carrot::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Carrot::Ref<Carrot::IndexBuffer> squareIB;
		squareIB.reset(Carrot::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Carrot::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Carrot::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Carrot::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Carrot::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Carrot::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Carrot::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Carrot::Timestep ts) override {

		if(Carrot::Input::IsKeyPressed(CT_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Carrot::Input::IsKeyPressed(CT_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		
		if (Carrot::Input::IsKeyPressed(CT_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Carrot::Input::IsKeyPressed(CT_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		
		if (Carrot::Input::IsKeyPressed(CT_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Carrot::Input::IsKeyPressed(CT_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		
		Carrot::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Carrot::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Carrot::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Carrot::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Carrot::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for(int y = 0; y < 20; y++)
		{
			for(int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Carrot::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Carrot::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Carrot::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		// Triangle
		//Carrot::Renderer::Submit(m_Shader, m_VertexArray);

		Carrot::Renderer::EndScene();

		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
		ImGui::Begin("Albin's stuff");
		float f = 20.0f;
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::End();
	}



	void OnEvent(Carrot::Event& event) override {
		
	}



private:
	Carrot::ShaderLibrary m_ShaderLibrary;
	Carrot::Ref<Carrot::Shader> m_Shader;
	Carrot::Ref<Carrot::VertexArray> m_VertexArray;

	Carrot::Ref<Carrot::Shader> m_FlatColorShader;
	Carrot::Ref<Carrot::VertexArray> m_SquareVA;

	Carrot::Ref<Carrot::Texture2D> m_Texture, m_ChernoLogoTexture;
	
	Carrot::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.1f;
	
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	
};

class Sandbox : public Carrot::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}

};

Carrot::Application* Carrot::CreateApplication() {
	return new Sandbox();
}