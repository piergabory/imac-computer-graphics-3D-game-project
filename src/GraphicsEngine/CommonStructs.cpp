/**
 * CommonStructs.hpp
 */

#include "CommonStructs.hpp"

 namespace GraphicsEngine {

     std::string LocalFilePath::s_absolutePathToExecutable = "";
     void LocalFilePath::setLocation(std::string executablePath) {
         executablePath = executablePath.substr(0, executablePath.find_last_of("/"));
         s_absolutePathToExecutable = executablePath.substr(0, executablePath.find_last_of("/") + 1);
     }

 }
