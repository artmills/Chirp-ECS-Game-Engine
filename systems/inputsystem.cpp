#include "inputsystem.hpp"

InputSystem::InputSystem(Display* display) : m_display(display) {}

// later it might be worth throwing the switch into its own function. but PollEvent()
// seems to take in all events at once. this might be problematic if a huge number of
// events are polled in a single frame. 
void InputSystem::Update(float dt)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_EventType::SDL_QUIT:
				SendMessage_Quit();	

			case SDL_EventType::SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_w)
				{
					//std::cout << "w has been pressed." << std::endl;
					SetInputs(Direction::vertical, 1);
				}
				else if (e.key.keysym.sym == SDLK_s)
				{
					//std::cout << "s has been pressed." << std::endl;
					SetInputs(Direction::vertical, -1);
				}
				if (e.key.keysym.sym == SDLK_a)
				{
					SetInputs(Direction::horizontal, -1);
					//std::cout << "a has been pressed." << std::endl;
				}
				else if (e.key.keysym.sym == SDLK_d)
				{
					SetInputs(Direction::horizontal, 1);
					//std::cout << "d has been pressed." << std::endl;
				}
				if (e.key.keysym.sym == SDLK_t)
				{
					SetInputs(Direction::depth, 1);
				}
				else if (e.key.keysym.sym == SDLK_g)
				{
					SetInputs(Direction::depth, -1);
				}
				break;
			default:
				break;
		}
		
	}
}

void InputSystem::ResetInputs()
{
	for (uint i = 0; i < m_inputComponents.NumberOfComponents(); i++)
	{
		m_inputComponents.getComponent(i)->Reset();
	}
}

void InputSystem::RegisterEntity(uint entityID, InputComponent& input)
{
	// add the relevant components of the entity to the proper arrays.
	int inputHandle = m_inputComponents.AddComponent(input);

	// register the handles for these components to the hash map.
	std::vector<int> handles { inputHandle }; 
	m_entities.emplace(entityID, handles);

	std::cout << "Registering entity with input: " << inputHandle << std::endl;
}

void InputSystem::SetInputs(Direction direction, float value)
{
	// go through the component array, setting the proper input values.
	for (uint i = 0; i < m_inputComponents.NumberOfComponents(); i++)
	{
		InputComponent* input = m_inputComponents.getComponent(i);
		if (input != nullptr)
		{
			switch (direction)
			{
				case Direction::horizontal:
					input->setHorizontalMotion(value);
					break;
				case Direction::vertical:
					input->setVerticalMotion(value);
					break;
				case Direction::depth:
					input->setDepthMotion(value);
				default:
					break;

			}
		}
	}
}

void InputSystem::SynchronizeInputs(ECSComponentArray<InputComponent>& from)
{
	m_inputComponents.TrustCopyFrom(from);	
}

ECSComponentArray<InputComponent>& InputSystem::ExportInputs()
{
	return m_inputComponents;
}

void InputSystem::SendMessage_Quit()
{
	m_display->CloseWindow();
}















