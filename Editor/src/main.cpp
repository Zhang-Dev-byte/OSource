#include <OSource.h>
#include "EditorLayer.h"

class Editor : public OSource::Application{
public:
	OSource::Camera cam = OSource::Camera(-1.6f, 1.6f, -0.9, 0.9);
	OSource::Sprite s = OSource::Sprite(OSource::Texture("res/image.png"), "Hello");
	virtual void Run() override{
        EditorGL::Genframebuffers();
		s.SetRotation(45);
	}
	virtual void Render() override{
        s.SetRotation(90);
        EditorGL::Bindframebuffer();
		s.Render(cam);
        EditorGL::Unbindframebuffer();
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Editor();
}
