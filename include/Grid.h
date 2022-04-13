#pragma once
#include "SFML/Graphics.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Camera.h"
#include <sstream>

class Grid
{
public:
	Grid(int cellSize, int cellScale, sf::Vector2i gridSize, Camera& camera);
	void Update();
	void Draw(tgui::CanvasSFML& canvas);

public:
	int GetClickedOnCellIndex(const sf::Vector2i& point);
	void HandleEvents(sf::Event& event, sf::Vector2f ratio);
public:
	void SetColor(sf::Color c);
	void SetCellSize(int size);
	void SetGridSize(sf::Vector2i size);;

private:
	int cellSize = 16;
	int cellScale = 4;
	sf::Vector2i gridSize = { 10,10 };
	sf::RectangleShape hLine;
	sf::RectangleShape vLine;
	Camera& camera;

	// used for scaling line width when resizing
	sf::Vector2f ratio = { 1.f, 1.f };
};

