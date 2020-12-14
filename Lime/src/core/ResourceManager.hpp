/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.hpp
Purpose: Manage Resources
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include "Pch.hpp"
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
			return std::any_cast<T&>(mResPool[id]);
		}
	
		mResID[resloc] = mNextRes;
		T res;
		loadResource(res,resloc);
		mResPool[mNextRes] = res;
		++mNextRes;
		return std::any_cast<T&>(mResPool[mNextRes-1]);
	}
private:
	std::unordered_map<std::string, ResourceID> mResID;
	std::unordered_map<ResourceID, std::any> mResPool;
	ResourceID mNextRes;

};
#endif // !RESOURCEMANAGER_HPP