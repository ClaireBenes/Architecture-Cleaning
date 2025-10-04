#pragma once

#include "Component.hpp"

#include <engine/graphics/ShapeList.hpp>

namespace engine
{
	namespace gameplay
	{
		class Actor;

		class RenderComponent : public Component
		{
		public:
			RenderComponent(Actor& owner, graphics::ShapeList shapeList = {});

			virtual void setup() override;
			virtual void unSetup() override;

			graphics::ShapeList& getShapeList();

			void draw();

		private:
			graphics::ShapeList shapeList;
		};
	}
}