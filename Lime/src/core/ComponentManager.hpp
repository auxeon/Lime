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
	}

	template<typename T>
	void removeComponent(EntityID entity){
		getComponentContainer<T>()->remove(entity);
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