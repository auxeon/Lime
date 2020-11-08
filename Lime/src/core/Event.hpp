#ifndef EVENT_HPP
#define EVENT_HPP
#include "Pch.hpp"

class Event{
public:
	Event() = delete;

	explicit Event(EventID type): mType(type){

	}

	template<typename T>
	void setParam(EventID id, T value){
		mData[id] = value;
	}

	template<typename T>
	T getParam(EventID id){
		return std::any_cast<T>(mData[id]);
	}

	EventID getType() const{
		return mType;
	}

private:
	EventID mType{};
	std::unordered_map<EventID, std::any> mData{};
};

#endif