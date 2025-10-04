#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

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
			Manager();
			~Manager();

			void update();
			void render();

			void draw(const ShapeList &shapeList, const sf::Transform &transform);

			bool hasFocus() const;

			void addRenderComponent(const std::shared_ptr<gameplay::RenderComponent>& renderComponent);
			void removeRenderComponent(const std::shared_ptr<gameplay::RenderComponent>& renderComponent);

			static Manager &getInstance();

		private:
			void clear();
			void display();

		private:
			std::vector<std::shared_ptr<gameplay::RenderComponent>> renderComponents{};

			sf::RenderWindow window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;

			static Manager *instance;
		};
	}
}
