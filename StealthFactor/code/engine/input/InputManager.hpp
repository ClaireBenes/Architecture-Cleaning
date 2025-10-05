#pragma once

#include <set>

#include <SFML/Window/Keyboard.hpp>

#include <engine/ApplicationEventListener.h>

namespace engine
{
	class Engine;

	namespace input
	{
		class Manager : public ApplicationEventListener
		{
		public:
			Manager(bool hasFocus);

			// True during all frames while the key is pressed.
			bool isKeyPressed(sf::Keyboard::Key key) const;

			// True only the first frame after that the key is pressed.
			bool isKeyJustPressed(sf::Keyboard::Key key) const;

			// True only the first frame after that the key is released.
			bool isKeyJustReleased(sf::Keyboard::Key key) const;

			void update();

			void onApplicationEvent(const sf::Event &event) override;

		private:
			std::set<sf::Keyboard::Key> justPressedKeys;
			std::set<sf::Keyboard::Key> justReleasedKeys;

			bool hasFocus = false;
		};
	}
}
