#pragma once

#include "CC3D.h"

class Sandbox2D : public CC3D::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	/// <summary>
	/// Test Rendering Scenes from lectures
	/// </summary>
	void TestDraw();
	void TestDraw44();
	void TestDraw45();
	void TestDraw46(CC3D::Timestep ts);
	void TestDraw47();

	void OnUpdate(CC3D::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void DockSpaceDemo();
	/// <summary>
	/// visualization functions using imgui
	/// </summary>
	void ProfileVisual();
	void RenderStatusVisual();

	void OnEvent(CC3D::Event& e) override;
private:
	CC3D::OrthographicCameraController m_CameraController;
	
	// Temp
	CC3D::Ref<CC3D::VertexArray> m_SquareVA;
	CC3D::Ref<CC3D::Shader> m_FlatColorShader;
	CC3D::Ref<CC3D::Texture2D> m_CheckerboardTexture;
	CC3D::Ref<CC3D::Framebuffer> m_Framebuffer;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	//profiling
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

};