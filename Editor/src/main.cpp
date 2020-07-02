#include <OSource.h>
#include "SandboxLayer.h"

class Editor : public OSource::Application{
public:
	OSource::Camera cam = OSource::Camera(-1.6f, 1.6f, -0.9, 0.9);
	OSource::Sprite s = OSource::Sprite(OSource::Texture("res/image.png"), "Hello");
	virtual void Run() override{
		s.SetRotation(45);
	}
	virtual void Render() override{
		s.Render(cam);
	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Editor();
}
