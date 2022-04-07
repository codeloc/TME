#pragma once
#include "Map.h"
#include "ResourceManager.h"
#include <vector>
#include "TMGui.h"
#include "Grid.h"
#include "Camera.h"

class Editor
{
public:
	Editor(sf::RenderWindow& windowRef);
public:
	void HandleEvents(sf::Event& event);
	void Update();
	void Draw();

private:
	sf::RenderWindow* window;
	Map map;
	Grid mainGrid;
	tgui::CanvasSFML::Ptr canvas;
	TMGui gui;

	sf::View currentView;
	Camera camera;
	sf::Vector2i currWinSize;
	sf::Vector2i canvasOffset = { 10 ,35 };
	tgui::MessageBox::Ptr dbug;

	sf::Vector2f ratio = { 1.f, 1.f };
}; 

