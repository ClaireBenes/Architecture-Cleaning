#include "Target.hpp"

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/components/PhysicsComponent.hpp>
#include <engine/gameplay/components/RenderComponent.hpp>

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

				physicsComponent = std::make_shared<PhysicsComponent>(*this);
				physicsComponent->createBox(
					gameplay::Manager::CELL_SIZE * 0.9f, 
					gameplay::Manager::CELL_SIZE * 0.9f,
					1.f
				);
				addComponent(physicsComponent);
			}

			void Target::update()
			{
				physicsComponent->updatePosition();
			}
		}
	}
}
