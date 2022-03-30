#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "ResourceManager.h"
#include <vector>
struct Tile {
	int id;
	sf::Sprite sprite;
};
struct Grid
{
	int size;
	int x;
	int y;
	sf::RectangleShape hLine;
	sf::RectangleShape vLine;
};

class Editor
{
public:
	void Init(sf::RenderWindow& window);
	void Update(sf::Event& event);
	void Draw();
private:
	void CreateNewMap();
	void MakeNewFile();
	void OpenMap();
	void SaveMap();
	void ClearMap();
private:
	void DrawMap();
	void SelectTile(const sf::Vector2i& mousePosition);
	void AddTileToMap(const Tile& tile);
	bool CheckLocationIsFree(const Tile& tile);
	void OverrideLocation(const Tile& tile);

public:
	void DrawMainGrid();
	void SaveMsgBox();
	void MenuBarItemClickedCallback(const tgui::String& item);
	void SaveMsgBoxBtnClickedCallback(const tgui::String& btn);
	void OpenFileDialog(std::string parent);
	void SaveFileDialog();
private:
	void GuiLoadSpriteSheet();
	void UpdateCanvasView(sf::Event& event);
	
private:
	Tile selectedTile;
	bool tileIsSelected = false;
	float tileSize = 16.f;
	float tileScaleFactor = 4.f;
	int selectedTileIndex;
	
	sf::Vector2f mapSize = {50.f,50.f};
	sf::Vector2i spriteSheetSize = { 4,4 }; // Row/Col
	std::vector<Tile> map;
	// Resources //
	ResourceManager resManager;
	// GUI //
	sf::RenderWindow* window;
	tgui::CanvasSFML::Ptr canvas;
	tgui::Gui gui;
	sf::Sprite test;
	tgui::ChildWindow::Ptr createNewMapWindow;
	// File System //
	std::string newMapFilePath;
	std::string spriteSheetTextureName;
	std::string spriteSheetTextureDirectory;
	Grid mainGrid;
	bool saved = true;
	bool startUp = true;
	bool mapTextureLoaded = false; // sprite sheet
	sf::Vector2f zoomFactor; // view size change in %
	float zoomTick = 1.f; // nTick offset from original view size
	sf::Vector2f originalViewSize = {876.f,484.f};
	sf::Vector2f originalCanvasSize = { 876.f,484.f };
	tgui::Vector2f dragOldMousePosition;
	sf::View currentView;
	tgui::ChildWindow::Ptr dbug;
}; 

