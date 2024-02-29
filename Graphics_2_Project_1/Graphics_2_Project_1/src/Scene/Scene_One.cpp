#include "Scene_One.h"
#include "../AppSettings.h"
#include "../GraphicsApplication.h"

Scene_One::Scene_One(GraphicsApplication* application)
{
	this->mApplication = application;
}

void Scene_One::Start()
{
	mMainCamera = new GameCamera();
	mMainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 65.0f);
	mMainCamera->transform.SetPosition(mApplication->listOfCameraTransforms[0]->position);
	mMainCamera->transform.SetRotation(mApplication->listOfCameraTransforms[0]->rotation);
	mMainCamera->applyPostProcessing = true;

	mCamController = new CameraController(mMainCamera);

#pragma region Lights

	for (int i = 0; i < mApplication->listOfLights.size(); i++)
	{
		Light* light = mApplication->listOfLights[i];
		light->InitializeLight(light->lightType);

		switch (light->lightType)
		{
		case Point:
			light->name = "Point Light";
			break;
		case Spot:
			light->name = "Spot Light";
			break;
		case Directional:
			light->name = "Directional Light";
			break;
		}
	}

#pragma endregion

#pragma region Models

	for (ModelData* modelData : mApplication->listOfModels)
	{
		if (modelData->shader == "Default")
		{
			modelData->model->shader = Renderer::GetInstance().defaultShader;
		}
		else if (modelData->shader == "AlphaBlend")
		{
			modelData->model->shader = Renderer::GetInstance().alphaBlendShader;
		}

		else if (modelData->shader == "AlphaCutOut")
		{
			modelData->model->shader = Renderer::GetInstance().alphaCutOutShader;
		}

		modelData->model->LoadModel(modelData->path);

		for (MaterialData* matData : modelData->materialData)
		{
			BaseMaterial* material = modelData->model->meshes[matData->index]->material;

			if (modelData->shader == "Default" || modelData->shader == "AlphaBlend" || modelData->shader == "ColorMask" ||
				modelData->shader == "UVAnim" || modelData->shader == "AlphaCutOut")
			{
				material->AsMaterial()->SetBaseColor(matData->color);
				material->AsMaterial()->textureTiling = matData->tiling;
				if (matData->diffusePath != "")
				{
					material->AsMaterial()->diffuseTexture = new Texture(matData->diffusePath);
				}
				if (matData->maskPath != "")
				{
					material->AsMaterial()->alphaMask = new Texture(matData->maskPath);
					material->AsMaterial()->useMaskTexture = true;
				}
			}
		}

	
	}

#pragma endregion

	SetUpSecurityCamera();
	SetUpSecurityMonitor();

}

void Scene_One::Update()
{
}

void Scene_One::Render()
{
}

void Scene_One::SetUpSecurityCamera()
{
	mSecurityCamera1 = new GameCamera();
	mSecurityCamera1->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 65.0f);
	mSecurityCamera1->transform.SetPosition((mApplication->listOfCameraTransforms[5]->position));
	mSecurityCamera1->transform.SetRotation((mApplication->listOfCameraTransforms[5]->rotation));
	mSecurityCamera1->SetRenderTexture(new RenderTexture());
	mSecurityCamera1->name = "Security Camera 1";
	mSecurityCamera1->applyPostProcessing = true;
	mSecurityCamera1->postProcessing->bloom.isEnabled = true;

	mSecurityCamera2 = new GameCamera();
	mSecurityCamera2->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 65.0f);
	mSecurityCamera2->transform.SetPosition((mApplication->listOfCameraTransforms[2]->position));
	mSecurityCamera2->transform.SetRotation((mApplication->listOfCameraTransforms[2]->rotation));
	mSecurityCamera2->SetRenderTexture(new RenderTexture());
	mSecurityCamera2->name = "Security Camera 2";
	mSecurityCamera2->applyPostProcessing = true;
	mSecurityCamera2->postProcessing->chromaticAberration.isEnabled = true;

	mSecurityCamera3 = new GameCamera();
	mSecurityCamera3->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 65.0f);
	mSecurityCamera3->transform.SetPosition((mApplication->listOfCameraTransforms[3]->position));
	mSecurityCamera3->transform.SetRotation((mApplication->listOfCameraTransforms[3]->rotation));
	mSecurityCamera3->SetRenderTexture(new RenderTexture());
	mSecurityCamera3->name = "Security Camera 3";
	mSecurityCamera3->applyPostProcessing = true;
	mSecurityCamera3->postProcessing->heatDistortion.isEnabled = true;
	mSecurityCamera3->postProcessing->heatDistortion.mAmount = 2.5f;

	mSecurityCamera4 = new GameCamera();
	mSecurityCamera4->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 500.0f, 65.0f);
	mSecurityCamera4->transform.SetPosition((mApplication->listOfCameraTransforms[7]->position));
	mSecurityCamera4->transform.SetRotation((mApplication->listOfCameraTransforms[7]->rotation));
	mSecurityCamera4->SetRenderTexture(new RenderTexture());
	mSecurityCamera4->name = "Security Camera 4";
	mSecurityCamera4->applyPostProcessing = true;
	mSecurityCamera4->postProcessing->nightVision.isEnabled = true;

}

void Scene_One::SetUpSecurityMonitor()
{
	mMonitor = new Model("Assets/Models/Monitor.fbx");
	mMonitor->name = "Monitor";
	mMonitor->transform.SetPosition(glm::vec3(-37.9f, 34.5f, -86.5f));
	mMonitor->transform.SetRotation(glm::vec3(-90.0f, 180.0f, 0));
	mMonitor->transform.SetScale(glm::vec3(50));


	mQuad1 = new Model("res/Models/DefaultQuad.fbx");
	mQuad1->name = "Quad 1";
	mQuad1->transform.SetPosition(glm::vec3(-32.5f, 44.5f, -87.8f));
	mQuad1->transform.SetScale(glm::vec3(-4.9f, -2.65f, 2.65f));
	mQuad1->meshes[0]->material->AsMaterial()->diffuseTexture = mSecurityCamera2->renderTexture;

	mQuad2 = new Model();
	mQuad2->CopyFromModel(*mQuad1, true);
	mQuad2->name = "Quad 2";
	mQuad2->transform.SetPosition(glm::vec3(-42.72f, 44.5f, -87.8f));
	mQuad2->meshes[0]->material->AsMaterial()->diffuseTexture = mSecurityCamera1->renderTexture;

	mQuad3 = new Model();
	mQuad3->CopyFromModel(*mQuad1, true);
	mQuad3->name = "Quad 3";
	mQuad3->transform.SetPosition(glm::vec3(-32.5f, 38.82f, -87.8f));
	mQuad3->meshes[0]->material->AsMaterial()->diffuseTexture = mSecurityCamera3->renderTexture;

	mQuad4 = new Model();
	mQuad4->CopyFromModel(*mQuad1, true);
	mQuad4->name = "Quad 4";
	mQuad4->transform.SetPosition(glm::vec3(-42.72f, 38.82f, -87.8f));
	mQuad4->meshes[0]->material->AsMaterial()->diffuseTexture = mSecurityCamera4->renderTexture;
}
