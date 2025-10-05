#pragma once

#include <ode/collision.h>

#include <engine/graphics/ShapeList.hpp>

#include <engine/gameplay/Actor.hpp>

namespace engine
{
	namespace gameplay
	{
		class RenderComponent;
		class PhysicsComponent;

		namespace actors
		{
			class Target : public Actor
			{
			public:
				Target(const ManagerProvider& managerProvider);

				virtual void update() override;

			private:
				std::shared_ptr<RenderComponent> renderComponent;
				std::shared_ptr<PhysicsComponent> physicsComponent;
			};
		}
	}
}
