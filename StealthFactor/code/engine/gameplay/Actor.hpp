#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/Transform.hpp>

#include <engine/gameplay/ManagerProvider.h>

namespace engine
{
	namespace gameplay
	{
		class Component;

		class Actor
		{
		public:
			Actor(const ManagerProvider& managerProvider);
			virtual ~Actor();

			virtual void update() = 0;

			void addComponent(const std::shared_ptr<Component>& component);

			const sf::Vector2f &getPosition() const;
			void setPosition(const sf::Vector2f &newPosition);

			float getRotation() const;
			void setRotation(float newRotation);

			const sf::Transform &getTransform() const;

			const ManagerProvider &getManagerProvider() const;

		protected:
			const ManagerProvider &managerProvider;

		private:
			std::vector<std::shared_ptr<Component>> components{};

			sf::Vector2f _position{};
			float _rotation{ 0.f };
			sf::Transform _transform;

			void updateTransform();
		};
	}
}
