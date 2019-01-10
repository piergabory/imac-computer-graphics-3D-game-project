/**
 * \file ImportedMesh.cpp
 * \author Marco Kouyaté
 * \date 19/12/18
 */

#include "ImportedMesh.hpp"

namespace GraphicsEngine {
    
    //CONSTRUCTOR
    //Create a Mesh3D from imported .obj
    //Parameters :
        //LocalFilePath - relative path -> absolute path
    ImportedMesh::ImportedMesh(const LocalFilePath &path) : Mesh(loadModel(path)) {}
    
    //ASSIMP FUNCTIONS
    //Read file through ASSIMP importer
    std::vector<Vertex3D> ImportedMesh::loadModel(const LocalFilePath &path)
    {
        std::vector<Vertex3D> vertices;
        
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
            //aiProcess_Triangulate - triangulate polygons for OpenGL
            //aiProcess_FlipUVs - flips all UV coordinates along the y-axis
            //aiProcess_GenNormals - Generate normals if they don't exist
        
        // check for errors
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            //TODO - catch error;
        }
        
        
        vertices = processNode(scene->mRootNode, scene);
        return vertices;
    }
    
    // process ASSIMP's root node recursively
    std::vector<Vertex3D> ImportedMesh::processNode(aiNode *node, const aiScene *scene)
    {
        std::vector<Vertex3D> vertices;
        
        // process each mesh located at the current node
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
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
    
    std::vector<Vertex3D> ImportedMesh::processMesh(aiMesh *mesh, const aiScene *scene)
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
    
    void ImportedMesh::displayVertices (std::vector<Vertex3D> vertices, std::string bugLocation){
        //TODO remove test
        std::cout << "Print vertices of " << bugLocation <<  std::endl;
        std::cout << "Vertices vector size : " << vertices.size() << std::endl;
        for (unsigned int i=0; i < vertices.size(); i++){
            std::cout << "m_position : " << vertices[i].m_position[0] << " / " << vertices[i].m_position[1] << " / " << vertices[i].m_position[2] <<  std::endl;
            std::cout << "m_normal : " << vertices[i].m_normal[0] << " / " << vertices[i].m_normal[1] << " / " << vertices[i].m_normal[2] <<  std::endl;
            std::cout << "m_textureCoordinates : " << vertices[i].m_textureCoordinates[0] << " / " << vertices[i].m_textureCoordinates[1] <<  std::endl;
            
        }
        std::cout << "end of printed vertices" << std::endl;
        std::cout << std::endl;
    }
}
