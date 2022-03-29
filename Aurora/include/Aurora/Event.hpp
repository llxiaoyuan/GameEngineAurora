#pragma once

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include<map>
#include<functional>

class Event
{
	typedef void HandlerT();
	int handlerID;

public:

	Event() :handlerID(0) {}

	template<class ObjT, class FuncT> int addHandler(ObjT obj, FuncT func)
	{
		handlers.emplace(handlerID, std::bind(func, std::forward<ObjT>(obj)));
		return handlerID++;
	}

	void removeHandler(const int& handlerID)
	{
		handlers.erase(handlerID);
	}

	void operator()()
	{
		for (const auto& i : handlers)
		{
			i.second();
		}
	}

private:

	std::map<int, std::function<HandlerT>> handlers;

};

#endif // !_EVENT_HPP_
