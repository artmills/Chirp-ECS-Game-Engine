#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>


// SDL communicates with the operating system to create a window.
// OpenGL communicates with the GPU to perform drawing calculations.
// Then OpenGL context allows the operating system to cede some control to OpenGL so that the window can be drawed on.


class Display
{
public:

	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void Clear(float r, float g, float b, float a);

	// we have two buffers: at any one instant, the window is rendered to one and OpenGL draws to another. swap between them to update the display while still displaying something at the same time.
	void Update();

	// TEMPORARY: later set up a real event system.
	void CloseWindow();

	bool IsClosed();

private:

	bool m_isClosed;

	// initialize SDL. might put this in a different class when wanting other SDL functionality.
	void InitializeSDL(int width, int height, const std::string& title);
	void DeInitializeSDL();

	// initialize GLEW.
	void InitializeGLEW();

	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	// Clean Up:
	void CleanUp();
};
