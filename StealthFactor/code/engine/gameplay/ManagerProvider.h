#pragma once

namespace engine
{
	namespace graphics
	{
		class Manager;
	}

	namespace input
	{
		class Manager;
	}

	namespace physics
	{
		class Manager;
	}

	namespace gameplay
	{
		class Manager;

		struct ManagerProvider
		{
			gameplay::Manager* gameplayManager{ nullptr };
			graphics::Manager* graphicsManager{ nullptr };
			input::Manager* inputManager{ nullptr };
			physics::Manager* physicsManager{ nullptr };
		};
	}
}