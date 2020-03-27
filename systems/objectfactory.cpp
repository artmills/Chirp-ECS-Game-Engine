#include "objectfactory.hpp"

ObjectFactory::ObjectFactory(RenderSystem* renderSystem, PhysicsSystem* physicsSystem, InputSystem* inputSystem)
{
	this->renderSystem = renderSystem;
	this->physicsSystem = physicsSystem;
	this->inputSystem = inputSystem;
}


void ObjectFactory::CreateEntity_Triangle()
{
	ECSEntity triangle;
	TransformComponent transform(triangle.getID(), 0, 0, -2.0f, 0, 0, 0);

	// create test model.
	Vertex v0(-0.5f, -0.3f, 0, 0.2f, 0.3f, 0.6f, 1.0);
	Vertex v1(0.5f, 0, 0, 0.6f, 0.2f, 0.2f, 1.0);
	Vertex v2(0, 0.5f, 0, 0.7f, 0.1f, 0.8f, 1.0);
	std::vector<Vertex> vertices { v0, v1, v2 };
	std::vector<uint> triangles { 0, 1, 2 };
	MeshComponent mesh(triangle.getID(), vertices, triangles);

	PhysicsComponent physics;

	triangle.giveComponent(ComponentType::Transform);
	triangle.giveComponent(ComponentType::Mesh);
	triangle.giveComponent(ComponentType::Physics);

	std::vector<BaseECSComponent*> components;
	components.push_back(static_cast<BaseECSComponent*>(&transform)); 
	components.push_back(static_cast<BaseECSComponent*>(&mesh)); 
	components.push_back(static_cast<BaseECSComponent*>(&physics)); 

	RegisterToSystems(triangle, components);
}

void ObjectFactory::CreateEntity_Moveable_Triangle()
{
	ECSEntity triangle;
	//TransformComponent transform(triangle.getID(), 0, 0, 0, 0, 0, 0);
	TransformComponent transform(triangle.getID(), 0, 0, -2.0f, 0, 0, 0);

	// create test model.
	Vertex v0(-0.5f, -0.3f, 0, 0.2f, 0.3f, 0.6f, 1.0);
	Vertex v1(0.5f, 0, 0, 0.6f, 0.2f, 0.2f, 1.0);
	Vertex v2(0, 0.5f, 0, 0.7f, 0.1f, 0.8f, 1.0);
	std::vector<Vertex> vertices { v0, v1, v2 };
	std::vector<uint> triangles { 0, 1, 2 };
	MeshComponent mesh(triangle.getID(), vertices, triangles);

	PhysicsComponent physics;

	triangle.giveComponent(ComponentType::Transform);
	triangle.giveComponent(ComponentType::Mesh);
	triangle.giveComponent(ComponentType::Physics);

	InputComponent input;
	triangle.giveComponent(ComponentType::Input);

	std::vector<BaseECSComponent*> components;
	components.push_back(static_cast<BaseECSComponent*>(&transform)); 
	components.push_back(static_cast<BaseECSComponent*>(&mesh)); 
	components.push_back(static_cast<BaseECSComponent*>(&physics)); 
	components.push_back(static_cast<BaseECSComponent*>(&input)); 

	RegisterToSystems(triangle, components);
}



void ObjectFactory::CreateTerrain(int xChunks, int yChunks, int width, int height, float xT, float yT, float zT, float blockSize, int percent, int affinity, int smooth)
{
	// 1) get a total grid for the entire terrain.
	GridComponent globalGrid = TerrainFactory::CA(xChunks * width, yChunks * height, percent, affinity, smooth);

	// 2) create each chunk with a grid and mesh component.
	for (int x = 0; x < xChunks; ++x)
	{
	for (int y = 0; y < yChunks; ++y)
	{
		ECSEntity chunk;
		
		// a) create the grid for this chunk.
		GridComponent grid(width, height);
		for (int i = 0; i < width; ++i)
		{
		for (int j = 0; j < height; ++j)
		{
			grid.setElement(i, j, globalGrid.getElement(x * width + i, y * height + j));	
		}
		}

		/*grid.Print();
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;*/

		// b) get the mesh for this chunk.
		MeshComponent mesh = TerrainFactory::ConvertToMesh(chunk.getID(), grid, blockSize);

		// c) get the transform for this chunk.
		float xPosition = xT + blockSize * (x * width);
		float yPosition = yT + blockSize * (y * height);
		TransformComponent transform(chunk.getID(), xPosition, yPosition, zT, 0, 0, 0); 

		// d) add these components to the chunk.
		chunk.giveComponent(ComponentType::Grid);	
		chunk.giveComponent(ComponentType::Mesh);	
		chunk.giveComponent(ComponentType::Transform);	
		
		// e) register to systems.
		std::vector<BaseECSComponent*> components;
		components.push_back(static_cast<BaseECSComponent*>(&transform));
		components.push_back(static_cast<BaseECSComponent*>(&mesh));
		components.push_back(static_cast<BaseECSComponent*>(&grid));
		RegisterToSystems(chunk, components);
	}
	}
}

void ObjectFactory::RegisterToSystems(ECSEntity& entity, std::vector<BaseECSComponent*>& components)
{
	// this might just have to be a giant switch on the component array in ECSEntity.

	// meshes:
	if (entity.hasComponent(ComponentType::Mesh))
	{
		// mesh + transform:
		if (entity.hasComponent(ComponentType::Transform))
		{
			renderSystem->RegisterEntity(
					entity.getID(),
					*static_cast<TransformComponent*>(components[0]),
					*static_cast<MeshComponent*>(components[1]));
		}
	}

	// transforms:
	if (entity.hasComponent(ComponentType::Transform))
	{
		// transform + physics:
		if (entity.hasComponent(ComponentType::Physics))
		{
			// transform + physics + input:
			if (entity.hasComponent(ComponentType::Input))
			{
				std::cout << "Entity with input." << std::endl;
				physicsSystem->RegisterEntity(
						entity.getID(),
						*static_cast<TransformComponent*>(components[0]),
						*static_cast<PhysicsComponent*>(components[2]),
						*static_cast<InputComponent*>(components[3]));
				
				inputSystem->RegisterEntity(
						entity.getID(),
						*static_cast<InputComponent*>(components[3]));
			}
			
			// no input:
			else 
			{
				std::cout << "Entity with NO input." << std::endl;
				physicsSystem->RegisterEntity(
						entity.getID(),
						*static_cast<TransformComponent*>(components[0]),
						*static_cast<PhysicsComponent*>(components[2]));
			}
		}
	}
}





















