#include <OSource.h>
#include "EditorLayer.h"

class Editor : public OSource::Application{
public:
	OSource::Sprite s = OSource::Sprite(OSource::Texture("res/image.png"), "Hello");
	OSource::Sprite se = OSource::Sprite(OSource::Texture("res/image.png"), "Hellok");
	virtual void Run() override{
        EditorGL::Genframebuffers();
		s.SetRotation(45);
		EditorGL::AddSprite(&s);
		EditorGL::AddSprite(&se);
	}
	virtual void Render() override{
	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Editor();
}
