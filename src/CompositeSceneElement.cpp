#include <CompositeSceneElement.hpp>

CompositeSceneElement::CompositeSceneElement()
{
}

CompositeSceneElement::~CompositeSceneElement()
{
    ElementsIterator it;
    for(it = this->elements.begin(); it != this->elements.end(); ++it)
    {
        delete *it;
    }
}

CompositeSceneElement* CompositeSceneElement::append(SceneElement* e)
{
    this->elements.push_back(e);
    return this;
}

void CompositeSceneElement::draw(glm::mat4 transform)
{
    ElementsIterator it;
    for(it = this->elements.begin(); it != this->elements.end(); ++it)
    {
        (*it)->draw(transform * this->getTransform());
    }   
}
