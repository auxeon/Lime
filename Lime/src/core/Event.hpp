/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Event.hpp
Purpose: Description of event
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/

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

	string getTypeName() const {
		return typeid(mType).name();
	}

private:
	EventID mType{};
	std::unordered_map<EventID, std::any> mData{};
};

#endif