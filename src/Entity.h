#include "Component.h"

namespace ECS
{
	class Entity : public CContainer
	{
	private:
		const size_t m_id = 0;
		const std::string m_tag = "default";
		bool m_active = true;
	
		void destroy()
		{
			m_active = false;
		}
	public:
		Entity(const size_t & id, const std::string & tag, bool active = true)
			: m_id(id), m_tag(tag), m_active(active) {}
	};
	
	typedef std::vector<std::shared_ptr<Entity>> EntityVec;

	class EntityManager
	{
	private:
		EntityVec toAdd;
		std::unordered_map<std::string, EntityVec> entities;
		size_t total = 0;
	public:
		EntityManager();
		void clearEntities();
		void update();
		void removeEntity(std::shared_ptr<Entity> entity);
		std::shared_ptr<Entity> addEntity(const std::string & tag);
		EntityVec & getEntities();
		EntityVec & getEntities(const std::string & tag);
	};	
}