/**
 * \file CommonStructs.hpp
 */

#include "CommonStructs.hpp"

 namespace GraphicsEngine {

     std::string LocalFilePath::s_absolutePathToExecutable = "";
     void LocalFilePath::setLocation(std::string executablePath) {
         
         executablePath = executablePath.substr(0, executablePath.find_last_of("/"));
         
         std::string executableFolder = executablePath.substr(0, executablePath.find_last_of("/"));
         
        std::cout << "executablePath : " << executablePath << std::endl;
         std::cout << "executableFolder : " << executableFolder << std::endl;
         
         if (executableFolder.length() < 5){
             executablePath = "../";
         }
         
         
         
         s_absolutePathToExecutable = executableFolder + "/";

     }

 }
