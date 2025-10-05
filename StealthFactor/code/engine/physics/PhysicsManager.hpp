#pragma once

#include <memory>
#include <set>
#include <vector>

#include <ode/collision.h>

namespace engine
{
	namespace gameplay
	{
		class PhysicsComponent;
	}

	namespace physics
	{
		class Manager
		{
		public:
			Manager();
			~Manager();

			void update();

			dSpaceID getSpaceId() const;

			std::set<std::shared_ptr<gameplay::PhysicsComponent>> getCollisionsWith(
				const std::shared_ptr<gameplay::PhysicsComponent>& component
			) const;

		private:
			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};

			using Collisions = std::vector<Collision>;

			dSpaceID spaceId;
			Collisions frameCollisions;

			std::shared_ptr<gameplay::PhysicsComponent> getComponentFromGeomData(dGeomID geomId) const;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
