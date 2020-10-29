#ifndef GRAPHICSSYSTEM_HPP
#define GRAPHICSSYSTEM_HPP
class GraphicsSystem {
	//	//GRAPHICS 
	//
	//	static const int gfxScreenWidth = SCREEN_WIDTH;
	//	static const int gfxScreenHeight = SCREEN_HEIGHT;
	//	SDL_Window* gfxWindow;
	//	SDL_Surface* gfxWindowSurface;
	//	//OpenGL
	//	SDL_GLContext gfxOpenGLContext;
	//
	//	// initialize sdl with the video subsystem initialization flags
	//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	//		std::cout << "SDL Init errror : " << SDL_GetError() << std::endl;
	//	}
	//
	//	// creating the window to render to with the necessary flags
	//	gfxWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gfxScreenWidth, gfxScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//	if (NULL == gfxWindow) {
	//		std::cout << "Error creating window : " << SDL_GetError() << std::endl;
	//		return(false);
	//	}
	//
	//	// set opengl version flags
	//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	//
	//	// setting the core profile doesn't allow us to use older deprecated functions 
	//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//
	//
	//	// creating the main sdl opengl context now
	//	gfxOpenGLContext = SDL_GL_CreateContext(gfxWindow);
	//
	//
	//	gfxWindowSurface = SDL_GetWindowSurface(gfxWindow);
	//
	//	// use glad loader to gain access to openGL calls - needed on windows only 
	//#ifdef _WIN32
	//	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	//#endif
	//
	//	// let's print out the OpenGL version info 
	//	std::cout << "GraphicsManager : gfxInit : OpenGL Version " << (char*)glGetString(GL_VERSION) << std::endl;
	//
	//	bool running = true;
	//	while (running) {
	//		SDL_Event Event;
	//		while (SDL_PollEvent(&Event))
	//		{
	//			if (Event.type == SDL_KEYDOWN)
	//			{
	//				switch (Event.key.keysym.sym)
	//				{
	//				case SDLK_ESCAPE:
	//					running = 0;
	//					break;
	//				default:
	//					break;
	//				}
	//			}
	//			else if (Event.type == SDL_QUIT)
	//			{
	//				running = 0;
	//			}
	//		}
	//		glViewport(0, 0, gfxScreenWidth, gfxScreenHeight);
	//		glClearColor(1.f, 0.f, 1.f, 0.f);
	//		glClear(GL_COLOR_BUFFER_BIT);
	//
	//		SDL_GL_SwapWindow(gfxWindow);
	//	}
	//
};
#endif