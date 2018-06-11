#ifndef __APP_H__
#define __APP_H__

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#ifdef __LINUX__
#define USING_GLEW
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define AppNull (App*)0

typedef void (*DrawCallback)();

class App
{
	public:
		App(const char* title="Application", int width=800, int height=600, bool oldOpenGL=false);
		virtual ~App();
		virtual bool run(DrawCallback callback);

	private:
		SDL_Window *window;
		SDL_GLContext context;
		bool canRun;
};

#endif
