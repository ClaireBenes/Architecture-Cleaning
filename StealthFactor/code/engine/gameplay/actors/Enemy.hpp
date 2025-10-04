#pragma once

#include <string>

#include <engine/gameplay/actors/Character.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace actors
		{
			class Enemy : public Character
			{
			public:
				Enemy(const std::string &archetypeName);

				virtual void update() override;

			private:
				float visionRadius{ 0 };
				int shootDelay{ 0 };
				int shootDelayCounter{ 0 };

				void loadArchetype(const std::string &archetypeName);
			};
		}
	}
}
