#include "engine/graphics/GraphicsManager.hpp"

#include <cassert>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>

#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/components/RenderComponent.hpp>

namespace engine
{
	namespace graphics
	{
		Manager::Manager(ApplicationEventListener &eventListener)
			: eventListener(eventListener)
		{
			window.create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");

			window.setVerticalSyncEnabled(true);

			cameraView = sf::View(
				sf::Vector2f{ 0.f, 0.f }, 
				sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT }
			);
		}

		Manager::~Manager()
		{
			window.close();
		}

		void Manager::update()
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				eventListener.onApplicationEvent(event);
			}
		}

		void Manager::render()
		{
			clear();

			for (const std::shared_ptr<gameplay::RenderComponent>& renderComponent : renderComponents)
			{
				renderComponent->draw();
			}

			display();
		}

		void Manager::clear()
		{
			window.clear(sf::Color::Black);
			window.setView(cameraView);
		}

		void Manager::draw(const ShapeList &shapeList, const sf::Transform &transform)
		{
			sf::RenderStates renderStates{ transform };
			for (auto shape : shapeList.getShapes())
			{
				window.draw(*shape, renderStates);
			}
		}

		void Manager::display()
		{
			window.display();
		}

		bool Manager::hasFocus() const
		{
			return window.hasFocus();
		}

		void Manager::addRenderComponent(const std::shared_ptr<gameplay::RenderComponent>& renderComponent)
		{
			renderComponents.push_back(renderComponent);
		}

		void Manager::removeRenderComponent(const std::shared_ptr<gameplay::RenderComponent>& renderComponent)
		{
			auto itr = std::find(renderComponents.begin(), renderComponents.end(), renderComponent);
			assert(itr != renderComponents.end());

			renderComponents.erase(itr);
		}

		void Manager::setCameraCenter(sf::Vector2f viewCenter)
		{
			cameraView.setCenter(viewCenter);
		}
	}
}
