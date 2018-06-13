#ifndef __SCENE_ELEMENT__
#define __SCENE_ELEMENT__

#define SceneElementNull (SceneElement*)0

#include <glm/glm.hpp>

class SceneElement
{
    public:
        SceneElement();
        virtual ~SceneElement();
        virtual void draw(glm::mat4 transform) = 0;
        virtual glm::mat4 getTransform();
        virtual void setTransform(glm::mat4 transform);
    private:
        glm::mat4 transform;

};

#endif
