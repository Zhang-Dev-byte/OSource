#pragma once
#include <OSource.h>
class LayerSandbox : public OSource::Layer {
public:
	virtual void OnRun() override {
	}
	virtual void OnRender() override {
	}
	virtual void HandleInput(OSource::Input& input) override {
	}
};

void OSource::OnLayersCreate() {
	OSource::Layer* l = new LayerSandbox();
	OSource::AddLayer(l);
}