#include "PhysicsManager.hpp"

#include <ode/odeinit.h>

#include <engine/gameplay/components/PhysicsComponent.hpp>

namespace engine
{
	namespace physics
	{
		Manager::Collision::Collision(dGeomID o1, dGeomID o2)
			: o1{ o1 }
			, o2{ o2 }
		{
		}

		Manager::Manager()
		{
			dInitODE();

			spaceId = dHashSpaceCreate(0);
		}

		Manager::~Manager()
		{
			dSpaceDestroy(spaceId);
			dCloseODE();
		}

		void Manager::update()
		{
			frameCollisions.clear();
			dSpaceCollide(spaceId, &frameCollisions, &Manager::nearCallback);
		}

		dSpaceID Manager::getSpaceId() const
		{
			return spaceId;
		}

		std::set<std::shared_ptr<gameplay::PhysicsComponent>> Manager::getCollisionsWith(
			const std::shared_ptr<gameplay::PhysicsComponent>& component
		) const
		{
			std::set<std::shared_ptr<gameplay::PhysicsComponent>> objectCollisions{};

			dGeomID componentGeomId = static_cast<dGeomID>(component->getShapePointer());
			for (const Collision &collision : frameCollisions)
			{
				if (collision.o1 == componentGeomId)
				{
					objectCollisions.insert(getComponentFromGeomData(collision.o2));
				}
				if (collision.o2 == componentGeomId)
				{
					objectCollisions.insert(getComponentFromGeomData(collision.o1));
				}
			}

			return objectCollisions;
		}

		std::shared_ptr<gameplay::PhysicsComponent> Manager::getComponentFromGeomData(dGeomID geomId) const
		{
			void* geomData = dGeomGetData(geomId);
			gameplay::PhysicsComponent* component = reinterpret_cast<gameplay::PhysicsComponent*>(geomData);
			return component->getSharedPointer<gameplay::PhysicsComponent>();
		}

		void Manager::nearCallback(void *data, dGeomID o1, dGeomID o2)
		{
			auto &frameCollisions = *reinterpret_cast<Collisions *>(data);
			frameCollisions.emplace_back(o1, o2);
		}
	}
}
