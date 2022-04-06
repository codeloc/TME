#pragma once
#include "SFML/Graphics.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Camera.h"
#include <sstream>

class Grid
{
public:
	Grid(int cellSize, sf::Vector2i gridSize, Camera& camera);
	void Upadate();
	void Draw(tgui::CanvasSFML& canvas);
	void Draw(sf::RenderTexture& rt);

public:
	std::string GetDebugSStream();
	int GetClickedOnCellIndex(const sf::Vector2i& point);
public:
	void SetHorizontalLength(float length);
	void SetVerticalLength(float length);
	void SetColor(sf::Color c);
	void SetCellSize(int size);
	void SetGridSize(sf::Vector2i size);;

private:
	int cellSize = 64;
	sf::Vector2i gridSize = { 10,10 };
	sf::RectangleShape hLine;
	sf::RectangleShape vLine;
	Camera& camera;
	std::stringstream ss;
};

