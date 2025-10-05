#pragma once

namespace sf
{
	class Event;
}

namespace engine
{
	class ApplicationEventListener
	{
	public:
		virtual void onApplicationEvent(const sf::Event &event) = 0;
	};
}