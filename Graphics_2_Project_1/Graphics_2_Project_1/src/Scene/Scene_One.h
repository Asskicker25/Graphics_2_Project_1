#pragma once

#include <Graphics/Scene/BaseScene.h>
#include <Graphics/GameCamera.h>

using namespace Scene;

class GraphicsApplication;

class Scene_One : public BaseScene
{
public:

	Scene_One(GraphicsApplication* application);

	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
	
private:
	GraphicsApplication* mApplication = nullptr;
	GameCamera* mMainCamera = nullptr;
};

