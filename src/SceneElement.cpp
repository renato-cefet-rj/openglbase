#include <SceneElement.hpp>

SceneElement::SceneElement()
{
    this->transform = glm::mat4(1.0f);
}

SceneElement::~SceneElement()
{
}

glm::mat4 SceneElement::getTransform()
{
    return this->transform;
}

void SceneElement::setTransform(glm::mat4 transform)
{
    this->transform = transform;
}

