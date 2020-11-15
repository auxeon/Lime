#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include "Pch.hpp"
#include "Types.hpp"
#include "Event.hpp"
// if windows
#ifdef _WIN64
#include "platform/windows/ResourceLoader.hpp"
#endif

// if macos
#ifdef __APPLE__
#include "platform/macos/ResourceLoader.hpp"
#endif
// for now supports only loading textures 
class ResourceManager {
public:
	void init() {
		mNextRes = 0;
	}
	void onEvent(Event& e) {

	}
	void update() {

	}
	template <typename T>
	T& get(std::string resloc) {
		ResourceID id;
		if (mResID.count(resloc)>0) {
			id = mResID[resloc];
			return std::any_cast<T>(mResPool[id]);
		}
		mNextRes += 1;
		mResID[resloc] = mNextRes;
		mResPool[mNextRes] = loadResource<T>(resloc);
	}
private:
	std::unordered_map<std::string, ResourceID> mResID;
	std::unordered_map<ResourceID, std::any> mResPool;
	ResourceID mNextRes;

};
#endif // !RESOURCEMANAGER_HPP