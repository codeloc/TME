#include "Editor.h"
#include <sstream>

Editor::Editor(sf::RenderWindow& windowRef)
	:
	window(&windowRef),
	mainGrid(16,4,{10,10}, camera)
{
	window->setFramerateLimit(60);

	currWinSize = (sf::Vector2i)window->getSize();
	canvasManager.Init(windowRef);
	canvas = tgui::CanvasSFML::create();
	canvas->setSize("70%");
	canvas->setPosition(10, 35);
	canvasManager.Add(canvas);

	currentView.setSize(canvas->getSize()) ;
	currentView.setCenter(currentView.getSize() / 2.f);
	camera.Init(windowRef, currentView);

	gui.Init(windowRef);
	InitGuiElements();
}

void Editor::HandleEvents(sf::Event& event)
{
	gui.HandleEvents(event);
	auto mousePosition = sf::Mouse::getPosition(*window);
	switch (event.type)
	{
		case sf::Event::Resized:
		{
			sf::Vector2i newSize = { (int)event.size.width , (int)event.size.height };
			ratio = sf::Vector2f((float)newSize.x / 1280.f, (float)newSize.y / 720.f);

			// this (r)atio is relative to prev size while (ratio) is relative to original size
			sf::Vector2f r = sf::Vector2f((float)newSize.x / currWinSize.x, (float)newSize.y / currWinSize.y);
			
			// we are calculating this cuz tgui stupid, var canvasPosition is fixed
			canvas->setPosition(canvas->getPosition().x / r.x, canvas->getPosition().y / r.y); 
			currWinSize = newSize;
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				auto point = mousePosition - canvasPosition;
				mainGrid.GetClickedOnCellIndex(point);
			}
		}
	}
	camera.HandleEvents(event);
	mainGrid.HandleEvents(event, ratio);
	
}

void Editor::Update()
{
	currentView = camera.GetView();
	canvas->setView(currentView);

	mainGrid.Update();
}

void Editor::Draw()
{
	canvas->clear({ 40,40,40 });
	map.Draw(*canvas);
	mainGrid.Draw(*canvas);
	canvasManager.Draw();
	gui.Draw();
	canvas->display();
}

void Editor::InitGuiElements()
{
	tgui::Theme black{ "dependencies/TGUI/themes/Black.txt" };
	// init menu bar //
	auto menuBarLayout = tgui::BoxLayout::create();
	menuBarLayout->setHeight(35);

	auto mainMenuBar = tgui::MenuBar::create();

	mainMenuBar->addMenu("Map");
	mainMenuBar->addMenuItem("Map", "New");			// make a new map (mapsize,tilesize,scalefactor)
	mainMenuBar->addMenuItem("Map", "Open");		// open a map file, read and recreate in the editor
	mainMenuBar->addMenuItem("Map", "Save");		// save file
	mainMenuBar->addMenuItem("Map", "Clear");		// clear al placed tiles in map

	auto mbr = mainMenuBar->getRenderer();
	mbr->setBackgroundColor(gui.backgroundColor);
	mbr->setSelectedBackgroundColor(gui.selectedBackgroundColor);
	mbr->setTextColor(tgui::Color::White);
	mbr->setTextSize(14);

	mainMenuBar->onMenuItemClick(&Editor::MenuBarCallback, this); // finds menu->item and passes it into callback as para
	menuBarLayout->add(mainMenuBar);
	gui.Add(menuBarLayout);
}

void Editor::MenuBarCallback(const tgui::String& item)
{
	// Map //
	//if (item == "New")
	//{
	//	if (!saved)
	//	{
	//		SaveMsgBox(); // calls CreateNewMap() if button pressed
	//	}
	//	if (saved)
	//	{
	//		CreateNewMap();
	//	}
	//}
	if (item == "Open")
	{
		OpenFile("Map");
	}
	//else if (item == "Save")
	//{
	//	SaveMap();
	//}
	if (item == "Clear")
	{
		map.ClearMap();
	}
	//// Sprite //
	//else if (item == "Open sprite sheet")
	//{
	//	OpenFileDialog("Sprite");
	//}
}

void Editor::OpenFile(std::string parent)
{
	if (parent == "Map")
	{
		auto openFileDialog = tgui::FileDialog::create("Open map", "Open");
		openFileDialog->setOrigin(0.5f, 0.5f);
		openFileDialog->setPosition("50%");

		openFileDialog->onFileSelect([=] {
			map.GetFile().SetFilePath(std::string(openFileDialog->getSelectedPaths()[0].asString()));
			map.GetFile().SetFileDir(std::string(openFileDialog->getSelectedPaths()[0].getParentPath().asString()));
			map.GetFile().SetFileName(std::string(openFileDialog->getSelectedPaths()[0].getFilename()));
			map.OpenMap();

			mainGrid.SetGridSize(this->map.GetSize());
			mainGrid.SetCellSize(this->map.GetTileSize());
			openFileDialog->close();
			});
		gui.Add(openFileDialog);
	}
}
