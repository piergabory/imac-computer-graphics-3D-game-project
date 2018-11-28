//
//  Object.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        glm::mat4 m_normalMatrix;
        
        void applyTransformations();
        
    public:
        inline void* modelViewMatrixPointer() { return glm::value_ptr(m_modelViewMatrix); }
        inline void* normalMatrixPointer() { return glm::value_ptr(m_normalMatrix); }
        
        void translate(const glm::vec3 translationVector);
        
        void rotate(const float angle, const glm::vec3 direction);
        
        void scale(const glm::vec3 scalingVector);
        
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
