/**
 * CommonStructs.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
 #ifndef CommonStructs_hpp
 #define CommonStructs_hpp

  #include <glm/glm.hpp>

 namespace GraphicsEngine {
    
     /**
      * VERTEX STRUCT
      * holds vertex data for 3D meshes.
      */
     struct Vertex {
         // properties
         glm::vec3 m_position;
         glm::vec3 m_normal;
         glm::vec2 m_textureCoordinates;
         
         // constructor
         Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture):
            m_position(position), m_normal(normal), m_textureCoordinates(texture) {}
     };
    
 }

 #endif /* CommonStructs_hpp */
