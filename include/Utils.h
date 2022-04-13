#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <sstream>

namespace DBUG
{
using namespace DBUG;

	enum class Type
	{
		INFO, ERROR
	};

	template<typename T>
	inline void Log(const tgui::Vector2<T>& obj)
	{
		std::cout << obj.x << " " << obj.y << std::endl;
	}
	template<typename T>
	inline void Log(sf::Vector2<T> vec2)
	{
		std::cout << vec2.x << " " << vec2.y << std::endl;
	}
	inline void Log(const std::string& msg, Type type = Type::INFO)
	{
		switch (type)
		{
		case Type::INFO:
			std::cout << "Info: " <<  msg << std::endl;
			break;
		case Type::ERROR:
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
		case Type::INFO:
			std::cout << "Info: " << intNum << std::endl;
			break;
		case Type::ERROR:
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
		case Type::INFO:
			std::cout << "Info: " << floatNum << std::endl;
			break;
		case Type::ERROR:
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

	class FilePath
	{
	public:
		void SetFilePath(std::string fullpath) { MAP_FILE_PATH = fullpath; }
		void SetFileDir(std::string fileDir) { MAP_FILE_DIR = fileDir; }
		void SetFileName(std::string fileName)	{ MAP_FILE_NAME = fileName; }

		std::string GetFilePath() { return MAP_FILE_PATH; }
		std::string GetFileDir() { return MAP_FILE_DIR; }
		std::string GetFileName() { return MAP_FILE_NAME; }

		bool IsEmpty() { return MAP_FILE_PATH == ""; }
	private:
		std::string MAP_FILE_PATH = ""; // DIR + NAME
		std::string MAP_FILE_DIR = "";
		std::string MAP_FILE_NAME = "";
	};
}
