#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

typedef std::shared_ptr<sf::Texture> TextureRef;
typedef std::shared_ptr<sf::Font> FontRef;

class ResourceManager
{
public:
public:
	bool LoadTexture(const std::string& name, const std::string& path);
	bool LoadFont(const std::string& name, const std::string& path);
	TextureRef GetTexture(const std::string& name);
	FontRef GetFont(const std::string& name);
	void MurderOrphans();
private:
	std::unordered_map<std::string, TextureRef> textures;
	std::unordered_map<std::string, FontRef> fonts;
};

