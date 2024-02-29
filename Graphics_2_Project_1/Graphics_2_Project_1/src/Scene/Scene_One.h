#pragma once

#include <Graphics/Scene/BaseScene.h>
#include <Graphics/GameCamera.h>
#include "../Camera/CameraController.h"


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

	void SetUpSecurityCamera();

	GraphicsApplication* mApplication = nullptr;
	GameCamera* mMainCamera = nullptr;
	CameraController* mCamController = nullptr;

	Model* mMonitor = nullptr;

};

