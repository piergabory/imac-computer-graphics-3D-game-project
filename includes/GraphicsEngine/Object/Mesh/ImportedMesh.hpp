/**
 * \file ImportedMesh.hpp
 * \author Marco Kouyaté
 * \date 19/12/18
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
    
    /**
     * IMPORTED MESH CLASS
     * \version 0.1
     * \brief Import an .obj file and create a Mesh3D from imported vertices.
     *
     * This class uses ASSIMP library to load vertices from a .obj file, expecting a filepath as argument to create a Mesh3D.
     *
     * \warning You need ASSIMP to compile!
     *
     */

    class ImportedMesh : public Mesh3D
    {
  
    public:
        ImportedMesh(LocalFilePath &path) ;
        
        
    private:
        
        //ASSIMP FUNCTIONS
        
        /// \brief loads a model with supported ASSIMP extensions from file and returns a vector of vertices.
        static std::vector<Vertex3D> loadModel(LocalFilePath &path);
        
        /// \brief process ASSIMP's root node recursively
        static std::vector<Vertex3D> processNode(aiNode *node, const aiScene *scene);
        
        /// \brief extract vertices from current mesh
        static std::vector<Vertex3D> processMesh(aiMesh *mesh, const aiScene *scene);
        
        static void displayVertices (std::vector<Vertex3D> vertices, std::string bugLocation);
      
    };

}
#endif
