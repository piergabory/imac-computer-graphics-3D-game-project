//
//  Context.hpp
//  xcode target
//
//  Created by Pierre Gabory on 17/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Context_hpp
#define Context_hpp

#include <memory>

#include "Object3D.hpp"

namespace GraphicsEngine {

    template<class ObjectType>
    class Context {
    private:
        /**
         * Object list in scene. Vector of object pointers.
         *
         * An object may appear twice, Objects know how to draw themselves.
         * Scene handle their relation with the camera's (aka, the projection matrix) for each of them on draw().
         */
        std::vector< std::weak_ptr<ObjectType> > m_objects;

        virtual void contextWillRender() const {}
        virtual void initializeObject(const std::shared_ptr<ObjectType> &newObject) const {}
        virtual void objectPrerenderStage(const std::shared_ptr<ObjectType> &newObject) const {}


    public:
        // adds an object in the scene.
        void add(const std::shared_ptr<ObjectType> &newObject) {
            m_objects.push_back(newObject);
            initializeObject(newObject);
            // shared pointer is destroyed.
            // Value is own in the scope of Context::add() call, and linked here by a weak pointer in m_objects
        }

        // remove an object from the scenes.
        void remove(const std::shared_ptr<ObjectType> &object) {
            for(size_t i = 0; i < m_objects.size(); ++i) {
                std::shared_ptr<ObjectType> tmpobject = m_objects[i].lock();

                // find object and deletes it.
                if (object == tmpobject) {
                    m_objects.erase(m_objects.begin() + i);
                }

                // tmpobject is destroyed
            }
        }


        // Draws the scene: Span through each element in the scene, projects them on the camera.
        void render() {
            contextWillRender();

            for(size_t i = 0; i < m_objects.size(); ++i) {
                if (m_objects[i].expired()) {
                    m_objects.erase(m_objects.begin() + i);
                    continue;
                }

                std::shared_ptr<ObjectType> object = m_objects[i].lock();

                // push the vertices in the pipeline
                objectPrerenderStage(object);
                object->draw();
            }

            // shared pointer object is destroyed.
        }


        // constructor
        // initialize camera
        Context() {}

        // destructor
        // deletes memory allocated on each pointer in the object vector.
        virtual ~Context() {}
    };
}
#endif /* Context_hpp */
