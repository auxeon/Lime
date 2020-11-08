#ifndef LIME_HPP
#define LIME_HPP

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "SystemManager.hpp"
#include "ChrononManager.hpp"
#include "GraphicsManager.hpp"
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
		mChrononManager = std::make_unique<ChrononManager>();
		mGraphicsManager = std::make_unique<GraphicsManager>();
		mIsRunning = true;
		dt = 0.0;
		
		// set defaults 
		setMaxFPS(60);

		//Managers that have an explicit initialization
		mGraphicsManager->init();
	}
	// GraphicsManager
	void initGraphics() {
		mGraphicsManager->init();
	}
	void printGraphicsInfo() {
		mGraphicsManager->printInfo();
	}
	void updateGraphics() {
		mGraphicsManager->update();
	}
	string getGraphicsWindowTitle() {
		return mGraphicsManager->getWindowTitle();
	}
	void setGraphicsWindowTitle(string s) {
		mGraphicsManager->setWindowTitle(s);
	}
	void resizeGraphicsWindow(unsigned int w, unsigned int h) {
		mGraphicsManager->resize(w, h);
	}

	// ChrononManager
	void startFrame() {
		mChrononManager->startframe();
	}

	void endFrame() {
		mChrononManager->endFrame();
		dt = mChrononManager->updatedt();
	}

	double getFPS() {
		return mChrononManager->getFPS();
	}

	void setMaxFPS(unsigned int maxfps) {
		mChrononManager->setMaxFPS(maxfps);
	}

	double getUptime() {
		return mChrononManager->getUptime();
	}

	long long getTotalFrames() {
		return mChrononManager->getTotalFrames();
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
	void setSystemArchetype(Archetype atype){
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
	std::unique_ptr<ChrononManager> mChrononManager;
	std::unique_ptr<GraphicsManager> mGraphicsManager;
	bool mIsRunning = false;
	double dt;
};

#endif