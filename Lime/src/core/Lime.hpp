#ifndef LIME_HPP
#define LIME_HPP

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "SystemManager.hpp"
#include "Types.hpp"


class Lime
{
public:
	// init
	void init(){
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mEventManager = std::make_unique<EventManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}


	// entity
	EntityID createEntity(){
		return mEntityManager->createEntity();
	}

	void destroyEntity(EntityID entity){
		mEntityManager->destroyEntity(entity);
		mComponentManager->entityDestroyed(entity);
		mSystemManager->entityDestroyed(entity);
	}

	// component
	template<typename T>
	void registerComponent(){
		mComponentManager->registerComponent<T>();
	}

	template<typename T>
	void addComponent(EntityID entity, T component){
		mComponentManager->addComponent<T>(entity, component);
		auto atype = mEntityManager->getArchetype(entity);
		atype.set(mComponentManager->getComponentType<T>(), true);
		mEntityManager->setArchetype(entity, atype);
		mSystemManager->entityArchetypeChanged(entity, atype);
	}

	template<typename T>
	void removeComponent(EntityID entity){
		mComponentManager->removeComponent<T>(entity);
		auto atype = mEntityManager->getArchetype(entity);
		atype.set(mComponentManager->getComponentType<T>(), false);
		mEntityManager->setArchetype(entity, atype);
		mSystemManager->entityArchetypeChanged(entity, atype);
	}

	template<typename T>
	T& getComponent(EntityID entity){
		return mComponentManager->getComponent<T>(entity);
	}

	template<typename T>
	ComponentID getComponentType(){
		return mComponentManager->getComponentType<T>();
	}

	// system
	template<typename T>
	std::shared_ptr<T> registerSystem(){
		return mSystemManager->registerSystem<T>();
	}

	template<typename T>
	void SetSystemArchetype(Archetype atype){
		mSystemManager->setArchetype<T>(atype);
	}


	// event 
	void addEventListener(EventID eventId, std::function<void(Event&)> const& listener){
		mEventManager->addListener(eventId, listener);
	}

	void sendEvent(Event& event){
		mEventManager->sendEvent(event);
	}

	void sendEvent(EventID eventId){
		mEventManager->sendEvent(eventId);
	}

public:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<EventManager> mEventManager;
	std::unique_ptr<SystemManager> mSystemManager;
};

#endif