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

	this->window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

	this->perspectiveAspect = (1.0f*width)/height;
	this->lookAt(glm::vec3(0.0f,0.0f,10.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
	this->perspective(glm::radians(45.0f),0.1f,100.0f);
	glEnable(GL_DEPTH_TEST);
	this->canRun = true;

	this->bgcolor.r = 0.3f;
	this->bgcolor.g = 0.6f;
	this->bgcolor.b = 0.3f;
	this->bgcolor.a = 1.0f;
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

void App::updatePerspectiveAndLookAtMatrix()
{
	glm::mat4 projection = glm::perspective(this->perspectiveFieldOfView,this->perspectiveAspect,this->perspectiveNear,this->perspectiveFar);
	glm::mat4 view = glm::lookAt(this->lookAtEye,this->lookAtCenter,this->lookAtUp);
	this->vp = projection * view;
}

void App::perspective(float perspectiveFieldOfView, float perspectiveNear, float perspectiveFar)
{
	this->perspectiveFieldOfView = perspectiveFieldOfView;
	this->perspectiveNear = perspectiveNear;
	this->perspectiveFar = perspectiveFar;
	this->updatePerspectiveAndLookAtMatrix();
}

void App::lookAt(glm::vec3 lookAtEye, glm::vec3 lookAtCenter, glm::vec3 lookAtUp)
{
	this->lookAtEye = lookAtEye;
	this->lookAtCenter = lookAtCenter;
	this->lookAtUp = lookAtUp;
	this->updatePerspectiveAndLookAtMatrix();
}

bool App::run(DrawCallback callback)
{
	GLfloat depth[] = { 1.0 };
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
				glClearBufferfv(GL_COLOR, 0, &this->bgcolor[0]);
				glClearBufferfv(GL_DEPTH, 0, depth);
				callback(this->vp);
				SDL_GL_SwapWindow(this->window);
			}

			else if (event.type == SDL_WINDOWEVENT) 
			{
				if(event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					int width = event.window.data1;
					int height = event.window.data2;
					glViewport(0,0,(GLsizei)width,(GLsizei)height);
					this->perspectiveAspect = ((1.0f)*width)/height;
					this->updatePerspectiveAndLookAtMatrix();
				}
			}

			else if( event.type == SDL_KEYDOWN ) 
			{ 
				if(event.key.keysym.sym == SDLK_UP)
				{
				}
				else if(event.key.keysym.sym == SDLK_DOWN)
				{
				}
				else if(event.key.keysym.sym == SDLK_LEFT)
				{
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{
				}
			}

			else if( event.type == SDL_MOUSEMOTION ) 
			{ 
				SDL_Log("Mouse Position %dx%d", event.motion.x, event.motion.y);
			}

			else if( event.type == SDL_MOUSEBUTTONDOWN ) 
			{ 
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					SDL_Log("Left Button clicked");
				}
			}
		}
	}
	SDL_RemoveTimer(timerId);
	return true;
}

void App::background(float r, float g, float b, float a)
{
	this->bgcolor.r = r;
	this->bgcolor.g = g;
	this->bgcolor.b = b;
	this->bgcolor.a = a;
}
