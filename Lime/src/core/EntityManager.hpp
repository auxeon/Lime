/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: EntityManager.hpp
Purpose: EntityManager
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Pch.hpp"
#include "limits.h"

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
		if (mLivingEntityCount == UINT32_MAX && mAvailableEntities.size() > 0) {
			mLivingEntityCount = 0;
		}
		LM_CORE_TRACE("[Entity ID: {}] Entity created", id);
		return id;
	}

	void destroyEntity(EntityID entity){
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		mArchetypes[entity].reset();
		mAvailableEntities.push_back(entity);
		mAllocdEntities.erase(entity);
		--mLivingEntityCount;
		LM_CORE_TRACE("[Entity ID: {}] Entity destroyed", entity);
	}

	void setArchetype(EntityID entity, Archetype atype){
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		mArchetypes[entity] = atype;
		LM_CORE_TRACE("[Entity ID: {}] Archetype changed", entity);
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