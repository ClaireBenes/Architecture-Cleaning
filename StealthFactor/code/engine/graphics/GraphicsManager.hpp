#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include <engine/ApplicationEventListener.h>

namespace engine
{
	namespace gameplay
	{
		class RenderComponent;
	}

	namespace graphics
	{
		class ShapeList;

		class Manager
		{
		public:
			Manager(ApplicationEventListener& eventListener);
			~Manager();

			void update();
			void render();

			void draw(const ShapeList &shapeList, const sf::Transform &transform);

			bool hasFocus() const;

			void addRenderComponent(const std::shared_ptr<gameplay::RenderComponent>& renderComponent);
			void removeRenderComponent(const std::shared_ptr<gameplay::RenderComponent>& renderComponent);

			void setCameraCenter(sf::Vector2f viewCenter);

		private:
			void clear();
			void display();

		private:
			std::vector<std::shared_ptr<gameplay::RenderComponent>> renderComponents{};

			sf::RenderWindow window;
			sf::View cameraView;

			ApplicationEventListener& eventListener;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;
		};
	}
}
