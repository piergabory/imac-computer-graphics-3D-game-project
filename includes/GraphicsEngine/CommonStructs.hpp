/**
 * \file CommonStructs.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */
#ifndef CommonStructs_hpp
#define CommonStructs_hpp

#include <string>
#include <glm/glm.hpp>

 namespace GraphicsEngine {
    
     /**
      * VERTEX STRUCT
      * holds vertex data for 3D meshes.
      */
     struct Vertex3D {
         // properties
         glm::vec3 m_position;
         glm::vec3 m_normal;
         glm::vec2 m_textureCoordinates;
         
         // constructor
         Vertex3D(glm::vec3 position, glm::vec3 normal, glm::vec2 texture):
            m_position(position), m_normal(normal), m_textureCoordinates(texture) {}
     };


     /**
      * VERTEX STRUCT
      * holds vertex data for 2D meshes.
      */
     struct Vertex2D {
         // properties
         glm::vec2 m_position;
         glm::vec2 m_textureCoordinates;

         // constructor
         Vertex2D(glm::vec2 position, glm::vec2 texture):
         m_position(position), m_textureCoordinates(texture) {}
     };


     /**
      * LocalFilePath
      * Subclass to std::string allowing easy creation of absolutes paths relatives to the executable
      */
     class LocalFilePath : public std::string {
     private:
         static std::string s_absolutePathToExecutable;

     public:
         static void setLocation(std::string executablePath);

         LocalFilePath(std::string localPath) : std::string(s_absolutePathToExecutable + localPath) {
             assert(!s_absolutePathToExecutable.empty());
         }
     };
     /**
     * @struct u_light_direction
     * @brief This structure represents light points
     */
    
     struct Light{
      // propriety
      glm::vec3 m_position;
      float m_intensity;
      glm::vec3 m_color;

      //constructor
      Light(glm::vec3 position, float intensity = 0.5, glm::vec3 color = glm::vec3(255)):m_position(position), m_intensity(intensity), m_color(color){
        assert(intensity>=0 && intensity<=1 && "The intensity shoud be in [0;1]");
        /// \todo faire une intensité > 1 pour les surexpositions
        assert(color[0]<256 && color[1]<256 && color[2]<256);
        assert(color[0]>=0 && color[1]>=0 && color[2]>=0);
        }
};
 }

 #endif /* CommonStructs_hpp */
