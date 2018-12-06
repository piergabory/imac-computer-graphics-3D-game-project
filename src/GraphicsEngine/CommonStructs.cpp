/**
 * CommonStructs.hpp
 */

#include "CommonStructs.hpp"

 namespace GraphicsEngine {

     std::string LocalFilePath::m_absolutePathToExecutable = "";
     void LocalFilePath::setLocation(std::string executablePath) {
         executablePath = executablePath.substr(0, executablePath.find_last_of("/"));
         m_absolutePathToExecutable = executablePath.substr(0, executablePath.find_last_of("/") + 1);
     }

 }
