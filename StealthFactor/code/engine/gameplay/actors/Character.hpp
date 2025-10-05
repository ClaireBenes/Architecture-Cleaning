#pragma once

#include <ode/collision.h>

#include <engine/graphics/ShapeList.hpp>

#include <engine/gameplay/Actor.hpp>

namespace engine
{
	namespace gameplay
	{
		class RenderComponent;

		namespace actors
		{
			class Character : public Actor
			{
			public:
				Character(const ManagerProvider& managerProvider);

			protected:
				std::shared_ptr<RenderComponent> renderComponent;

				bool isWalking{ false };
			};
		}
	}
}
