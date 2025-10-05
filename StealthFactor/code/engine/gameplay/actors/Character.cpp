#include "Character.hpp"

#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/components/RenderComponent.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			Character::Character(const ManagerProvider& managerProvider)
				: Actor(managerProvider)
			{
				renderComponent = std::make_shared<RenderComponent>(*this);
				addComponent(renderComponent);
			}
		}
	}
}
