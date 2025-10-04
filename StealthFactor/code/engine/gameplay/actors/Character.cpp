#include "Character.hpp"

#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			Character::Character()
			{
				collisionGeomId = dCreateBox(physics::Manager::getInstance().getSpaceId(), 0.f, 0.f, 0.f);
				dGeomSetData(collisionGeomId, this);

				renderComponent = std::make_shared<RenderComponent>(*this);
				addComponent(renderComponent);
			}

			Character::~Character()
			{
				dGeomDestroy(collisionGeomId);
			}
		}
	}
}
