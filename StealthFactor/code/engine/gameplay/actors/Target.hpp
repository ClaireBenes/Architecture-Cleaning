#pragma once

#include <ode/collision.h>

#include <engine/graphics/ShapeList.hpp>

#include <engine/gameplay/Actor.hpp>
#include <engine/gameplay/components/RenderComponent.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			class Target : public Actor
			{
			public:
				Target(const ManagerProvider& managerProvider);
				~Target();

				virtual void update() override;

			private:
				std::shared_ptr<RenderComponent> renderComponent;

				dGeomID collisionGeomId;
			};
		}
	}
}
