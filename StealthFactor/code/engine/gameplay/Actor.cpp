#include "Actor.hpp"

#include "components/Component.hpp"

namespace engine
{
	namespace gameplay
	{
		Actor::~Actor()
		{
			for (const std::shared_ptr<Component>& component : components)
			{
				component->unSetup();
			}
		}

		void Actor::addComponent(const std::shared_ptr<Component>& component)
		{
			component->setup();
			components.push_back(component);
		}

		const sf::Vector2f & Actor::getPosition() const
		{
			return _position;
		}

		void Actor::setPosition(const sf::Vector2f &newPosition)
		{
			_position = newPosition;
			updateTransform();
		}

		float Actor::getRotation() const
		{
			return _rotation;
		}

		void Actor::setRotation(float newRotation)
		{
			_rotation = newRotation;
			updateTransform();
		}

		const sf::Transform & Actor::getTransform() const
		{
			return _transform;
		}

		void Actor::updateTransform()
		{
			_transform = sf::Transform::Identity;
			_transform.translate(_position);
			_transform.rotate(_rotation);
		}
	}
}
