#include <OSource.h>

class Sandbox : public OSource::Application{
public:
	virtual void Run() override{
	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Sandbox();
}