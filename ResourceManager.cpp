#include "ResourceManager.h"
#include "Utils.h"
bool ResourceManager::LoadTexture(const std::string& name, const std::string& path)
{
	DBUG::Log("Loading texture...", DBUG::Type::INFO);
	auto pTex = std::make_shared<sf::Texture>();
	if (pTex->loadFromFile(path))
	{
		textures.insert({ name,pTex });
		return true;
	}
	// load from file has debug output;
	return false;
}

bool ResourceManager::LoadFont(const std::string& name, const std::string& path)
{
	DBUG::Log("Loading font...", DBUG::Type::INFO);
	auto pFont = std::make_shared<sf::Font>();
	if (pFont->loadFromFile(path))
	{
		fonts.insert({ name,pFont });
		return true;
	}
	// load from file has debug output;
	return false;
}

TextureRef ResourceManager::GetTexture(const std::string& name)
{
	const auto i = textures.find(name);
	if(i != textures.end())
	{
		return i->second;
	}
	return nullptr;
}

FontRef ResourceManager::GetFont(const std::string& name)
{
	const auto i = fonts.find(name);
	if (i != fonts.end())
	{
		return i->second;
	}
	return nullptr;
}

void ResourceManager::MurderOrphans()
{
	for (auto i = textures.begin(); i != textures.end();)
	{
		if (i->second.use_count() == 1)
		{
			i = textures.erase(i);
		}
		else
		{
			++i;
		}
	}
	for (auto i = fonts.begin(); i != fonts.end();)
	{
		if (i->second.use_count() == 1)
		{
			i = fonts.erase(i);
		}
		else
		{
			++i;
		}
	}
}
