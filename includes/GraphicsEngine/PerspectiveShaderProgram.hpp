//
//  PerspectiveShaderProgram.hpp
//  xcode target
//
//  Created by Pierre Gabory on 28/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef PerspectiveShaderProgram_hpp
#define PerspectiveShaderProgram_hpp

#include "Frameworks.hpp"
#include "ShaderProgram.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GraphicsEngine {
    class PerspectiveShaderProgram : public ShaderProgram {
    private:
        GLuint m_uniformModelViewMatrix;
        GLuint m_uniformNormalMatrix;
        GLuint m_uniformModelViewProjectionMatrix;
        
        GLuint m_uniformTextureSampler;
        
        void findUniforms();
        
    public:
        PerspectiveShaderProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
        
        ~PerspectiveShaderProgram() {};
        
        void setUniformMatrices(const glm::mat4 &modelView, const glm::mat4 &projection);
    };
}

#endif /* PerspectiveShaderProgram_hpp */
