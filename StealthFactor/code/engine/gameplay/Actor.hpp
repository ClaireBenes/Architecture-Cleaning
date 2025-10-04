#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/Transform.hpp>

namespace engine
{
	namespace gameplay
	{
		class Component;

		class Actor
		{
		public:
			virtual ~Actor();

			virtual void update() = 0;

			void addComponent(const std::shared_ptr<Component>& component);

			const sf::Vector2f &getPosition() const;
			void setPosition(const sf::Vector2f &newPosition);

			float getRotation() const;
			void setRotation(float newRotation);

			const sf::Transform &getTransform() const;

		private:
			std::vector<std::shared_ptr<Component>> components{};

			sf::Vector2f _position{};
			float _rotation{ 0.f };
			sf::Transform _transform;

			void updateTransform();
		};
	}
}
