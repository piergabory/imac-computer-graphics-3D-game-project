//
//  Object.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Frameworks.hpp"
#include "CommonStructs.hpp"
#include "Mesh.hpp"
#include "Material.hpp"


namespace GraphicsEngine {
    class Object {
    private:
        Mesh *m_mesh;
        Material *m_material;
        
        glm::mat4 m_modelViewMatrix;
        
        void applyTransformations();
        
    public:
        void translate(const glm::vec3 &translationVector);
        
        void rotate(const float angle, const glm::vec3 &direction);
        
        void scale(const glm::vec3 &scalingVector);
        
        void project(const glm::mat4 &projectionMatrix);
        
        void draw() const;
        
        Object(Mesh *mesh, Material *material) : m_mesh(mesh), m_material(material) {
            assert(mesh != nullptr);
            assert(material != nullptr);
        }
        
        Object(Mesh &mesh, Material &material) : m_mesh(&mesh), m_material(&material) {}
        
        ~Object() {}
    };
}


#endif /* Object_hpp */
