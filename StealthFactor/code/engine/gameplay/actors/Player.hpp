#pragma once

#include <engine/gameplay/actors/Character.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			class Player : public Character
			{
			public:
				Player();

				virtual void update() override;

				bool hasJustMoved() const;

			private:
				bool justMoved{ false };
			};
		}
	}
}
