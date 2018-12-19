/**
 * \file ImportedMesh.hpp
 *
 * IMAC 2 Project CG CPP
 *
 */


#ifndef IMPORTEDMESH_H
#define IMPORTEDMESH_H



//include all assimp functions
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//include
#include "Mesh.hpp"
#include "CommonStructs.hpp"

// TODO check if useful
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>




namespace GraphicsEngine {

    class ImportedMesh : public Mesh3D
    {
  
    public:
        ImportedMesh(LocalFilePath &path) ; // constructor, expects a filepath to a 3D model.
        
        
    private:
        /*  Functions   */

        static std::vector<Vertex3D> loadModel(LocalFilePath &path); // loads a model with supported ASSIMP extensions from file and returns a vector of vertices.
        
        static std::vector<Vertex3D> processNode(aiNode *node, const aiScene *scene); // process ASSIMP's root node recursively
        
        static std::vector<Vertex3D> processMesh(aiMesh *mesh, const aiScene *scene);
        
        static void displayVertices (std::vector<Vertex3D> vertices, std::string bugLocation);
      
    };

}
#endif
