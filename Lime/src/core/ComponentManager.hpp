/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: ComponentManager.hpp
Purpose: Component management
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include "Pch.hpp"
#include "core/ComponentContainer.hpp"

class ComponentManager{
public:
	template<typename T>
	void registerComponent(){
		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");
		mComponentTypes.insert({ typeName, mNextComponentID });
		mComponentContainers.insert({ typeName, std::make_shared<ComponentContainer<T>>() });
		LM_CORE_TRACE("[Component ID: {}] Component registered", mNextComponentID);
		++mNextComponentID;
	}

	template<typename T>
	ComponentID getComponentType(){
		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");
		return mComponentTypes[typeName];
	}

	template<typename T>
	void addComponent(EntityID entity, T component){
		getComponentContainer<T>()->insert(entity, component);
		LM_CORE_TRACE("[Entity ID: {}] Component {} added", entity, getComponentType<T>());
	}

	template<typename T>
	void removeComponent(EntityID entity){
		auto comID = getComponentType<T>();
		getComponentContainer<T>()->remove(entity);
		LM_CORE_TRACE("[Entity ID: {}] Component {} removed", entity, comID);
	}

	template<typename T>
	T& getComponent(EntityID entity){
		return getComponentContainer<T>()->getData(entity);
	}

	void entityDestroyed(EntityID entity){
		for (auto const& pair : mComponentContainers){
			auto const& component = pair.second;
			component->entityDestroyed(entity);
		}
	}

//private:
public:
	std::unordered_map<const char*, ComponentID> mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentContainer>> mComponentContainers{};
	ComponentID mNextComponentID{};


	template<typename T>
	std::shared_ptr<ComponentContainer<T>> getComponentContainer(){
		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentContainer<T>>(mComponentContainers[typeName]);
	}
};

#endif