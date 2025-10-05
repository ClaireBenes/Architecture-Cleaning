#include "Player.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/actors/Target.hpp>

#include <engine/gameplay/components/RenderComponent.hpp>
#include <engine/gameplay/components/PhysicsComponent.hpp>

#include <engine/input/InputManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			Player::Player(const ManagerProvider& managerProvider)
				: Character(managerProvider)
			{
				renderComponent->getShapeList().load("player");

				physicsComponent = std::make_shared<PhysicsComponent>(*this);
				physicsComponent->createBox(
					gameplay::Manager::CELL_SIZE * 0.9f,
					gameplay::Manager::CELL_SIZE * 0.9f,
					1.f
				);
				addComponent(physicsComponent);
			}

			void Player::update()
			{
				justMoved = false;
				auto position = getPosition();
				float rotation = getRotation();

				input::Manager* inputManager = managerProvider.inputManager;

				if (inputManager->isKeyJustPressed(sf::Keyboard::Left))
				{
					justMoved = true;
					position.x -= gameplay::Manager::CELL_SIZE;
					rotation = 180.f;
				}

				if (inputManager->isKeyJustPressed(sf::Keyboard::Right))
				{
					justMoved = true;
					position.x += gameplay::Manager::CELL_SIZE;
					rotation = 0.f;
				}

				if (inputManager->isKeyJustPressed(sf::Keyboard::Up))
				{
					justMoved = true;
					position.y -= gameplay::Manager::CELL_SIZE;
					rotation = -90.f;
				}

				if (inputManager->isKeyJustPressed(sf::Keyboard::Down))
				{
					justMoved = true;
					position.y += gameplay::Manager::CELL_SIZE;
					rotation = 90.f;
				}

				if (justMoved)
				{
					setPosition(position);
					setRotation(rotation);

					physicsComponent->updatePosition();
				}

				gameplay::Manager* gameplayManager = managerProvider.gameplayManager;
				for (const std::shared_ptr<PhysicsComponent> &collidedComponent : physicsComponent->getActiveCollisions())
				{
					Actor *actor = collidedComponent->getOwner();

					auto targetActor = dynamic_cast<actors::Target *>(actor);
					if (targetActor)
					{
						gameplayManager->loadNextMap();
					}
				}
			}

			bool Player::hasJustMoved() const
			{
				return justMoved;
			}
		}
	}
}
