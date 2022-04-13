#include "Map.h"
#include "Utils.h"
#include <fstream>

using namespace DBUG;

Map::Map()
{
}

void Map::HandleEvents(sf::Event& event)
{
}

void Map::Update(sf::Vector2i mousePosition)
{

}

void Map::Draw(tgui::CanvasSFML& canvas)
{
	if (!map.empty())
	{
		for (auto t : map)
		{
			canvas.draw(t.sprite);
		}
	}
	/*if (tileSelected && canvas.isMouseOnWidget((tgui::Vector2f)(sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		canvas.draw(selectedTile.sprite);
	}*/
}

void Map::OpenMap()
{
	saved = true; // if we just open a map from file its same state as saved
	startup = false;
	int id = 0;
	sf::Sprite sprite;
	sf::Vector2i position;
	std::ifstream in;
	std::string line;

	size_t count; // reading id/posX/posY
	size_t count2;
	size_t count3;

	in.open(mapFile.GetFilePath());
	if (in.is_open())
	{
		std::getline(in, line);
		sAtlas.SetFileDir(line);
		//ATLAS_FILE_DIR = line;

		std::getline(in, line);
		sAtlas.SetFileName(line);
		//ATLAS_FILE_NAME = line;

		std::getline(in, line);
		mapSize.x = std::stof(line);
		std::getline(in, line);
		mapSize.y = std::stof(line);
		std::getline(in, line);
		tileSize = std::stof(line);
		std::getline(in, line);
		tileScale = std::stof(line);

		map.clear();
		sAtlas.LoadSpriteSheet();
		sprite.setTexture(sAtlas.GetTexture());
		sprite.setScale(tileScale, tileScale);
		selectedTile.sprite.setTexture(sAtlas.GetTexture());
		selectedTile.sprite.setScale({ (float)tileScale,(float)tileScale });
		while (std::getline(in, line))
		{
			count = line.find(',');
			id = std::stoi(line.substr(0, count));
			count2 = line.find(',', count + 1);
			position.x = std::stoi(line.substr(count + 1, count2 - 1 - count));
			count3 = line.find(',', count2 + 1);
			position.y = std::stoi(line.substr(count2 + 1, count3 - 1 - count2));

			sprite.setPosition((sf::Vector2f)(position * (int)tileSize * (int)tileScale));
			int nCellsX = (int)sprite.getTexture()->getSize().x / tileSize;
			int nCellsY = (int)sprite.getTexture()->getSize().y / tileSize;

			sprite.setTextureRect({
				 ((id % nCellsX) * (int)tileSize),
				 ((id / nCellsY)  * (int)tileSize),
				 (int)tileSize,
				 (int)tileSize
				});
			// add tiles to map //
			map.push_back({ id,sprite });
		}
		in.close();
		Log("Map loaded");
	}
}

void Map::SaveMap()
{
}

void Map::ClearMap()
{
	if (!map.empty())
	{
		map.clear();
		Log("map cleared");
	}
}

SpriteAtlas& Map::GetAtlas()
{
	return sAtlas;
}

sf::Vector2i Map::GetSize()
{
	return mapSize;
}

int Map::GetTileSize()
{
	return tileSize;
}

int Map::GetScale()
{
	return tileScale;
}

FilePath& Map::GetFile()
{
	return mapFile;
}
