#pragma once
#include <OSource.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>

unsigned int FBO, TCB, RBO;
OSource::Camera camera = OSource::Camera(-1.6f, 1.6f, -0.9, 0.9);
OSource::Timestep Timestep = OSource::Timestep();
std::string jsondir = "Info/js/ObjectNotation/Json/Serialized";
std::vector<OSource::Sprite*> sprites = std::vector<OSource::Sprite*>();
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
	}
	extern void Bindframebuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	extern void Unbindframebuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	extern void AddSprite(OSource::Sprite* sprite) {
		sprites.push_back(sprite);
	}
	extern std::string StringToHex(const std::string& in) {
		std::stringstream ss;

		ss << std::hex << std::setfill('0');
		for (size_t i = 0; in.length() > i; ++i) {
			ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
		}

		return ss.str();
	}

	extern std::string HexToString(const std::string& in) {
		std::string output;

		if ((in.length() % 2) != 0) {
			throw std::runtime_error("Invalid string length...");
		}

		size_t cnt = in.length() / 2;

		for (size_t i = 0; cnt > i; ++i) {
			uint32_t s = 0;
			std::stringstream ss;
			ss << std::hex << in.substr(i * 2, 2);
			ss >> s;

			output.push_back(static_cast<unsigned char>(s));
		}

		return output;
	}
}
class LayerEditor : public OSource::Layer {
public:
	OSource::Sprite& ssprite = OSource::Sprite(OSource::Texture(""), "");
	float spos[2];
	float sscale[2];
	float srot;
	virtual void OnRun() override {
		std::cout << EditorGL::HexToString(EditorGL::StringToHex("hello")) << std::endl;
	}
	virtual void OnRender() override {
		EditorGL::Bindframebuffer();
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto i = sprites.begin(); i != sprites.end(); i++) {
			OSource::Sprite& r = **i;
			r.Render(camera);
		}

		EditorGL::Unbindframebuffer();
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);


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
		ImGui::Image((void*)TCB, ImVec2(1280 / 1.7f, 720 / 1.7f));
		ImGui::End();

		ImGui::Begin("Scene");
		OSource::Sprite& r = OSource::Sprite(OSource::Texture(""), "");
		for (auto i = sprites.begin(); i != sprites.end(); i++) {
			r = **i;
			if(ImGui::Button(r.GetName(), ImVec2(100, 20))){
				ssprite = r;
				spos[0] = ssprite.GetPosition().x;
				spos[1] = ssprite.GetPosition().y;

				sscale[0] = ssprite.GetScale().x;
				sscale[1] = ssprite.GetScale().y;

				srot = ssprite.GetRotation();
			}
		}
		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::Text(ssprite.GetName());
		ImGui::InputFloat2("Position", spos);
		ImGui::InputFloat2("Scale", sscale);
		ImGui::InputFloat("Rotation", &srot);
		if(ImGui::Button("Delete", ImVec2(100, 20))) {
			for (int i = 0; i < sprites.size(); i++) {
				OSource::Sprite* p = sprites[i];
				OSource::Sprite& r = *p;
				if (r.GetName() == ssprite.GetName()) {
					sprites.erase(sprites.begin() + i);
					ssprite = OSource::Sprite(OSource::Texture(""), "");

					spos[0] = 0;
					spos[1] = 0;

					sscale[0] = 0;
					sscale[1] = 0;

					srot = 0;
				}
			}
		}
		ImGui::End();
		ssprite.SetPosition(vec2(spos[0], spos[1]));
		ssprite.SetScale(vec2(sscale[0], sscale[1]));
		ssprite.SetRotation(srot);
		for (auto i = sprites.begin(); i != sprites.end(); i++) {
			OSource::Sprite& r = **i;
			if (r.GetName() == ssprite.GetName()) {
				r = ssprite;
			}
		}
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