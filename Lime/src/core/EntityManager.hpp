#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Pch.hpp"

class EntityManager{
public:
	EntityManager(){
		for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity){
			mAvailableEntities.push_back(entity);
		}
	}

	EntityID createEntity(){
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
		EntityID id = mAvailableEntities.front();
		mAllocdEntities.insert(id);
		mAvailableEntities.pop_front();
		++mLivingEntityCount;
		return id;
	}

	void destroyEntity(EntityID entity){
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		mArchetypes[entity].reset();
		mAvailableEntities.push_back(entity);
		mAllocdEntities.erase(entity);
		--mLivingEntityCount;
	}

	void setArchetype(EntityID entity, Archetype atype){
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		mArchetypes[entity] = atype;
	}

	Archetype getArchetype(EntityID entity){
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		return mArchetypes[entity];
	}

	bool hasComponent(EntityID entity, ComponentID compid) {
		return mArchetypes[entity].test(compid);
	}

public:
	std::deque<EntityID> mAvailableEntities{};
	std::set<EntityID> mAllocdEntities{};
	std::array<Archetype, MAX_ENTITIES> mArchetypes{};
	uint32_t mLivingEntityCount{};
};

#endif