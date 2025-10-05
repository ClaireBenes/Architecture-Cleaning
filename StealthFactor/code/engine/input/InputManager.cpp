#include "engine/input/InputManager.hpp"

#include <iterator>

#include <SFML/Window/Event.hpp>

namespace engine
{
	namespace input
	{
		Manager::Manager(bool hasFocus)
			: hasFocus(hasFocus)
		{
		}

		bool Manager::isKeyPressed(sf::Keyboard::Key key) const
		{
			if (!hasFocus)
				return false;

			return sf::Keyboard::isKeyPressed(key);
		}

		bool Manager::isKeyJustPressed(sf::Keyboard::Key key) const
		{
			if (!hasFocus)
				return false;

			return justPressedKeys.find(key) != std::end(justPressedKeys);
		}

		bool Manager::isKeyJustReleased(sf::Keyboard::Key key) const
		{
			if (!hasFocus)
				return false;

			return justReleasedKeys.find(key) != std::end(justReleasedKeys);
		}

		void Manager::update()
		{
			justPressedKeys.clear();
			justReleasedKeys.clear();
		}

		void Manager::onApplicationEvent(const sf::Event &event)
		{
			switch (event.type)
			{
				case sf::Event::GainedFocus:
					hasFocus = true;
					break;
				case sf::Event::LostFocus:
					hasFocus = false;
					break;

				case sf::Event::KeyPressed:
					justPressedKeys.insert(event.key.code);
					break;
				case sf::Event::KeyReleased:
					justReleasedKeys.insert(event.key.code);
					break;

				default:
					break;
			}
		}
	}
}
