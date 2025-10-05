#pragma once

#include <engine/gameplay/actors/Character.hpp>

namespace engine
{
	namespace gameplay
	{
		class PhysicsComponent;

		namespace actors
		{
			class Player : public Character
			{
			public:
				Player(const ManagerProvider& managerProvider);

				virtual void update() override;

				bool hasJustMoved() const;

			private:
				std::shared_ptr<PhysicsComponent> physicsComponent;

				bool justMoved{ false };
			};
		}
	}
}
