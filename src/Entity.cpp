#include "Entity.h"

EntityManager::EntityManager()
{
	
}

void EntityManager::update()
{
	std::unordered_map<std::string, EntityVec> new_map;
	for (auto me : entities)
	{
		for (int elemIndex=0; elemIndex < me.second.size(); elemIndex++)
		{
			auto e = me.second[elemIndex];
			if ( e->isAlive() )
			{
				new_map[me.first].push_back(e);
			}
		}
	}
	if (!toAdd.empty())
	{
		for (auto a : toAdd)
		{
			new_map[a->tag()].push_back(a);
		}
		toAdd.clear();
	}
	entities = new_map;
}

void EntityManager::clearEntities()
{
	entities.clear();
}

void EntityManager::removeEntity(std::shared_ptr<Entity> entity)
{
	entity->destroy();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(total++, tag));
	toAdd.push_back(e);
	return e;
}

EntityVec & EntityManager::getEntities()
{
	EntityVec result;
	
	for (auto it=entities.begin(); it != entities.end(); it++)
	{
		for (std::shared_ptr< Entity > e : it->second)
		{
			result.push_back(e);
		}
	}
	
	return result;
}

EntityVec & EntityManager::getEntities(const std::string & tag)
{
	return entities[tag];
}