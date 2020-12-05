#ifndef LIME_HPP
#define LIME_HPP

#include "Pch.hpp"
#include "components/CameraComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/PlayerComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "systems/ControllerSystem.hpp"
#include "systems/CameraSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "systems/BroadcastSystem.hpp"
#include "systems/DMSystem.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "SystemManager.hpp"
#include "ChrononManager.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "Types.hpp"

extern Grid gridmap;

class Lime
{
public:
	// serde
	template <typename T>
	inline void serializeComponent(ordered_json& j, const EntityID& entity) {
		if (hasComponent<T>(entity)) {
				const auto& component = getComponent<T>(entity);
				to_json(j, component);
		}
	}
	inline void serializeEntity(ordered_json& j, const EntityID& entity) {
		j["EntityID"] = entity;
		serializeComponent<TransformComponent>(j["TransformComponent"], entity);
		serializeComponent<PlayerComponent>(j["PlayerComponent"], entity);
		serializeComponent<ControllerComponent>(j["ControllerComponent"], entity);
		serializeComponent<SpriteComponent>(j["SpriteComponent"], entity);
		serializeComponent<CameraComponent>(j["CameraComponent"], entity);

	}

	template <typename T>
	inline void deserializeComponent(ordered_json& j, EntityID& entity) {
		T component;
		if (!j.is_null()) {
			from_json(j, component);
			addComponent(entity, component);
		}
	}
	inline void deserializeEntity(ordered_json& j, EntityID& entity) {
		entity = createEntity();
		if (j["EntityID"].is_null() || j["EntityID"] != entity) {
			j["EntityID"] = entity;
		}
		deserializeComponent<TransformComponent>(j["TransformComponent"], entity);
		deserializeComponent<PlayerComponent>(j["PlayerComponent"], entity);
		deserializeComponent<ControllerComponent>(j["ControllerComponent"], entity);
		deserializeComponent<SpriteComponent>(j["SpriteComponent"], entity);
		deserializeComponent<CameraComponent>(j["CameraComponent"], entity);
	}

	// load 
	void load(string filepath) {
		std::ifstream in(filepath);
		ordered_json j;
		in >> j;
		if (!j["Entities"].is_null()) {
			for (auto& entityjson : j["Entities"]) {
				EntityID entid;
				deserializeEntity(entityjson, entid);
			}
		}


		// doing the map loading 
		// will add this into the level json later 
		loadResource(gridmap, "Lime/maps/map_00.json");

		for (int i = 0; i < gridmap.rows ; ++i) {
			for (int j = 0; j < gridmap.cols; ++j) {
				std::cout << gridmap.cells[i][j].data << "";
				if (gridmap.cells[i][j].data == 1) {
					EntityID wall = createEntity();
					const int blocksize = 20;
					addComponent(wall, TransformComponent{
						glm::vec3{j * blocksize, (gridmap.rows-i-1) * blocksize,1.0f},
						glm::vec3{blocksize,blocksize,1.0f},
						glm::translate(glm::mat4(1.0f),glm::vec3{j*blocksize,(gridmap.rows-i-1)*blocksize,1.0f})
					});
					addComponent(wall, SpriteComponent{
						"Lime/res/grass.png",
						(GLuint)0,
						false,
						0.0f,
						1,
						1
					});
				}
			}
			std::cout << std::endl;
		}

		//for (int i = 0; i < gridmap.rows; ++i) {
		//	for (int j = 0; j < gridmap.cols; ++j) {
		//		if (gridmap.cells[i][j].data == 1) {

		//		}
		//	}
		//	std::cout << std::endl;
		//}



		LM_CORE_INFO("MAP LOADED !");



	}
	// save
	void save(string filepath) {
		std::ofstream out(filepath);
		ordered_json j;
		j["Entities"] = ordered_json::array();
		for (auto entity : mEntityManager->mAllocdEntities) {
			ordered_json json_ent;
			serializeEntity(json_ent, entity);
			j["Entities"].push_back(json_ent);
		}
		out << std::setw(4) << j;
	}
	// init
	void init(){

		Log::init();

		// REGISTER ALL ENUMS
		LIMEENUMS_MOUSEBUTTONS::stringify();
		LIMEENUMS_EVENTID::stringify();
		LIMEENUMS_PLAYERSTATES::stringify();
		LIMEENUMS_CAMERAMOVEMENTS::stringify();
		LIMEENUMS_SDL_SCANCODES::stringify();


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
		mGraphicsManager->init();
		mSystemManager->init();
		mResourceManager->init();

		registerComponent<TransformComponent>();
		registerComponent<ControllerComponent>();
		registerComponent<SpriteComponent>();
		registerComponent<CameraComponent>();
		registerComponent<PlayerComponent>();

		// register system and set its signature 
		registerSystem<ControllerSystem>();
		registerSystem<SpriteSystem>();
		registerSystem<CameraSystem>();
		registerSystem<BroadcastSystem>();
		registerSystem<DMSystem>();

		// Controller System
		{
			Archetype atype;
			atype.set(getComponentType<TransformComponent>());
			atype.set(getComponentType<ControllerComponent>());
			setSystemArchetype<ControllerSystem>(atype);
		}
		// Sprite System 
		{
			Archetype atype;
			atype.set(getComponentType<SpriteComponent>());
			setSystemArchetype<SpriteSystem>(atype);
		}

		// Camera Component
		{
			Archetype atype;
			atype.set(getComponentType<TransformComponent>());
			atype.set(getComponentType<ControllerComponent>());
			atype.set(getComponentType<CameraComponent>());
			setSystemArchetype<CameraSystem>(atype);
		}

		// Broadcast System
		{
			Archetype atype;
			atype.set(getComponentType<TransformComponent>());
			setSystemArchetype<BroadcastSystem>(atype);
		}

		// DirectMessage System
		{
			Archetype atype;
			atype.set(getComponentType<TransformComponent>());
			setSystemArchetype<DMSystem>(atype);
		}

		addEventListener(EventID::E_TIMED_EVENT, [this](Event& e) {this->onTimedEvent(e); });
		
		//Event timedevent1(EventID::E_TIMED_EVENT);
		//timedevent1.setParam<string>(EventID::P_TIMED_EVENT_DATA, "TEMPORAL MESSAGE TRIGGERED");
		//mEventManager->sendTimedEvent(timedevent1, 2000);


	}

	void systemInit() {
		mSystemManager->init();
	}

	void update() {
		mEventManager->update();
		mInputManager->update();
		mGraphicsManager->update();
		mSystemManager->update();
		mResourceManager->update();

	}

	void onEvent(Event& e) {
		mInputManager->onEvent(e);
		mGraphicsManager->onEvent(e);
		mSystemManager->onEvent(e);
		mResourceManager->onEvent(e);

	}

	void onTimedEvent(Event& e) {
		if (e.getType() == EventID::E_TIMED_EVENT) {
			const auto& msg = e.getParam<string>(EventID::P_TIMED_EVENT_DATA);
			const auto& start =  e.getParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_START);
			const auto& exec =  e.getParam<std::chrono::steady_clock::time_point>(EventID::P_TIMED_EVENT_TIME_EXEC);
			const auto& wait = std::chrono::duration_cast<std::chrono::milliseconds>(exec - start);
			LM_CORE_INFO("TIMED EVENT : {} - QUEUE WAIT : {} ms", msg, wait.count());
			Event timedevent1(EventID::E_TIMED_EVENT);
			timedevent1.setParam<string>(EventID::P_TIMED_EVENT_DATA, "TEMPORAL MESSAGE TRIGGERED");
			mEventManager->sendTimedEvent(timedevent1, 2000);

		}
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
	glm::vec2* getMousePosition() {
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
	template <typename T>
	bool hasComponent(EntityID entity) {
		const char* typeName = typeid(T).name();
		ComponentID comid = mComponentManager->getComponentType<T>();
		return mEntityManager->hasComponent(entity, comid);
	}

	bool hasComponent(EntityID entity, ComponentID comid) {
		return mEntityManager->hasComponent(entity, comid);
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


extern Lime gLimeEngine;

inline void sdlPoll() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_WINDOWEVENT) {
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				Event event(EventID::E_WINDOW_RESIZED);
				event.setParam<unsigned int>(EventID::P_WINDOW_RESIZED_WIDTH, e.window.data1);
				event.setParam<unsigned int>(EventID::P_WINDOW_RESIZED_HEIGHT, e.window.data2);
				gLimeEngine.sendEvent(event);
			}
		}
		else if (e.type == SDL_QUIT) {
			Event event(EventID::E_WINDOW_QUIT);
			gLimeEngine.sendEvent(event);
		}
		else if (gLimeEngine.mInputManager->isKeyPressed(SDL_SCANCODE_ESCAPE)) {
			Event e1(EventID::E_WINDOW_KEY_PRESSED);
			e1.setParam<SDL_Scancode>(P_WINDOW_KEY_PRESSED_KEYCODE, SDL_SCANCODE_ESCAPE);
			gLimeEngine.sendEvent(e1);
			Event e2(EventID::E_WINDOW_QUIT);
			gLimeEngine.sendEvent(e2);
		}
		else if (gLimeEngine.mInputManager->mouseMove(e)) {
			Event event(EventID::E_WINDOW_MOUSE_MOVE);
			event.setParam<float>(EventID::P_WINDOW_MOUSE_MOVE_X, gLimeEngine.mInputManager->mX());
			event.setParam<float>(EventID::P_WINDOW_MOUSE_MOVE_Y, gLimeEngine.mInputManager->mY());
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			Event event(EventID::E_WINDOW_MOUSE_DOWN);
			int button=0;
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				button = mouseButtons::LB;
				break;
			case SDL_BUTTON_MIDDLE:
				button = mouseButtons::MB;
				break;
			case SDL_BUTTON_RIGHT:
				button = mouseButtons::RB;
				break;
			default:
				break;
			}
			event.setParam<int>(EventID::P_WINDOW_MOUSE_DOWN_BUTTON, button);
			event.setParam<float>(EventID::P_WINDOW_MOUSE_DOWN_X, gLimeEngine.mInputManager->mX());
			event.setParam<float>(EventID::P_WINDOW_MOUSE_DOWN_Y, gLimeEngine.mInputManager->mY());
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			Event event(EventID::E_WINDOW_MOUSE_UP);
			int button = 0;
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				button = mouseButtons::LB;
				break;
			case SDL_BUTTON_MIDDLE:
				button = mouseButtons::MB;
				break;
			case SDL_BUTTON_RIGHT:
				button = mouseButtons::RB;
				break;
			default:
				break;
			}
			event.setParam<int>(EventID::P_WINDOW_MOUSE_UP_BUTTON, button);
			event.setParam<float>(EventID::P_WINDOW_MOUSE_UP_X, gLimeEngine.mInputManager->mX());
			event.setParam<float>(EventID::P_WINDOW_MOUSE_UP_Y, gLimeEngine.mInputManager->mY());
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				Event ebroadcast(EventID::E_BROADCAST_EVENT);
				ebroadcast.setParam<string>(EventID::P_BROADCAST_EVENT_DATA, "To infinity and beyond !");
				gLimeEngine.sendEvent(ebroadcast);
			}
			Event event(EventID::E_WINDOW_KEY_PRESSED);
			event.setParam<SDL_Scancode>(P_WINDOW_KEY_PRESSED_KEYCODE, e.key.keysym.scancode);
			gLimeEngine.sendEvent(event);
		}
		else if (e.type == SDL_KEYUP) {
			Event event(EventID::E_WINDOW_KEY_RELEASED);
			event.setParam<SDL_Scancode>(P_WINDOW_KEY_RELEASED_KEYCODE, e.key.keysym.scancode);
			gLimeEngine.sendEvent(event);
		}

	}

}

//EntityID box = createEntity();
//addComponent<TransformComponent>(box, TransformComponent{
//	glm::vec3{-1.0f,-3.0f,0.0f},
//	glm::mat4{1.0f}
//});
//addComponent<SpriteComponent>(box, SpriteComponent{
//	"Lime/res/gear.png",
//	0,
//	false,
//	0.0f,
//	1,
//	1
//});

//EntityID box2 = createEntity();
//addComponent<TransformComponent>(box2, TransformComponent{
//	glm::vec3{1.0f,13.0f,0.0f},
//	glm::mat4{1.0f}
//	});
//addComponent<SpriteComponent>(box2, SpriteComponent{
//	"Lime/res/gear.png",
//	0,
//	false,
//	0.0f,
//	1,
//	1
//	});

//EntityID camera = createEntity();
//addComponent<TransformComponent>(camera, TransformComponent{
//	glm::vec3{0.0f,0.0f,20.0f},
//	glm::mat4{1.0f}
//});
//addComponent<CameraComponent>(camera, CameraComponent{
//	glm::vec3{0.0f,0.0f,-1.0f},
//	glm::vec3{0.0f,1.0f,0.0f},
//	glm::vec3{1.0f,0.0f,0.0f},
//	glm::vec3{0.0f,1.0f,0.0f},
//	glm::mat4(1.0f),
//	glm::mat4(1.0f),
//	float {1.0f},
//	float {1.0f},
//	float {0.0f},
//	float {-90.0f},
//	float {1.0f},
//	int {0},
//	int {0},
//	int {400},
//	int {400},
//	bool {true},
//	glm::vec4{20,174,96,255}
//});

/*
addComponent<ControllerComponent>(box,ControllerComponent{
	SDL_SCANCODE_I,
	SDL_SCANCODE_K,
	SDL_SCANCODE_J,
	SDL_SCANCODE_L,
	SDL_SCANCODE_P,
	SDL_SCANCODE_U,
	SDL_SCANCODE_O,
	glm::vec3{1.0f,1.0f,1.0f}
});

EntityID box2 = createEntity();
addComponent<TransformComponent>(box2, TransformComponent{
	glm::vec3{-1.0f,-1.0f,0.0f},
	glm::mat4{1.0f}
	});
addComponent<SpriteComponent>(box2, SpriteComponent{
	"Lime/res/gear.png",
	0,
	false,
	0.0f,
	1,
	1
	});
addComponent<ControllerComponent>(box2, ControllerComponent{
	SDL_SCANCODE_I,
	SDL_SCANCODE_K,
	SDL_SCANCODE_J,
	SDL_SCANCODE_L,
	SDL_SCANCODE_P,
	SDL_SCANCODE_U,
	SDL_SCANCODE_O,
	glm::vec3{1.0f,1.0f,1.0f}
	});*/


#endif