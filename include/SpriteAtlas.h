#pragma once
#include "Utils.h"
#include "ResourceManager.h"
using namespace util;

class SpriteAtlas
{
public:
	void SetFilePath(FilePath fullpath);
	void SetFileDir(std::string dir);
	void SetFileName(std::string name);
	void LoadSpriteSheet();
	FilePath GetFilePath();
	sf::Texture& GetTexture();
private:
	FilePath filePath;
	ResourceManager resManager;
};

