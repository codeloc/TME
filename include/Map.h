#pragma once
#include "ResourceManager.h"
#include "SpriteAtlas.h"
#include "Utils.h"

using namespace util;

class Map
{
public:
	Map();
	void HandleEvents(sf::Event& event);
	void Update(sf::Vector2i mousePosition);
	void Draw(tgui::CanvasSFML& canvas);

	void OpenMap();
	void SaveMap();
	void ClearMap();
public:
	SpriteAtlas& GetAtlas();
	sf::Vector2i GetSize();
	int GetTileSize();
	int GetScale();
	FilePath& GetFile();
private:
	struct Tile
{
	int id;
	sf::Sprite sprite;
};
	Tile selectedTile;

	sf::Vector2i mapSize = { 10,10 }; // default
	int tileSize = 16;				  // default
	int tileScale = 4;				  // default
	std::vector<Tile> map;

	bool tileSelected = false;
	bool saved;
	bool startup;


	FilePath mapFile;

	SpriteAtlas sAtlas;
};

