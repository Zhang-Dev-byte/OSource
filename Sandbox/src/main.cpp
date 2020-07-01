#include <iostream>
#include <OSource.h>

class Sandbox : public OSource::Application{
public:
	virtual void Run() override{
		
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Sandbox();
}