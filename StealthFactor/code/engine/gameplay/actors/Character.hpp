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
			class Character : public Actor
			{
			public:
				Character();
				virtual ~Character();

			protected:
				std::shared_ptr<RenderComponent> renderComponent;

				dGeomID collisionGeomId;

				bool isWalking{ false };
			};
		}
	}
}
