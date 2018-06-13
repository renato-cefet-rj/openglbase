#ifndef __COMPOSITE_SCENE_ELEMENT__
#define __COMPOSITE_SCENE_ELEMENT__

#define CompositeSceneElementNull (CompositeSceneElement*)0
#include <SceneElement.hpp>
#include <list>

typedef  std::list<SceneElement*>::iterator ElementsIterator;

class CompositeSceneElement: public SceneElement
{
    public:
        CompositeSceneElement();
        virtual ~CompositeSceneElement();
        virtual CompositeSceneElement* append(SceneElement* se);
        virtual void draw(glm::mat4 transform);

    private:
        std::list<SceneElement*> elements;
};

#endif
