/**
 * \file Object2D.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */

#ifndef Object2D_hpp
#define Object2D_hpp
#pragma once

#include "Object.hpp"

namespace GraphicsEngine {

    /**
     * OBJECT 2D CLASS
     *
     * \brief Creates a rectangular sprite
     * \version 0.2
     *
     * create a rectangular quad from two points and links it to the 2D Shader
     * the 2D shaders needs to initialized before any instanciations.
     */

    class Object2D : public Object<Vertex2D> {

    private:
        /// \brief Common shader for 2D objects. Simply projects the texture on the 4 corners of the rectangle.
        static std::shared_ptr<ShaderProgram> s_2dShader;

        
        // constructor delegates:

        /// \brief Static initializer for the 2D material (from imagepath)
        static std::shared_ptr<Material> createMaterial(LocalFilePath textureImagePath);

        /// \brief Static initializer for the 2D material (from texture)
        static std::shared_ptr<Material> createMaterial(std::shared_ptr<Texture> &texture);

        /// \brief Static initializer to construct a 2D rectangular mesh
        static std::shared_ptr<Mesh2D> createBoundingBox(const glm::vec2 &position, const glm::vec2 &size);


    public:
        /// \brief sets the common shader. Needs to be called before any class instanciation
        static void initialize2DShaderProgram(LocalFilePath vertexShaderPath, LocalFilePath  framgmentShaderPath);
        
        //change texture of the object
        void texture(std::shared_ptr<Texture> newtex);

        /// \brief constructor using a file path.
        Object2D(const glm::vec2 &position, const glm::vec2 &size, const LocalFilePath image) : Object<Vertex2D>(createBoundingBox(position, size), createMaterial(image)) { }

        /// \brief constructor using a texture.
        Object2D(glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture) : Object<Vertex2D>(createBoundingBox(position, size), createMaterial(texture)) { }
    };
}

#endif /* Object2D_hpp */
