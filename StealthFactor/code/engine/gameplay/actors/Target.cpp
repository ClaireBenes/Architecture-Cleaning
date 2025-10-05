#include "Target.hpp"

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			Target::Target(const ManagerProvider& managerProvider)
				: Actor(managerProvider)
			{
				renderComponent = std::make_shared<RenderComponent>(*this);
				renderComponent->getShapeList().load("target");
				addComponent(renderComponent);

				physics::Manager* physicsManager = managerProvider.physicsManager;
				collisionGeomId = dCreateBox(
					physicsManager->getSpaceId(), 
					gameplay::Manager::CELL_SIZE * 0.9f, 
					gameplay::Manager::CELL_SIZE * 0.9f,
					1.f
				);
				dGeomSetData(collisionGeomId, this);
			}

			Target::~Target()
			{
				dGeomDestroy(collisionGeomId);
			}

			void Target::update()
			{
				auto &position = getPosition();
				dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
			}
		}
	}
}
