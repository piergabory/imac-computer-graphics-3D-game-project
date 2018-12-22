/**
 * \file Context.hpp
 *
 * IMAC 2 Project CG CPP
 */

#ifndef Context_hpp
#define Context_hpp

#include <memory>

#include "Object.hpp"


namespace GraphicsEngine {

    /**
     * CLASS TEMPLATE CONTEXT
     *
     * Superclass to Scene and Canvas
     * \brief Container of Object 2D or 3D, manage their lifecycle and render.
     */
    template<class ObjectType>
    class Context {
    private:

        /**
         * \brief Object list in scene. Vector of object pointers.
         *
         * An object may appear twice, Objects know how to draw themselves.
         * Scene handle their relation with the camera's (aka, the projection matrix) for each of them on draw().
         */
        std::vector< std::weak_ptr<ObjectType> > m_objects;


        // RENDER LIFECYCLE

        /// \brief virtual method called before each render ( used to enable/disable depth testing and/or backface culling)
        virtual void contextWillRender() const {}

        /// \brief Object initializer called on newly added object
        /// usecase (3D): to set their projections matrices for object
        virtual void initializeObject(const std::shared_ptr<ObjectType> &newObject) const {}

        /// \brief Object initializer called before each render.
        /// if an object is about to be rendered, this method will be called with the object's reference.
        /// usecase (3D): to project the object in the camera before each render.
        virtual void objectPrerenderStage(const std::shared_ptr<ObjectType> &newObject) const {}


    public:
        /// \brief adds an object in the context.
        void add(const std::shared_ptr<ObjectType> &newObject) {
            m_objects.push_back(newObject);
            initializeObject(newObject);
            // shared pointer is destroyed.
            // Value is own in the scope of Context::add() call, and linked here by a weak pointer in m_objects
        }

        /// \brief remove an object from the scenes.
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


        /// \brief Draws the scene: Span through each element in the scene.
        void render() {
            // call lifcycle method
            contextWillRender();

            // foreach object
            for(size_t i = 0; i < m_objects.size(); ++i) {

                // clean up lost objects
                if (m_objects[i].expired()) {
                    m_objects.erase(m_objects.begin() + i);
                    continue;
                }

                // create shared pointer
                std::shared_ptr<ObjectType> object = m_objects[i].lock();

                // push the vertices in the pipeline
                objectPrerenderStage(object);
                object->draw();
            }

            // shared pointer object is destroyed.
        }


        /// \brief constructor
        Context() {}

        /// \brief destructor
        virtual ~Context() {}
    };
}
#endif /* Context_hpp */
