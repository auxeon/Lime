#ifndef LIME_HPP
#define LIME_HPP

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "SystemManager.hpp"
#include "ChrononManager.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "Types.hpp"


class Lime
{
public:
	// serde
	void serialize(EntityID entity) {

	}

	EntityID deserialize(json j) {

	}

	// load 
	void load(string filepath) {

	}
	// save
	void save(string filepath) {

	}
	// init
	void init(){
		// ECS
		mEntityManager = std::make_unique<EntityManager>();
		mComponentManager = std::make_unique<ComponentManager>();
		mSystemManager = std::make_unique<SystemManager>();
		mEventManager = std::make_unique<EventManager>();
		// OTHER
		mChrononManager = std::make_unique<ChrononManager>();
		mInputManager = std::make_unique<InputManager>();
		mGraphicsManager = std::make_unique<GraphicsManager>();
		mResourceManager = std::make_unique<ResourceManager>();
		mIsRunning = true;
		dt = 0.0;
		
		// set defaults 
		setMaxFPS(60);

		// call init methods of managers
		mInputManager->init();
		mSystemManager->init();
		mGraphicsManager->init();
		mResourceManager->init();
	}

	void update() {
		mInputManager->update();
		mSystemManager->update();
		mGraphicsManager->update();
		mResourceManager->update();
	}

	void onEvent(Event& e) {
		mInputManager->onEvent(e);
		mSystemManager->onEvent(e);
		mGraphicsManager->onEvent(e);
		mResourceManager->onEvent(e);
	}

	// wrappers for manager functions

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

	// InputManager
	bool isKeyPressed(SDL_Scancode keycode) {
		return mInputManager->isKeyPressed(keycode);
	}
	bool isKeyReleased(SDL_Scancode keycode) {
		return mInputManager->isKeyReleased(keycode);
	}
	bool isKeyTriggered(SDL_Scancode keycode) {
		return mInputManager->isKeyTriggered(keycode);
	}
	void mouseButtonDown(SDL_Event event = SDL_Event()) {
		mInputManager->mouseButtonDown(event);
	}
	bool mouseMove(SDL_Event event = SDL_Event()) {
		return mInputManager->mouseMove(event);
	}
	void mouseButtonUp(SDL_Event event = SDL_Event()) {
		mInputManager->mouseButtonUp(event);
	}
	bool getMouseButtonState(int buttonnumber) {
		return mInputManager->getMouseButtonState(buttonnumber);
	}
	LMVec2* getMousePosition() {
		return mInputManager->getMousePosition();
	}
	float mX() {
		return mInputManager->mX();
	}
	float mY() {
		return mInputManager->mY();
	}

	// GraphicsManager
	void printGraphicsInfo() {
		mGraphicsManager->printInfo();
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

	// ResourceManager
	template <typename T>
	T& getOrLoadResource(string resloc) {
		return mResourceManager->get<T>(resloc);
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
	std::unique_ptr<InputManager> mInputManager;
	std::unique_ptr<ResourceManager> mResourceManager;
	bool mIsRunning = false;
	double dt;
};

#endif