#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <sstream>
namespace DBUG
{
	enum class Type
	{
		INFO, ERROR
	};
	inline void Log(const std::string& msg, Type type = Type::INFO)
	{
		switch (type)
		{
		case DBUG::Type::INFO:
			std::cout << "Info: " <<  msg << std::endl;
			break;
		case DBUG::Type::ERROR:
			std::cout << "Error: " << msg << std::endl;
			break;
		default:
			break;
		}
		
	}
	inline void Log(int intNum, Type type = Type::INFO)
	{
		switch (type)
		{
		case DBUG::Type::INFO:
			std::cout << "Info: " << intNum << std::endl;
			break;
		case DBUG::Type::ERROR:
			std::cout << "Error: " << intNum << std::endl;
			break;
		default:
			break;
		}
	}
	inline void Log(float floatNum, Type type = Type::INFO)
	{
		switch (type)
		{
		case DBUG::Type::INFO:
			std::cout << "Info: " << floatNum << std::endl;
			break;
		case DBUG::Type::ERROR:
			std::cout << "Error: " << floatNum << std::endl;
			break;
		default:
			break;
		}
	}
	template<typename T>
	inline void Log(sf::Vector2<T> vec2)
	{
		Log(vec2.x);
		Log(vec2.y);
	}

}

namespace util
{
	template<class T>
	inline T Add2Values(T val1, T val2)
	{
		return val1 + val2;
	}
}
