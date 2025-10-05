#include "PhysicsComponent.hpp"

#include <ode/collision.h>

#include <engine/gameplay/Actor.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		PhysicsComponent::PhysicsComponent(Actor& owner)
			: Component(owner)
		{
		}

		void PhysicsComponent::setup()
		{
		}

		void PhysicsComponent::unSetup()
		{
			if (shapePtr != nullptr)
			{
				dGeomDestroy(static_cast<dGeomID>(shapePtr));
			}
		}

		void PhysicsComponent::updatePosition()
		{
			const sf::Vector2f& position = owner.getPosition();
			dGeomSetPosition(static_cast<dGeomID>(shapePtr), position.x, position.y, 0);
		}

		void PhysicsComponent::createBox(float sizeX, float sizeY, float sizeZ)
		{
			physics::Manager* physicsManager = owner.getManagerProvider().physicsManager;

			dGeomID geomId = dCreateBox(physicsManager->getSpaceId(), sizeX, sizeY, sizeZ);
			dGeomSetData(geomId, this);

			shapePtr = geomId;
		}

		void* PhysicsComponent::getShapePointer() const
		{
			return shapePtr;
		}

		std::set<std::shared_ptr<PhysicsComponent>> PhysicsComponent::getActiveCollisions()
		{
			physics::Manager* physicsManager = owner.getManagerProvider().physicsManager;
			return physicsManager->getCollisionsWith(getSharedPointer<PhysicsComponent>());
		}
	}
}
