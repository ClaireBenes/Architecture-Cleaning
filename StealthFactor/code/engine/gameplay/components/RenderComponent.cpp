#include "RenderComponent.hpp"

#include <engine/gameplay/Actor.hpp>
#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		RenderComponent::RenderComponent(Actor& owner, graphics::ShapeList shapeList)
			: Component(owner), shapeList(shapeList)
		{
		}

		void RenderComponent::setup()
		{
			const std::shared_ptr<RenderComponent> sharedThis = getSharedPointer<RenderComponent>();
			graphics::Manager::getInstance().addRenderComponent(sharedThis);
		}

		void RenderComponent::unSetup()
		{
			const std::shared_ptr<RenderComponent> sharedThis = getSharedPointer<RenderComponent>();
			graphics::Manager::getInstance().removeRenderComponent(sharedThis);
		}

		graphics::ShapeList& RenderComponent::getShapeList()
		{
			return shapeList;
		}

		void RenderComponent::draw()
		{
			graphics::Manager::getInstance().draw(shapeList, owner.getTransform());
		}
	}
}
