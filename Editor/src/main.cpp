#include <OSource.h>
#include "EditorLayer.h"

class Editor : public OSource::Application{
public:
	OSource::Sprite s = OSource::Sprite(OSource::Texture("res/image.png"), "Hello");
	virtual void Run() override{
        EditorGL::Genframebuffers();
		s.SetRotation(45);
		EditorGL::AddSprite(&s);
	}
	virtual void Render() override{
	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Editor();
}
