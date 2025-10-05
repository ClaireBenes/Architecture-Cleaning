#pragma once

#include <memory>

namespace engine
{
	namespace gameplay
	{
		class Actor;

		class Component : public std::enable_shared_from_this<Component>
		{
		public:
			Component(Actor& owner);
			virtual ~Component() = default;

			virtual void setup() = 0;
			virtual void unSetup() = 0;

			template <typename T>
			std::shared_ptr<T> getSharedPointer()
			{
				return std::static_pointer_cast<T>(shared_from_this());
			}

		protected:
			Actor& owner;
		};
	}
}
