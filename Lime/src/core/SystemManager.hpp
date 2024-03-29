#ifndef SYSTEMMANAGER_HPP
#define SYSTEMANAGER_HPP

#include "Pch.hpp"
#include "core/System.hpp"

class SystemManager{
public:
	template<typename T>
	std::shared_ptr<T> registerSystem(){
		const char* typeName = typeid(T).name();
		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");
		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void setArchetype(Archetype atype){
		const char* typeName = typeid(T).name();
		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");
		mArchetypes.insert({ typeName, atype });
	}

	void entityDestroyed(EntityID entity){
		for (auto const& pair : mSystems){
			auto const& system = pair.second;
			system->mEntities.erase(entity);
		}
	}

	void entityArchetypeChanged(EntityID entity, Archetype entityArchetype){
		for (auto const& pair : mSystems){
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemArchetype = mArchetypes[type];

			if ((entityArchetype & systemArchetype) == systemArchetype){
				system->mEntities.insert(entity);
			}
			else{
				system->mEntities.erase(entity);
			}
		}
	}

private:
	std::unordered_map<const char*, Archetype> mArchetypes{};
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};


#endif