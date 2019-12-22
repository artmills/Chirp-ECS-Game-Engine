#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
#include <SDL2/SDL.h>

#include "../components/inputcomponent.hpp"
#include "../ecs/ecscomponentarray.hpp"
#include "../display.hpp"

// for convenience:
enum Direction
{
	horizontal = 0,
	vertical,
	depth
};

// handles input events, including both global key events and user-specific inputs.
class InputSystem
{

public:

	InputSystem(Display* display);

	void RegisterEntity(uint entityID, InputComponent& input);
	
	void Update(float dt);

	// system communication:
	void SynchronizeInputs(ECSComponentArray<InputComponent>& from);
	ECSComponentArray<InputComponent>& ExportInputs();

	// reset inputs:
	void ResetInputs();

private:

	// temporary: later implement a real event system.
	void SendMessage_Quit();
	Display* m_display = nullptr;

	// components:
	std::unordered_map<uint, std::vector<int> > m_entities;	
	ECSComponentArray<InputComponent> m_inputComponents;

	// apply the input data to the components:
	void SetInputs(Direction direction, float value);

};





/* SDL INPUT EVENT NOTES:
 *
 * enum SDL_Keycode:
 * represents a key. defined as "SDLK_a", "SDLK_SPACE", etc.
 *
 * enum SDL_Keymod:
 * represents a modifier key, such as "KMOD_NUM", "KMOD_RCTRL", etc.
 *
 * struct SDL_Keysym:
 * contains key information for a key event, including keycode and keymod.
 *
 * union SDL_Event:
 * union of all event structures, such as "SDL_KeyboardEvent", "SDL_MouseMotionEvent", etc
 * the "type" field lets us know which struct has been placed in the union.
 * to get the proper event, take a switch on SDL_Event.type.
 *
 * enum SDL_EventType:
 * represents a key event, such as "SDL_KEYDOWN" or "SDL_MOUSEMOTION" or "SDL_QUIT".
 * these are the cases for SDL_Event.type.
 *
 * function SDL_PollEvent(SDL_Event*): takes events from an event queue and stores them in the SDL_Event object.
 * always call this function on the same thread that initialized SDL.
 */































