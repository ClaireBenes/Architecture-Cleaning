#include "RenderComponent.hpp"

#include <engine/gameplay/Actor.hpp>
#include <engine/Engine.hpp>

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

			graphics::Manager* graphicsManager = owner.getManagerProvider().graphicsManager;
			graphicsManager->addRenderComponent(sharedThis);
		}

		void RenderComponent::unSetup()
		{
			const std::shared_ptr<RenderComponent> sharedThis = getSharedPointer<RenderComponent>();

			graphics::Manager* graphicsManager = owner.getManagerProvider().graphicsManager;
			graphicsManager->removeRenderComponent(sharedThis);
		}

		graphics::ShapeList& RenderComponent::getShapeList()
		{
			return shapeList;
		}

		void RenderComponent::draw()
		{
			graphics::Manager* graphicsManager = owner.getManagerProvider().graphicsManager;
			graphicsManager->draw(shapeList, owner.getTransform());
		}
	}
}
