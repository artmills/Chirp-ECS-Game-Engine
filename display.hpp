#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>


// SDL communicates with the operating system to create a window.
// OpenGL communicates with the GPU to perform drawing calculations.
// Then OpenGL context allows the operating system to cede some control to OpenGL so that the window can be drawed on.


/**
 * Interface between SDL, OpenGL, and the OS.
 *
 * Manages the display of the game and is responsible for initializing SDL and OpenGL.
 * Contains an Update() method that should be called in the main game loop.
 */
class Display
{
public:

	/** Creates a display of resolution (width) * (height) with the given title. 
	 * Initializes both SDL and GLEW.
	 */
	Display(int width, int height, const std::string& title);

	/** Destructor. 
	 * Calls the CleanUp() method.
	 */
	virtual ~Display();

	/** Clears the display with the given RGBA color. */
	void Clear(float r, float g, float b, float a);

	/** 
	 * Swap buffers.
	 *
	 * At one instant, the window is rendered to one buffer while OpenGL renders to another.
	 * Swap between the buffers to update the display and display something at the same time.
	 */
	void Update();

	/** Closes the window, terminating the program. */
	void CloseWindow();

	/** Checks to see if the window has been closed. */
	bool IsClosed();

private:

	/** Keep track of whether the window has been closed. */
	bool isClosed;

	/** Initialize SDL with the given width, height, and title of the desired window. */
	void InitializeSDL(int width, int height, const std::string& title);

	/** Release resources that were used by SDL. */
	void DeInitializeSDL();

	/** Initialize GLEW for OpenGL. */
	void InitializeGLEW();

	/** The actual window object, managed by SDL. */
	SDL_Window* window;

	/** The OpenGL context that is the interface between the window and the operating system. */
	SDL_GLContext glContext;

	/** Don't forget to clean up! Release all resources. */
	void CleanUp();
};
