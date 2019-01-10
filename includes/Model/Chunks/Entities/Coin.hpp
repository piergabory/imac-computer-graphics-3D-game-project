#pragma once

#include "Entity.hpp"

namespace GameModel
{
	class Coin final : public Entity
	{
    private:
        /// \brief static default entity object.
        /// use this instance to clone new objects
        static std::unique_ptr<GraphicsEngine::Object3D> s_entityObject;
        
    public:

        /// \brief object factory caller with parameters for an empty object
        /// automagically called on first instanciation of Entity
        static void loadObject();

		//Methods
		void firstVisit(Player &player) override;

        //Constructor / destructor
        Coin() {
            if (!s_entityObject) loadObject();
            m_entityObject =  std::make_shared<GraphicsEngine::Object3D>(*s_entityObject);
        }
        
        ~Coin() {}

	};
}
