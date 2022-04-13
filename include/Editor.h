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
	void InitGuiElements();
	void MenuBarCallback(const tgui::String& item);
	void OpenFile(std::string parent);
private:
	sf::RenderWindow* window;
	Map map;
	Grid mainGrid;
	tgui::CanvasSFML::Ptr canvas;
	TMGui canvasManager;
	TMGui gui;

	sf::View currentView;
	Camera camera;
	sf::Vector2i currWinSize;
	sf::Vector2i canvasPosition = { 10 ,35 };

	sf::Vector2f ratio = { 1.f, 1.f };

	sf::Vector2i mapSize;
	sf::Vector2f tileSize;
}; 

