#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/input/InputManager.hpp>

namespace engine
{
	Engine::Engine()
	{
		graphicsManager = std::make_unique<graphics::Manager>(*this);
		managerProvider.graphicsManager = graphicsManager.get();
		
		inputManager = std::make_unique<input::Manager>(graphicsManager->hasFocus());
		managerProvider.inputManager = inputManager.get();

		physicsManager = std::make_unique<physics::Manager>();
		managerProvider.physicsManager = physicsManager.get();

		gameplayManager = std::make_unique<gameplay::Manager>(managerProvider);
		managerProvider.gameplayManager = gameplayManager.get();
	}

	void Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			startMap = configuration.child_value("start_map");
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;
		}
	}

	void Engine::run()
	{
		running = true;

		gameplayManager->loadMap(startMap);

		sf::Clock clock;
		while (running)
		{
			deltaTime = clock.restart().asSeconds();

			physicsManager->update();
			inputManager->update();
			graphicsManager->update();
			gameplayManager->update();

			graphicsManager->render();
		}
	}

	float Engine::getDeltaTime() const
	{
		return deltaTime;
	}

	void Engine::exit()
	{
		running = false;
	}

	void Engine::onApplicationEvent(const sf::Event& event)
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				exit();
				return;
		}

		inputManager->onApplicationEvent(event);
	}
}
