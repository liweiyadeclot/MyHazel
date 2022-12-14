#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr< Hazel::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));


		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float4, "a_Color"}
		};
		//在addVB之前，必须先设置好VB中的layout

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr< Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		//glDrawArrays(GL_TRIANGLES)

		//创建square的Vertex Array
		m_SquareVA.reset(Hazel::VertexArray::Create());
		float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr< Hazel::VertexBuffer> squareVB;
		squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Hazel::BufferLayout squareVBLayout = {
			{ Hazel::ShaderDataType::Float3, "a_Position"}
		};
		squareVB->SetLayout(squareVBLayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr< Hazel::IndexBuffer> squareIB;
		squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
	
		)";

		m_Shader.reset(new  Hazel::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
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

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
	
		)";

		m_BlueShader.reset(new  Hazel::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		HZ_TRACE("Delta time: {0}s ({1})", ts.GetSeconds(), ts.GetMilliseconds());
		//HZ_INFO("ExampleLayer::Update");
		//输入轮询，在任何时候我们都可以获得鼠标键盘的输入情况
		//而不是在之前在鼠标键盘输入时设置event
		

		//我们希望movement is timebased rather framesbased 


		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		//grey
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();
		//move camera up and right, scene will move down and left
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);


		Hazel::Renderer::Submit(m_BlueShader, m_SquareVA);


		Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();

	}

	void OnEvent(Hazel::Event& event) override
	{

	}


private:

	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;


	std::shared_ptr<Hazel::VertexArray> m_SquareVA;
	std::shared_ptr<Hazel::Shader> m_BlueShader;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f;
	float m_CameraSpeed = 0.1f;
	float m_CameraMoveSpeed = 1.0f;
};


class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//现在ImguiLayer将由Hazel生成时自动添加
		//PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}