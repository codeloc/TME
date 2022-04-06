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
	template<typename T>
	inline void Log(const tgui::Vector2<T>& obj)
	{
		std::cout << obj.x << " " << obj.y << std::endl;
	}
	template<typename S>
	inline void Log(sf::Vector2<S> vec2)
	{
		std::cout << vec2.x << " " << vec2.y << std::endl;
	}
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
	

}

namespace util
{
	template<class T>
	inline T Add2Values(T val1, T val2)
	{
		return val1 + val2;
	}
}
