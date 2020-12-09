#ifndef COMPONENTCONTAINER_HPP
#define COMPONENTCONTAINER_HPP

#include "Pch.hpp"



class IComponentContainer{
public:
	virtual ~IComponentContainer() = default;
	virtual void entityDestroyed(EntityID entity) = 0;
};


template<typename T>
class ComponentContainer : public IComponentContainer{
public:
	void insert(EntityID entity, T component){
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");
		size_t newIndex = mCount;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentContainer[newIndex] = component;
		++mCount;
	}

	void remove(EntityID entity){
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into end where element got deleted to keep density
		size_t indexOfRemovedEntityID = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mCount - 1;
		mComponentContainer[indexOfRemovedEntityID] = mComponentContainer[indexOfLastElement];

		// Update map
		EntityID entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntityID;
		mIndexToEntityMap[indexOfRemovedEntityID] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		--mCount;

	}

	T& getData(EntityID entity){
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");
		return mComponentContainer[mEntityToIndexMap[entity]];
	}

	void entityDestroyed(EntityID entity) override{
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()){
			remove(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> mComponentContainer{};
	std::unordered_map<EntityID, size_t> mEntityToIndexMap{};
	std::unordered_map<size_t, EntityID> mIndexToEntityMap{};
	size_t mCount{};
};

#endif