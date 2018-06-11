#include <Cube.hpp>

Cube::Cube()
{
    float cubeVertex[] = 
    {
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f
    };

    float cubeColorPerVertex[] = 
    {
        1.0f,  0.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  0.5f,
        0.5f,  0.0f,  0.5f
    };

    unsigned int cubeIndex[] = 
    {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        3, 2, 6,
        6, 7, 3,
        4, 0, 3,
        3, 7, 4,
        5, 4, 7,
        7, 6, 5,
        4, 5, 1,
        1, 0, 4
    };

	glGenVertexArrays(1, &this->cubeVertexArrayId);
	glBindVertexArray(this->cubeVertexArrayId);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	

	glGenBuffers(1, &this->cubeVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->cubeVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), cubeVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,false,0,NULL);

	glGenBuffers(1, &this->cubeColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->cubeColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), cubeColorPerVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(1,3,GL_FLOAT,false,0,NULL);

	glGenBuffers(1, &this->cubeIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->cubeIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * 3 * sizeof(unsigned int), cubeIndex, GL_STATIC_DRAW);
}

Cube::~Cube()
{
    glDeleteBuffers(1,&this->cubeVertexArrayId);
    glDeleteBuffers(1,&this->cubeColorBufferId);
    glDeleteBuffers(1,&this->cubeIndexBufferId);
    glDeleteVertexArrays(1, &this->cubeVertexArrayId);
}

void Cube::draw()
{
	glBindVertexArray(this->cubeVertexArrayId);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
