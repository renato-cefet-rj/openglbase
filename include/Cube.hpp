#ifndef __CUBE_H__
#define __CUBE_H__

#include <App.hpp>

#define CubeNull (Cube*)0

class Cube
{
    public:
        Cube();
        virtual ~Cube();
        virtual void draw();

    private:
        GLuint cubeVertexArrayId;
        GLuint cubeVertexBufferId;
        GLuint cubeColorBufferId;
        GLuint cubeIndexBufferId;
};

#endif
