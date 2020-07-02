#pragma once
#include <OSource.h>
class LayerEditor : public OSource::Layer {
public:
	virtual void OnRun() override {
	}
	virtual void OnRender() override {
	}
	virtual void HandleInput(OSource::Input& input) override {
	}
};

void OSource::OnLayersCreate() {
	OSource::Layer* l = new LayerEditor();
	OSource::AddLayer(l);
}