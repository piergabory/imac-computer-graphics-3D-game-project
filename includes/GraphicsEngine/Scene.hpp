//
//  Scene.hpp
//  xcode target
//
//  Created by Pierre Gabory on 19/11/2018.
//  Copyright © 2018 Pierre Gabory. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <vector>
#include <iterator>

#include "Object.hpp"
#include "Camera.hpp"

namespace GraphicsEngine
{
    class Scene
    {
    private:
        std::vector<Object*> m_objects;
        Camera camera;
        
    public:
        void add(Object *newObject);
        
        void draw() const;
        
        Scene();
        ~Scene();
    };
}

#endif /* Scene_hpp */
