#include "engine/gameplay/GameplayManager.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <pugixml/pugixml.hpp>

#include <engine/gameplay/actors/Enemy.hpp>
#include <engine/gameplay/actors/Player.hpp>
#include <engine/gameplay/actors/Target.hpp>

#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		const float Manager::CELL_SIZE = 50.f;

		Manager::Manager(const ManagerProvider& managerProvider)
			: managerProvider(managerProvider)
		{
		}

		void Manager::update()
		{
			for (auto entity : actors)
			{
				entity->update();
			}

			preventMapCompletion = false;
			if (nextMapRequested && !nextMapName.empty())
			{
				nextMapRequested = false;
				loadMap(nextMapName);
			}

			if (shouldGameOver)
			{
				std::cout << "Game over" << std::endl;
				loadMap(currentMapName);
				shouldGameOver = false;
			}

			managerProvider.graphicsManager->setCameraCenter(getViewCenter());
		}

		void Manager::gameOver()
		{
			shouldGameOver = true;
		}

		sf::Vector2f Manager::getViewCenter() const
		{
			return sf::Vector2f{ columns * (CELL_SIZE / 2.f), rows * (CELL_SIZE / 2.f) };
		}

		void Manager::loadMap(const std::string & mapName)
		{
			for (auto entity : actors)
			{
				delete entity;
			}
			actors.clear();

			std::stringstream filename;
			filename << "maps/" << mapName << ".xml";

			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

			if (result)
			{
				assert(!doc.empty());
				auto xmlMap = doc.first_child();

				rows = std::stoi(xmlMap.child_value("rows"));
				assert(rows >= 0);

				columns = std::stoi(xmlMap.child_value("columns"));
				assert(columns >= 0);

				for (auto &xmlElement : xmlMap.child("elements").children())
				{
					if (!std::strcmp(xmlElement.name(), "enemy"))
					{
						int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < columns);

						std::string archetypeName = xmlElement.child_value("archetype");

						auto entity = new actors::Enemy{ managerProvider, archetypeName };
						entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						actors.insert(entity);
					}

					if (!std::strcmp(xmlElement.name(), "player"))
					{
						int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < columns);

						auto entity = new actors::Player{ managerProvider };
						entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						actors.insert(entity);
						playerActor = entity;
					}

					if (!std::strcmp(xmlElement.name(), "target"))
					{
						int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < columns);

						auto entity = new actors::Target{ managerProvider };
						entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						actors.insert(entity);
					}
				}

				currentMapName = mapName;
				nextMapName = xmlMap.child_value("next_map");

				// JIRA-1337: Map is skipped.
				// This prevents the map to be completed during the first frame. I don't know why this happens.
				preventMapCompletion = true;
			}
			else
			{
				std::cerr << "Map [" << mapName << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}
		}

		void Manager::loadNextMap()
		{
			if (!preventMapCompletion)
			{
				nextMapRequested = true;
			}
		}

		const actors::Player &Manager::getPlayer() const
		{
			assert(playerActor);
			return *playerActor;
		}
	}
}
