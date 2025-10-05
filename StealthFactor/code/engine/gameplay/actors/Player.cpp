#include "Player.hpp"

#include <ode/collision.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/actors/Target.hpp>

#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/Engine.hpp>

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
				
				// TODO: make a PhysicsComponent/BoxComponent
				collisionGeomId = dCreateBox(
					managerProvider.physicsManager->getSpaceId(), 
					gameplay::Manager::CELL_SIZE * 0.9f, 
					gameplay::Manager::CELL_SIZE * 0.9f, 
					1.f
				);
				dGeomSetData(collisionGeomId, this);
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

					dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
				}

				physics::Manager* physicsManager = managerProvider.physicsManager;
				gameplay::Manager* gameplayManager = managerProvider.gameplayManager;

				// TODO: make a method on our soon-existing PhysicsComponent to get on-going collisions
				auto collisions = physicsManager->getCollisionsWith(collisionGeomId);
				for (auto &geomId : collisions)
				{
					auto entity = reinterpret_cast<Actor *>(dGeomGetData(geomId));
					auto targetEntity = dynamic_cast<actors::Target *>(entity);
					if (targetEntity)
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
