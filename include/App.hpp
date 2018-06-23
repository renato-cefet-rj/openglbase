#ifndef __APP_H__
#define __APP_H__

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#ifdef __LINUX__
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define AppNull (App*)0

typedef void (*DrawCallback)(glm::mat4 transform);

class App
{
	public:
		App(const char* title="Application", int width=1024, int height=400, bool oldOpenGL=false);
		virtual ~App();
		virtual bool run(DrawCallback callback);
		virtual void background(float r, float g, float b, float a = 1.0f);

	private:
		virtual void updatePerspectiveAndLookAtMatrix();
		void perspective(float perspectiveFieldOfView, float perspectiveNear, float perspectiveFar);
		void lookAt(glm::vec3 lookAtEye, glm::vec3 lookAtCenter, glm::vec3 lookAtUp);

		SDL_Window *window;
		SDL_GLContext context;
		bool canRun;
		glm::mat4 vp;

		/* LookAt Attributes */
		glm::vec3 lookAtEye;
		glm::vec3 lookAtCenter;
		glm::vec3 lookAtUp;

		/* Perspective Attributes */
		float perspectiveFieldOfView;
		float perspectiveAspect;
		float perspectiveNear;
		float perspectiveFar;

		glm::vec4 bgcolor;
};

#endif
