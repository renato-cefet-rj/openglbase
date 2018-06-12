#include <App.hpp>

App::App(const char* title, int width, int height, bool oldOpenGL)
{
	this->window = (SDL_Window*) 0;
	this->canRun = false;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{		
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	if(oldOpenGL)
	{
		//OpenGL compatibility profile - deprecated functions are allowed
		SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}
	else
	{
		//OpenGL core profile - deprecated functions are disabled
		SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}

	this->window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);
	if(!this->window)
	{
		SDL_Log("Unable to create SDL window: %s", SDL_GetError());
		return;
	}

	this->context = SDL_GL_CreateContext(window);
	if(!context)
	{
		SDL_Log("Unable to create OPENGL context: %s", SDL_GetError());
		return;
	}

	glEnable(GL_DEPTH_TEST);
	SDL_ShowWindow(window);
	this->canRun = true;
}

App::~App()
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}


Uint32 timerCallback(Uint32 interval, void *param)
{
	SDL_Event event;
	SDL_UserEvent userevent;
	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;
	event.type = SDL_USEREVENT;
	event.user = userevent;
	SDL_PushEvent(&event);
	return interval;
}

bool App::run(DrawCallback callback)
{
	SDL_Event event;
	SDL_TimerID timerId;
	int quit = 0;

	if(!this->canRun)
	{
		return false;
	}
	timerId = SDL_AddTimer(40,timerCallback,NULL);

	while (!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = 1;
				break;
			}
			else if(event.type == SDL_USEREVENT)
			{
				callback();
				SDL_GL_SwapWindow(this->window);
			}
		}
	}
	SDL_RemoveTimer(timerId);
	return true;
}

