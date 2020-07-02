#pragma once
#include <OSource.h>
unsigned int FBO, TCB, RBO;
OSource::Camera camera = OSource::Camera(-1.6f, 1.6f, -0.9, 0.9);
OSource::Timestep Timestep = OSource::Timestep();
float movementSpeed = 2.5f;
namespace EditorGL {
	extern void Genframebuffers() {
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &TCB);
		glBindTexture(GL_TEXTURE_2D, TCB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TCB, 0);

		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			OS_CORE_ERROR("Framebuffer is not complete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		OS_CORE_INFO(TCB);
	}
	extern void Bindframebuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	extern void Unbindframebuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
class LayerEditor : public OSource::Layer {
public:
	virtual void OnRun() override {
	}
	virtual void OnRender() override {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		ImGui::Begin("Viewport");
		ImGui::Image((void*)TCB, ImVec2(640, 360));
		ImGui::End();
		ImGui::End();
	}
	virtual void HandleInput(OSource::Input& input) override {
		Timestep.Update();
		if (input.GetKey(GLFW_KEY_W)) {
			camera.Translate(vec2(0.0f, movementSpeed * Timestep.GetDeltatime()));
		}
		if (input.GetKey(GLFW_KEY_S)) {
			camera.Translate(vec2(0.0f, -movementSpeed * Timestep.GetDeltatime()));
		}
		if (input.GetKey(GLFW_KEY_A)) {
			camera.Translate(vec2(movementSpeed * Timestep.GetDeltatime(), 0.0f));
		}
		if (input.GetKey(GLFW_KEY_D)) {
			camera.Translate(vec2(-movementSpeed * Timestep.GetDeltatime(), 0.0f));
		}
	}
};

void OSource::OnLayersCreate() {
	OSource::Layer* l = new LayerEditor();
	OSource::AddLayer(l);
}