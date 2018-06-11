#include <App.hpp>
#include <Shader.hpp>
#include <Cube.hpp>

App *app = AppNull;
Shader *shader = ShaderNull;
Cube *cube = CubeNull;

void init()
{
	app = new App();
	shader = new Shader("vertexAndColorShader");
	cube = new Cube();
}

float angle = 0;

void draw()
{
	glm::mat4 projection, view, model;

	GLfloat color[] = { 0.3f, 0.6f, 0.3f, 1.0f };
	GLfloat depth[] = { 1.0 };
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, depth);

	projection = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);
	view = glm::lookAt(glm::vec3(0.0f,0.0f,10.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
	model = glm::translate(glm::mat4(1.0f),glm::vec3(3.0f,2.0f,0.0f));
	model = glm::rotate(model,angle+=0.02,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(projection*view*model);
	cube->draw();

	model = glm::translate(glm::mat4(1.0f),glm::vec3(-3.0f,2.0f,0.0f));
	model = glm::rotate(model,angle,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(projection*view*model);
	cube->draw();

	model = glm::translate(glm::mat4(1.0f),glm::vec3(-3.0f,-2.0f,0.0f));
	model = glm::rotate(model,angle,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(projection*view*model);
	cube->draw();

	model = glm::translate(glm::mat4(1.0f),glm::vec3(3.0f,-2.0f,0.0f));
	model = glm::rotate(model,angle,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(projection*view*model);
	cube->draw();
}

void end()
{
	delete cube;	
	delete shader;
	delete app;
}

int main(int argc, char**argv)
{
	init();
	app->run(draw);
	end();
	return 0;
}
