#include "display.hpp"

Display::Display(int width, int height, const std::string& title)
{
	InitializeSDL(width, height, title);
	InitializeGLEW();
}
Display::~Display()
{
	CleanUp();
}

// display methods:

void Display::CloseWindow()
{
	isClosed = true;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Display::IsClosed()
{
	return isClosed;
}

void Display::Update()
{
	// swap buffers.
	SDL_GL_SwapWindow(window);

	// check for updates.
	/*SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}*/
}

void Display::InitializeSDL(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// set extra OpenGL attributes for the window.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 2^8 different shades of red (256).
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 2^8 different shades of green (256).
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // 2^8 different shades of blue (256).
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 2^8 different shades of alpha (256).
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // how much minimum data (bits) for a single pixel. since we have 4 * 8 bits for color, we can use 32 here.  
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // double buffering for swap buffers. 

	// can choose where on the monitor screen to create the window.
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	// create the context.
	glContext = SDL_GL_CreateContext(window);
}

void Display::DeInitializeSDL()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::InitializeGLEW()
{
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "ERROR: GLEW failed to initialize. " << std::endl;
	}
	
	isClosed = false;
}

void Display::CleanUp()
{
	DeInitializeSDL();
}
