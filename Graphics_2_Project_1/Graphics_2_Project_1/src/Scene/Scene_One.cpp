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

}

void Scene_One::Update()
{
}

void Scene_One::Render()
{
}

void Scene_One::SetUpSecurityCamera()
{
	mMonitor = new Model("Assets/Models/Monitor.fbx");
	mMonitor->name = "Monitor";
	mMonitor->transform.SetPosition(glm::vec3(-37.9f, 34.5f, -86.5f));
	mMonitor->transform.SetRotation(glm::vec3(-90.0f,180.0f, 0));
	mMonitor->transform.SetScale(glm::vec3(50));
}
