#pragma once
#include "ResourceManager.h"

class Map
{
public:
	void HandleEvents(sf::Event& event);
	void Update(sf::Vector2i mousePosition);
	void Draw();
private:

private:
	struct Tile
{
	int id;
	sf::Sprite sprite;
};
	class Layer
	{
	public:
		std::vector<Tile> tiles;
	};

	sf::Vector2i mapSize = { 10,10 }; // default
	int tileSize = 16;				  // default
	int tileScale = 4;				  // default
	std::vector<Layer> map;
	Layer activeLayer;
};

