#include "Entity.h"
#include "Model.h"

namespace NoECS
{	
	class EntitySystem : public NoMVC::Model
	{
	public:
		EntitySystem() {}
		virtual ~EntitySystem() {}
		EntityManager entities;
		virtual void update();
		virtual void render();
	};
}