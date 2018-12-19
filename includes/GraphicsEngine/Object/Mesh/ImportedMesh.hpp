#ifndef IMPORTEDMESH_H
#define IMPORTEDMESH_H



//include all assimp functions
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Mesh.hpp"
#include "CommonStructs.hpp"

#include <string>
#include <fstream> // TODO check if useful
#include <sstream>
#include <iostream>
#include <map>
#include <vector>



namespace GraphicsEngine {

    class ImportedMesh : public Mesh3D
    {
  
    public:
        //static std::string directory;

        
        /*  Functions   */
        // constructor, expects a filepath to a 3D model.
        ImportedMesh(LocalFilePath &path) : Mesh (loadModel(path))
        {
            displayVertices(loadModel(path),"constructeur");
        }
        
        
    private:
        /*  Functions   */
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        std::vector<Vertex3D> loadModel(LocalFilePath &path) //TODO - load multiple meshes
        {
            std::vector<Vertex3D> vertices;
            
            // read file via ASSIMP
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
            // check for errors
            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
            {
                std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
                //return;
            }
            // retrieve the directory path of the filepath
            //directory = path.substr(0, path.find_last_of('/'));
            
            // process ASSIMP's root node recursively
            vertices = processNode(scene->mRootNode, scene);
            
            return vertices;
        }
        

        
        static std::vector<Vertex3D> processNode(aiNode *node, const aiScene *scene)
        {
            std::vector<Vertex3D> vertices;
            
            // process each mesh located at the current node
            for(unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                // the node object only contains indices to index the actual objects in the scene.
                // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                vertices = processMesh(mesh, scene);
                

            }
            // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
            for(unsigned int i = 0; i < node->mNumChildren; i++)
            {
                vertices = processNode(node->mChildren[i], scene);
            }
            
            
            
            return vertices ;
        }
        
        static std::vector<Vertex3D> processMesh(aiMesh *mesh, const aiScene *scene)
        {
            std::vector<Vertex3D> vertices;
            
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
                Vertex3D vertex(vectorP,vectorN,vectorT);
                vertices.push_back(vertex);
            }
            
            // return a mesh object created from the extracted mesh data

            
            return vertices;
        }
        
        static void displayVertices (std::vector<Vertex3D> vertices, std::string bugLocation){
            //TODO remove test
            std::cout << "Print vertices of " << bugLocation <<  std::endl;
            std::cout << "Vertices vector size : " << vertices.size() << std::endl;
            for (int i=0; i < vertices.size(); i++){
                std::cout << "m_position : " << vertices[i].m_position[0] << " / " << vertices[i].m_position[1] << " / " << vertices[i].m_position[2] <<  std::endl;
                std::cout << "m_normal : " << vertices[i].m_normal[0] << " / " << vertices[i].m_normal[1] << " / " << vertices[i].m_normal[2] <<  std::endl;
                std::cout << "m_textureCoordinates : " << vertices[i].m_textureCoordinates[0] << " / " << vertices[i].m_textureCoordinates[1] <<  std::endl;
                
            }
            std::cout << "end of printed vertices" << std::endl;
            std::cout << std::endl;
        }
      
    };

}
#endif
