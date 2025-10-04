#include "Component.hpp"

namespace engine
{
	namespace gameplay
	{
		Component::Component(Actor& owner)
			: owner(owner)
		{
		}
	}
}
