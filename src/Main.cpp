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

void draw(glm::mat4 vp)
{
	glm::mat4 model;

	GLfloat color[] = { 0.3f, 0.6f, 0.3f, 1.0f };
	GLfloat depth[] = { 1.0 };
	glClearBufferfv(GL_COLOR, 0, color);
	glClearBufferfv(GL_DEPTH, 0, depth);

	model = glm::translate(glm::mat4(1.0f),glm::vec3(3.0f,2.0f,0.0f));
	model = glm::rotate(model,angle+=0.05,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(vp*model);
	cube->draw();

	model = glm::translate(glm::mat4(1.0f),glm::vec3(-3.0f,2.0f,0.0f));
	model = glm::rotate(model,angle,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(vp*model);
	cube->draw();

	model = glm::translate(glm::mat4(1.0f),glm::vec3(-3.0f,-2.0f,0.0f));
	model = glm::rotate(model,angle,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(vp*model);
	cube->draw();

	model = glm::translate(glm::mat4(1.0f),glm::vec3(3.0f,-2.0f,0.0f));
	model = glm::rotate(model,angle,glm::vec3(0.0f,1.0f,0.0f));

	shader->setMVP(vp*model);
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
