#include "ExampleLayer.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
{
	m_VertexArray = CC3D::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	CC3D::Ref<CC3D::VertexBuffer> vertexBuffer = CC3D::VertexBuffer::Create(vertices, sizeof(vertices));
	CC3D::BufferLayout layout = {
		{ CC3D::ShaderDataType::Float3, "a_Position" },
		{ CC3D::ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	CC3D::Ref<CC3D::IndexBuffer> indexBuffer = CC3D::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));		m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = CC3D::VertexArray::Create();

	//TEXCOORD
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};


	CC3D::Ref<CC3D::VertexBuffer> squareVB = CC3D::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ CC3D::ShaderDataType::Float3, "a_Position" },
		{ CC3D::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	CC3D::Ref<CC3D::IndexBuffer> squareIB = CC3D::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));		m_SquareVA->SetIndexBuffer(squareIB);

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

	m_Shader = CC3D::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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
	m_FlatColorShader = CC3D::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	m_ShaderLibrary.Add(m_FlatColorShader);///add shader to shaderlib
	/// Draw Plate UV
	std::string UVShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string UVShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;


			void main()
			{
				color = vec4(v_TexCoord, 0.0, 1.0);
			}
		)";

	m_UVShader = CC3D::Shader::Create("UVColor", UVShaderVertexSrc, UVShaderFragmentSrc);
	m_ShaderLibrary.Add(m_UVShader);///add shader to shaderlib
	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = CC3D::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = CC3D::Texture2D::Create("assets/textures/ChernoLogo.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}


void ExampleLayer::OnUpdate(CC3D::Timestep ts) 
{
	///Log the delta time
	CC3D_TRACE("Delta time:{0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

	// Update
	m_CameraController.OnUpdate(ts);

	///model transform
	if (CC3D::Input::IsKeyPressed(CC3D_KEY_I))
	{
		m_SquareTransform.y += m_SquareMoveSpeed * ts;
	}
	else if (CC3D::Input::IsKeyPressed(CC3D_KEY_K))
	{
		m_SquareTransform.y -= m_SquareMoveSpeed * ts;
	}



	CC3D::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	CC3D::RenderCommand::Clear();



	CC3D::Renderer::BeginScene(m_CameraController.GetCamera());


	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	auto TestShader = m_ShaderLibrary.Get("UVColor");//find shader by name in shaderlibray

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);


	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			transform *= glm::translate(glm::mat4(1.0f), m_SquareTransform);
			CC3D::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	///draw uv
	glm::vec3 pos(1.5f, 0.0f, 0.0f);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	///CC3D::Renderer::Submit(m_UVShader, m_SquareVA, transform);//use shader to sumbit
	CC3D::Renderer::Submit(TestShader, m_SquareVA, transform);//sumbit by shaderlib
	auto textureShader = m_ShaderLibrary.Get("Texture");
	///draw texture
	m_Texture->Bind();
	CC3D::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	CC3D::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	//CC3D::Renderer::Submit(m_Shader, m_VertexArray);

	CC3D::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender() 
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(CC3D::Event& e)
{
	m_CameraController.OnEvent(e);
}