#include "Entity.h"

namespace NoECS
{	
	class EntitySystem : public Model
	{
	public:
		EntitySystem() {}
		virtual ~EntitySystem() {}
		EntityManager entities;
		virtual void update();
		virtual void render();
	};
}