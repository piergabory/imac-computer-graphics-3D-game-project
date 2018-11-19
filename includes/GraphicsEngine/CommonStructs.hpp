 //
 //  CommonStructs.hpp
 //  product
 //
 //  Created by Pierre Gabory on 17/11/2018.
 //

 #ifndef CommonStructs_hpp
 #define CommonStructs_hpp

  #include <glm/glm.hpp>

 namespace GraphicsEngine {
    
     struct Vertex {
         glm::vec3 m_position;
         glm::vec3 m_normal;
         glm::vec2 m_textureCoordinates;
         
         Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture):
            m_position(position), m_normal(normal), m_textureCoordinates(texture)
         {}
         
     };
    
 }

 #endif /* CommonStructs_hpp */
