#include "Character.hpp"

#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			Character::Character(const ManagerProvider& managerProvider)
				: Actor(managerProvider)
			{
				collisionGeomId = dCreateBox(managerProvider.physicsManager->getSpaceId(), 0.f, 0.f, 0.f);
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
