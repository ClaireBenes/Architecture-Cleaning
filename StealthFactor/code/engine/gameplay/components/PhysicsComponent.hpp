#pragma once

#include <set>

#include "Component.hpp"

namespace engine
{
	namespace gameplay
	{
		class PhysicsComponent : public Component
		{
		public:
			PhysicsComponent(Actor& owner);

			void setup() override;
			void unSetup() override;

			void createBox(float sizeX, float sizeY, float sizeZ = 0.0f);

			void updatePosition();

			void* getShapePointer() const;

			std::set<std::shared_ptr<PhysicsComponent>> getActiveCollisions();

		private:
			void* shapePtr = nullptr;
		};
	}
}

