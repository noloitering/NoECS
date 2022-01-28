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
}