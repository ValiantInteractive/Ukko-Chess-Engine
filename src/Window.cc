#include "Window.hh"

Window::Window()
{
	// get monitor resolution
	// SDL_DisplayMode mode;
	// SDL_GetCurrentDisplayMode(0, &mode);

	// Set width and height
	width = 800;
	height = 600;

	// store screen sizes
	setSizes();

	// create window
	window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
							  SDL_WINDOW_RESIZABLE);

	// if window creation fails
	if (!window)
		std::cout << "Could not create window! " << SDL_GetError() << "\n";
	else
	{
		// create the renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer)
			std::cout << "Could not create renderer! " << SDL_GetError() << "\n";
		else
		{
			// set the renderer
			Renderer::set(renderer);
		}
	}
}

void Window::resize(SDL_Event e)
{
	switch (e.type)
	{
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				// get new screensize and set it accordingly
				SDL_GetWindowSize(window, &width, &height);
				setSizes();
			}
			break;
	}
}

void Window::setSizes() const
{
	Screen::setWidth(width);
	Screen::setHeight(height);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
}

