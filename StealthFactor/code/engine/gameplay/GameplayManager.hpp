#pragma once

#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>

namespace engine
{
	namespace gameplay
	{
		class Actor;

		namespace actors
		{
			class Player;
		}

		class Manager
		{
		public:
			void update();

			void gameOver();

			sf::Vector2f getViewCenter() const;

			void loadMap(const std::string &mapName);
			void loadNextMap();

			const actors::Player &getPlayer() const;

			static const float CELL_SIZE;

			static Manager &getInstance();

		private:
			std::set<Actor *> actors;
			actors::Player *playerActor{};

			// Map
			std::string currentMapName;
			std::string nextMapName;
			int rows{ 0 };
			int columns{ 0 };

			bool preventMapCompletion{ false };
			bool nextMapRequested{ false };
			bool shouldGameOver{ false };

			static Manager *instance;
		};
	}
}
