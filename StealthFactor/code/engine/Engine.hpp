#pragma once

#include <memory>
#include <string>

#include <engine/ApplicationEventListener.h>

#include <engine/gameplay/ManagerProvider.h>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	class Engine : public ApplicationEventListener
	{
	public:
		Engine();

		void loadConfiguration();

		void run();
		float getDeltaTime() const;

		void exit();

		void onApplicationEvent(const sf::Event& event) override;

	private:
		bool running{ false };
		float deltaTime{ 0.0f };

		std::unique_ptr<gameplay::Manager> gameplayManager{ nullptr };
		std::unique_ptr<graphics::Manager> graphicsManager { nullptr };
		std::unique_ptr<input::Manager> inputManager{ nullptr };
		std::unique_ptr<physics::Manager> physicsManager{ nullptr };

		gameplay::ManagerProvider managerProvider{};

		// Configuration
		std::string startMap;
	};
}
