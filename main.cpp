#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <ctime>

#include "display.hpp"

#include "ecs/ecscomponent.hpp"
#include "ecs/ecscomponentarray.hpp"

#include "systems/objectfactory.hpp"
#include "systems/inputsystem.hpp"

int main()
{
	const int WIDTH = 80;
	const int HEIGHT = 80;
	const int FILL_PROBABILITY = 35;
	const int AFFINITY = 3;
	const float BLOCK_SIZE = 0.25f;
	const uint SMOOTH = (uint)0;
	const int SEED = 26;

	const int width = 1280;
	const int height = 920;
	Display display(width, height, "Chirp!");

	RenderSystem renderSystem(width, height);
	renderSystem.Start();

	PhysicsSystem physicsSystem;
	physicsSystem.Start();

	InputSystem inputSystem(&display);

	ObjectFactory factory(&renderSystem, &physicsSystem, &inputSystem);	

	factory.CreateEntity_Triangle();
	factory.CreateEntity_Moveable_Triangle();
	

	while (!display.IsClosed())
	{
		inputSystem.Update(0.15f);
		ECSComponentArray<InputComponent>& inputs = inputSystem.ExportInputs();

		physicsSystem.SynchronizeInputs(inputs);
		physicsSystem.Update(0.15f);

		inputSystem.ResetInputs();

		// test exporting:
		ECSComponentArray<TransformComponent>& transforms = physicsSystem.ExportTransforms();
		renderSystem.SynchronizeTransforms(transforms);

		renderSystem.Update(0.15f);

		display.Update();
	}

	std::cout << "End." << std::endl;
	return 0;
}
