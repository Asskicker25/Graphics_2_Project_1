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
	void SetUpSecurityMonitor();

	GraphicsApplication* mApplication = nullptr;
	CameraController* mCamController = nullptr;

	GameCamera* mMainCamera = nullptr;
	GameCamera* mSecurityCamera1 = nullptr;
	GameCamera* mSecurityCamera2 = nullptr;
	GameCamera* mSecurityCamera3 = nullptr;
	GameCamera* mSecurityCamera4 = nullptr;

	Model* mMonitor = nullptr;
	Model* mQuad1 = nullptr;
	Model* mQuad2 = nullptr;
	Model* mQuad3 = nullptr;
	Model* mQuad4 = nullptr;

};

