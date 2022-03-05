#include <unordered_map>
#include "Component.h"

namespace NoECS
{
	class Entity : public CContainer
	{
	private:
		const size_t id = 0;
		const std::string tag = "default";
		bool active = true;
	
	public:
		Entity(const size_t & i, const std::string & t, bool a=true)
			: id(i), tag(t), active(a) {}
		void destroy()
		{
			active = false;
		}
		
		bool isAlive()
		{
			
			return active;
		}
		
		const std::string& getTag()
		{
			
			return tag;
		}
		
		const size_t getId()
		{
			
			return id;
		}
		
	};
	
	typedef std::vector<std::shared_ptr< Entity > > EntityVec;

	class EntityManager
	{
	private:
		EntityVec toAdd;
		std::unordered_map<std::string, EntityVec> entities;
		size_t total = 0;
	public:
		EntityManager();
		void clear();
		void update();
		void removeEntity(std::shared_ptr<Entity> entity);
		std::shared_ptr<Entity> addEntity(const std::string& tag);
		size_t getTotal();
		EntityVec getEntities(); // in order of ID
		EntityVec& getEntities(const std::string& tag); // in map order
		std::unordered_map<std::string, EntityVec>& getEntityMap();
		void setEntities(const EntityVec& vec);
		void setEntities(const std::unordered_map<std::string, EntityVec>& map);
	};	
}