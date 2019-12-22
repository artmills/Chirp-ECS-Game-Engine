#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "loader.hpp"
#include "../ecs/ecssystem.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/meshcomponent.hpp"
#include "basicshader.hpp"
#include "../mathematics.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>

// renders all renderable objects.
// the render system needs a special case for when entities are added.
// adding an entity means that entity's model must be loaded to the GPU and given a
// VAO ID.
class RenderSystem : public ECSSystem
{
public:

	RenderSystem(uint width, uint height);
	
	// initilization function. equivalent to Start() in Unity. prepares data for when the system 
	// first starts.
	void Start() override;

	// update. main function for the system. runs every dt seconds.
	void Update(float dt) override;

	// register an entity by copying its components into the copies of the component
	// arrays.
	void RegisterEntity(uint entityID, TransformComponent& transform, MeshComponent& mesh);

	// delete an entity and its components.
	void DeregisterEntity(uint entityID);

	// delete a component.
	void DeleteComponent(ComponentType componentType, uint index) override;

	// synchronize arrays.
	void SynchronizeTransforms(ECSComponentArray<TransformComponent>& from);
	ECSComponentArray<TransformComponent>& ExportTransforms();

	// debug:
	void PrintArrays();

	
private:

	// hash map to keep track of entities and their components:
	std::unordered_map<uint, std::vector<int> > m_entities;	

	ECSComponentArray<TransformComponent> m_transforms;
	ECSComponentArray<MeshComponent> m_meshes;

	// rendering:
	BasicShader m_basicShader;

	void Render();
	void ClearScreen();

	void InitializeMesh(MeshComponent& mesh);
	void LoadMatrix(TransformComponent& transform);
	void Reset_VAO();

	
	// projection matrix:
	static float m_fieldOfViewRadians;
	static float m_nearPlane;
	static float m_farPlane;
	uint m_width = 800;
	uint m_height = 600;

	void CreatePerspectiveProjectionMatrix(glm::mat4& matrix, float fieldOfViewRadians, uint width, uint height, float nearPlane, float farPlane);
	glm::mat4 m_projectionMatrix;

	// debug:
	void PrintMatrix(glm::mat4& matrix);
};





















