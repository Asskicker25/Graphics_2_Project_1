#pragma once
#include <Graphics/ApplicationWindow.h>
#include "Scene/Scene_One.h"

struct MaterialData
{
	int index;
	glm::vec4 color;
	glm::vec2 tiling;

	std::string diffusePath;
	std::string maskPath;

	MaterialData(int index)
	{
		this->index = index;
		color = glm::vec4(1.0);
		tiling = glm::vec2(1.0);
		diffusePath = "";
		maskPath = "";
	}
};

struct ModelData
{
	Model* model;
	std::string path;
	std::string shader;
	std::vector<MaterialData* > materialData;

	ModelData()
	{
		model = new Model();
		shader = "Default";
	}

	MaterialData* GetMaterialData(int index)
	{
		for (MaterialData* mat : materialData)
		{
			if (mat->index == index)
				return mat;
		}

		return nullptr;
	}
};


class GraphicsApplication : public ApplicationWindow
{
public:
	Scene_One* sceneOne = nullptr;

	std::vector<ModelData*> listOfModels;
	std::vector<Light*> listOfLights;
	std::vector<Transform*> listOfCameraTransforms;

	int cameraPresetIndex = 0;
	bool loadAsync = false;

	// Inherited via ApplicationWindow
	void SetUp() override;
	void Update() override;
	void Render() override;
	void Shutdown() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;

	// Inherited via ApplicationWindow
	void OnPlayStateChanged(bool state) override;
};

