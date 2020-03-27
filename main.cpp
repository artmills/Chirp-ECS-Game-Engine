#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <ctime>

#include "display.hpp"

#include "ecs/ecscomponent.hpp"
#include "ecs/ecscomponentarray.hpp"

#include "systems/objectfactory.hpp"
#include "systems/inputsystem.hpp"

#include "systems/terrainfactory.hpp"

int main()
{
	const int width = 1280;
	const int height = 920;
	Display display(width, height, "Chirp!");

	RenderSystem renderSystem(width, height);
	renderSystem.Start();

	PhysicsSystem physicsSystem;
	physicsSystem.Start();

	InputSystem inputSystem(&display);

	ObjectFactory factory(&renderSystem, &physicsSystem, &inputSystem);	

	//factory.CreateEntity_Triangle();
	factory.CreateEntity_Moveable_Triangle();

	factory.CreateTerrain(3, 3, 100, 100, -50, -50, -100, 0.25f, 35, 3, 2);
	//factory.CreateTerrain(4, 4, 100, 100, -25, -25, -50, 0.25f, 35, 3, 2);

	int i = 0;
	const float UPDATE = 0.15f;

	while (!display.IsClosed())
	{
		inputSystem.Update(UPDATE);
		ECSComponentArray<InputComponent>& inputs = inputSystem.ExportInputs();

		physicsSystem.SynchronizeInputs(inputs);
		physicsSystem.Update(UPDATE);

		inputSystem.ResetInputs();

		// test exporting:
		ECSComponentArray<TransformComponent>& transforms = physicsSystem.ExportTransforms();
		renderSystem.SynchronizeTransforms(transforms);

		renderSystem.Update(UPDATE);
		display.Update();

		//++i;
		//std::cout << i << std::endl;
	}
	
	std::cout << "End." << std::endl;
	return 0;
}
