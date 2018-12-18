//
//  Model.hpp
//  Projet_S2_CG_CPP
//
//  Created by Djayd Nova on 18/12/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef MODEL_H
#define MODEL_H

//#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <stb_image.h>

//include all assimp functions
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Object.hpp"
#include "Mesh.hpp"
#include "CommonStructs.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace GraphicsEngine {

    class Model
    {
    public:
        /*  Model Data */

        vector<Object> objects;
        
        string directory;
        bool gammaCorrection;
        
        /*  Functions   */
        // constructor, expects a filepath to a 3D model.
        Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
        {
            loadModel(path);
        }
        
        // draws the model, and thus all its meshes
        void Draw(Shader shader)
        {
            for(unsigned int i = 0; i < objects.size(); i++)
                objects[i].draw();
        }
        
    private:
        /*  Functions   */
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(string const &path)
        {
            // read file via ASSIMP
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
            // check for errors
            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
            {
                cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
                return;
            }
            // retrieve the directory path of the filepath
            directory = path.substr(0, path.find_last_of('/'));
            
            // process ASSIMP's root node recursively
            processNode(scene->mRootNode, scene);
        }
        
        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode *node, const aiScene *scene)
        {
            // process each mesh located at the current node
            for(unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                // the node object only contains indices to index the actual objects in the scene.
                // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                displayVertices(processMesh(mesh, scene));
            }
            // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
            for(unsigned int i = 0; i < node->mNumChildren; i++)
            {
                processNode(node->mChildren[i], scene);
            }
            
        }
        
        vector<Vertex> processMesh(aiMesh *mesh, const aiScene *scene)
        {
            vector<Vertex> vertices;
            
            // Walk through each of the mesh's vertices
            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                
                glm::vec3 vectorP; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                // positions
                vectorP.x = mesh->mVertices[i].x;
                vectorP.y = mesh->mVertices[i].y;
                vectorP.z = mesh->mVertices[i].z;

                // normals
                glm::vec3 vectorN;
                vectorN.x = mesh->mNormals[i].x;
                vectorN.y = mesh->mNormals[i].y;
                vectorN.z = mesh->mNormals[i].z;
                
                glm::vec2 vectorT;
                // texture coordinates
                if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vectorT.x = mesh->mTextureCoords[0][i].x;
                    vectorT.y = mesh->mTextureCoords[0][i].y;
                }
                else
                    vectorT = glm::vec2(0.0f, 0.0f);
                Vertex vertex(vectorP,vectorN,vectorT);
                vertices.push_back(vertex);
            }
            
            // return a mesh object created from the extracted mesh data
            //return Object(vertices, indices, textures);
            return vertices;
        }
        
        void displayVertices (vector<Vertex> vertices){
            for (int i=0; i < vertices.size(); i++){
                cout << "m_position : " << vertices[i].m_position[0] << " / " << vertices[i].m_position[1] << " / " << vertices[i].m_position[2] <<  endl;
                cout << "m_normal : " << vertices[i].m_normal[0] << " / " << vertices[i].m_normal[1] << " / " << vertices[i].m_normal[2] <<  endl;
                cout << "m_textureCoordinates : " << vertices[i].m_textureCoordinates[0] << " / " << vertices[i].m_textureCoordinates[1] <<  endl;
                
                cout << endl;
            }
        }
      
    };

    unsigned int testFunction(){
        return 42;
    };
}
#endif
