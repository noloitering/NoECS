#include "Entity.h"

using namespace NoECS;

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
			new_map[a->getTag()].push_back(a);
		}
		toAdd.clear();
	}
	entities = new_map;
}

void EntityManager::clear()
{
	entities.clear();
	total = 0;
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

EntityVec EntityManager::getEntities()
{
	EntityVec result(total);
	for (auto it=entities.begin(); it != entities.end(); it++) // order by id
	{
		for (std::shared_ptr< Entity > e : it->second)
		{
			result.at(e->getId()) = e;
		}
	}
	EntityVec newVec;
	for (std::shared_ptr< Entity > e : result) // eliminate deleted entities
	{
		if ( e )
		{
			newVec.push_back(e);
		}
	}

	return newVec;
}

std::unordered_map<std::string, EntityVec>& EntityManager::getEntityMap()
{
	
	return entities;
}

EntityVec & EntityManager::getEntities(const std::string & tag)
{
	return entities[tag];
}

size_t EntityManager::getTotal()
{
	
	return total;
}

void EntityManager::setEntities(const EntityVec& vec)
{
	clear();
	for (auto elem : vec)
	{
		entities[elem->getTag()].push_back(elem);
		total++;
	}
}

void EntityManager::setEntities(const std::unordered_map<std::string, EntityVec>& map)
{
	clear();
	entities = map;
	for (auto elemTag : entities)
	{
		total += elemTag.second.size();
	}
}