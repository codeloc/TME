#include "Editor.h"
#include <fstream>
#include "Utils.h"
#include <exception>
void Editor::Init(sf::RenderWindow& newWindow)
{
	window = &newWindow;
	resManager.LoadFont("Consolab", "./Assets/consolab.ttf");
	gui.setWindow(*window);
	gui.setFont(tgui::Font::Font("./Assets/consola.ttf"));
	gui.getFont().setSmooth(true);

	dbug = tgui::ChildWindow::create();

	// Init Gui //
	{
		int padding = 10;
		tgui::Theme theme("D:/TGUI-0.10-nightly/themes/Black.txt");

		// Menu Bar // menuBar
		auto menuBar = tgui::BoxLayout::create();
		menuBar->setHeight(25);

		// Main Menu Bar // 
		auto mainMenuBar = tgui::MenuBar::create();
		auto mainMenuRenderer = mainMenuBar->getRenderer();
		{
			mainMenuBar->addMenu("Map");
			mainMenuBar->addMenuItem("Map", "New");		// make a new map (mapsize,tilesize,scalefactor)
			mainMenuBar->addMenuItem("Map", "Open");		// open a map file, read and recreate in the editor
			mainMenuBar->addMenuItem("Map", "Save");		// save file
			mainMenuBar->addMenuItem("Map", "Clear");		// clear al placed tiles in map

			mainMenuRenderer->setBackgroundColor({ 66,64,62 });
			mainMenuRenderer->setTextColor(tgui::Color::White);
			mainMenuRenderer->setSelectedBackgroundColor({ 76,74,72 });

			mainMenuBar->onMenuItemClick(&Editor::MenuBarItemClickedCallback, this); // finds menu->item and passes it into callback as para
		}

		// Second Menu Bar //
		auto secondMenuBar = tgui::MenuBar::create();
		auto secondMenuRenderer = secondMenuBar->getRenderer();
		{
			secondMenuBar->addMenu("Sprite");
			secondMenuBar->addMenuItem("Sprite", "Open sprite sheet");

			secondMenuRenderer->setBackgroundColor({ 66,64,62 });
			secondMenuRenderer->setTextColor(tgui::Color::White);
			secondMenuRenderer->setSelectedBackgroundColor({ 76,74,72 });

			secondMenuBar->setPosition("70%", 0);
			secondMenuBar->onMenuItemClick(&Editor::MenuBarItemClickedCallback, this); // finds menu->item and passes it into callback as para
			
			menuBar->add(mainMenuBar);
			menuBar->add(secondMenuBar);
			gui.add(menuBar);
		}

		
		// SFML CANVAS //
		canvas = tgui::CanvasSFML::create("70% - 20.f"); // 2 * padding
		{
			//originalViewSize = canvas->getView().getSize();
			//originalCanvasSize = canvas->getView().getSize();
			canvas->setPosition(padding, tgui::bindHeight(menuBar) + padding);
			canvas->setView({ {originalViewSize / 2.f},originalViewSize });
			currentView = { {originalViewSize / 2.f},originalViewSize };
			DBUG::Log(canvas->getView().getSize());
			gui.add(canvas);
		}
		
		// Info Panel // 
		auto infoPanel = tgui::Panel::create();
		auto infoPanelRenderer = infoPanel->getRenderer();
		{
			infoPanel->setHeight(25);
			infoPanel->setPosition(0, tgui::bindHeight(gui) - tgui::bindHeight(infoPanel));
			infoPanelRenderer->setBackgroundColor({ 86,84,142 });
			gui.add(infoPanel);
		}

		// Sprite Sheet Panel //
		auto mainPanel = tgui::ScrollablePanel::create();
		auto mainPanelRenderer = mainPanel->getRenderer();
		{
			mainPanel->setPosition(tgui::bindLeft(secondMenuBar), tgui::bindTop(canvas));
			mainPanel->setSize(
				tgui::bindWidth(gui) - tgui::bindPosX(mainPanel) - padding,
				tgui::bindHeight(gui) - tgui::bindPosY(mainPanel) - tgui::bindHeight(infoPanel) - padding);

			mainPanelRenderer->setBackgroundColor({ 56,54,52 });
			mainPanelRenderer->setBorders(1);
			mainPanelRenderer->setBorderColor({ 106,104,102 });
			mainPanelRenderer->setScrollbar(theme.getRenderer("Scrollbar"));

			gui.add(mainPanel, "mainPanel");
		}

		// Second  Panel //
		auto secondPanel = tgui::ScrollablePanel::create();
		auto secondPanelRenderer = secondPanel->getRenderer();
		{
			secondPanel->setPosition(tgui::bindLeft(canvas), tgui::bindHeight(canvas) + tgui::bindHeight(menuBar) + (2 * padding));
			secondPanel->setSize(tgui::bindWidth(canvas), tgui::bindHeight(gui) - tgui::bindPosY(secondPanel) - tgui::bindHeight(infoPanel) - padding);
			secondPanelRenderer->setBackgroundColor({ 56,54,52 });
			secondPanelRenderer->setBorders(1);
			secondPanelRenderer->setBorderColor({ 106,104,102 });

			gui.add(secondPanel);
		}
	}
	gui.add(dbug);
}

void Editor::Update(sf::Event& event)
{
	/*if (event.type == sf::Event::Resized)
	{
		sf::Vector2f curCanvasSize;
		sf::Vector2f newCanvasSize;
		sf::View newView;
		curCanvasSize = canvas->getSize();
		newCanvasSize = { ((float)event.size.width * 0.7f) - 20.f,((float)event.size.height * 0.7f) - 20.f };
		DBUG::Log(newCanvasSize);
		if (newCanvasSize.x < curCanvasSize.x && newCanvasSize.y < curCanvasSize.y)
		{
			newView = { newCanvasSize / 2.f, { newCanvasSize.x,newCanvasSize.y } };
			
		}
		else if (newCanvasSize.x < curCanvasSize.x)
		{
			newView = {{ newCanvasSize.x / 2.f, curCanvasSize.y / 2.f }, { newCanvasSize.x,curCanvasSize.y }
		};
		}
		else if (newCanvasSize.y < curCanvasSize.y)
		{
			newView = { { curCanvasSize.x / 2.f, newCanvasSize.y / 2.f }, { curCanvasSize.x,newCanvasSize.y} };
		}
		else
		{
			newView = { canvas->getView().getCenter(), curCanvasSize };
		}
			canvas->setView(newView);
	}*/
	
	gui.handleEvent(event);
	UpdateCanvasView(event);
	
}

void Editor::Draw()
{
	canvas->clear({ 86,84,82 });
	gui.draw();
	DrawMainGrid();
	DrawMap();
	canvas->display();
}

void Editor::CreateNewMap()
{
	int mapSizeMaxChars = 4;
	sf::Vector2f tempMapSize = { 0.f,0.f };
	float tempTileSize = 0.f;
	float tempScaleFactor = 0.f;

	createNewMapWindow = tgui::ChildWindow::create();
	createNewMapWindow->setOrigin(.5f,.5f);
	createNewMapWindow->setPosition("50%");
	createNewMapWindow->setTitle("New Map");
	createNewMapWindow->setTitleAlignment(tgui::ChildWindow::TitleAlignment::Center);

	// Layout of positioning lables and edit boxes //
	auto layout = tgui::BoxLayout::create();
	layout->setPosition(createNewMapWindow->getPosition() + tgui::Layout2d(10, 30));
	
	// Lable map width //
	auto lable1 = tgui::Label::create();
	lable1->setText("Map width: ");
	lable1->setPosition(layout->getPosition());
	
	// Lable map height //
	auto lable2 = tgui::Label::create();
	lable2->setText("Map height: ");
	lable2->setPosition(lable1->getPosition().x, lable1->getPosition().y + lable1->getSize().y +5);
	
	// Lable tile size //
	auto lable3 = tgui::Label::create();
	lable3->setText("Tile size: ");
	lable3->setPosition(lable1->getPosition().x, lable2->getPosition().y + lable2->getSize().y + 15);

	// Lable scale factor //
	auto lable4 = tgui::Label::create();
	lable4->setText("Scale factor: ");
	lable4->setPosition(lable1->getPosition().x, lable3->getPosition().y + lable3->getSize().y + 5);

	//Edid box map width//
	auto mapWidthEdidBox = tgui::EditBox::create();
	mapWidthEdidBox->setPosition(lable1->getSize().x + 30, layout->getPosition().y);
	mapWidthEdidBox->setSize(40, tgui::bindHeight(lable1));
	mapWidthEdidBox->setMaximumCharacters(mapSizeMaxChars);
	mapWidthEdidBox->setInputValidator(tgui::EditBox::Validator::Int);

	//Edid box map height//
	auto mapHeightEdidBox = tgui::EditBox::create();
	mapHeightEdidBox->setPosition(mapWidthEdidBox->getPosition().x, lable2->getPosition().y);
	mapHeightEdidBox->setSize(40, tgui::bindHeight(lable2));
	mapHeightEdidBox->setMaximumCharacters(mapSizeMaxChars);
	mapHeightEdidBox->setInputValidator(tgui::EditBox::Validator::Int);

	//Edid box tile size//
	auto tileSizeEdidtBox = tgui::EditBox::create();
	tileSizeEdidtBox->setPosition(mapWidthEdidBox->getPosition().x, lable3->getPosition().y);
	tileSizeEdidtBox->setSize(40, tgui::bindHeight(lable3));
	tileSizeEdidtBox->setMaximumCharacters(mapSizeMaxChars);
	tileSizeEdidtBox->setInputValidator(tgui::EditBox::Validator::Int);
	
	//Edid box tile size//
	auto scaleFactorEdidtBox = tgui::EditBox::create();
	scaleFactorEdidtBox->setPosition(mapWidthEdidBox->getPosition().x, lable4->getPosition().y);
	scaleFactorEdidtBox->setSize(40, tgui::bindHeight(lable4));
	scaleFactorEdidtBox->setMaximumCharacters(mapSizeMaxChars);
	scaleFactorEdidtBox->setInputValidator(tgui::EditBox::Validator::Int);

	tempMapSize = { mapWidthEdidBox->getText().toFloat(), mapHeightEdidBox->getText().toFloat() };
	tempTileSize = tileSizeEdidtBox->getText().toFloat();
	tempScaleFactor = scaleFactorEdidtBox->getText().toFloat();

	// buttons //
	auto createButton = tgui::Button::create("create");
	createButton->setPosition(createNewMapWindow->getSize().x / 2 - (int)createButton->getFullSize().x - 5, "85%");

	createButton->onClick([=]() {
		mapSize.x = mapWidthEdidBox->getText().toFloat();
		mapSize.y = mapHeightEdidBox->getText().toFloat();
		tileSize = tileSizeEdidtBox->getText().toFloat();
		tileScaleFactor = scaleFactorEdidtBox->getText().toFloat();
		createNewMapWindow->close();
		});
	auto cancelButtong = tgui::Button::create("cancel");
	cancelButtong->setPosition("50% + 5", "85%");
	cancelButtong->onClick([&] {createNewMapWindow->close(); });
	
	// add //
	createNewMapWindow->add(lable1);
	createNewMapWindow->add(lable2);
	createNewMapWindow->add(lable3);
	createNewMapWindow->add(lable4);
	createNewMapWindow->add(mapWidthEdidBox,"eb1");
	createNewMapWindow->add(mapHeightEdidBox, "eb2");
	createNewMapWindow->add(tileSizeEdidtBox, "eb3");
	createNewMapWindow->add(scaleFactorEdidtBox, "eb4");

	createNewMapWindow->add(createButton);
	createNewMapWindow->add(cancelButtong);
	gui.add(createNewMapWindow);
}

void Editor::MakeNewFile()
{
	// File Dialog //
	/*fileDialog = tgui::FileDialog::create("Save file", "Save");
	fileDialog->setPosition(0, 0);
	fileDialog->setSize(600, 400);
	fileDialog->setFileMustExist(false);
	newMapFilePath = fileDialog->getPath();
	gui.add(fileDialog);*/
}

void Editor::OpenMap()
{
	saved = true; // if we just open a map from file its same state as saved
	startUp = false;
	int id = 0;
	sf::Sprite sprite;
	sf::Vector2i position;
	std::ifstream in;
	std::string line;

	size_t count; // reading id/posX/posY
	size_t count2;
	size_t count3;

	in.open(newMapFilePath);
	if (in.is_open())
	{
		std::getline(in, line);
		spriteSheetTextureDirectory = line;
		std::getline(in, line);
		spriteSheetTextureName = line;

		std::getline(in, line);
		mapSize.x = std::stof(line);
		std::getline(in, line);
		mapSize.y = std::stof(line);
		std::getline(in, line);
		tileSize = std::stof(line);
		std::getline(in, line);
		tileScaleFactor = std::stof(line);

		map.clear();
		resManager.LoadTexture(spriteSheetTextureName, spriteSheetTextureDirectory + spriteSheetTextureName);
		sprite.setTexture(*resManager.GetTexture(spriteSheetTextureName));
		sprite.setScale(tileScaleFactor, tileScaleFactor);

		while (std::getline(in, line))
		{
			count = line.find(',');
			id = std::stoi(line.substr(0, count));
			count2 = line.find(',', count + 1);
			position.x = std::stoi(line.substr(count + 1, count2 - 1 - count));
			count3 = line.find(',', count2 + 1);
			position.y = std::stoi(line.substr(count2 + 1, count3 - 1 - count2));

			sprite.setPosition((sf::Vector2f)(position * (int)tileSize * (int)tileScaleFactor));
			sprite.setTextureRect({
				 (id % spriteSheetSize.x) * (int)tileSize,
				 (id / spriteSheetSize.y) * (int)tileSize,
				 (int)tileSize,
				 (int)tileSize
				});		
			map.push_back({ id,sprite });
		}
		in.close();
		DBUG::Log("Map loaded", DBUG::Type::INFO);
	}
}

void Editor::SaveMap()
{
	if (!mapTextureLoaded)
	{
		auto warningMsg = tgui::MessageBox::create();
		warningMsg->setTitle("No sprite has been loaded!");
		warningMsg->setTitleAlignment(tgui::ChildWindow::TitleAlignment::Center);
		warningMsg->setText("Load sprite sheet before saving the map");
		warningMsg->setOrigin(0.5f, 0.5f);
		warningMsg->setPosition("50%");
		warningMsg->addButton("Ok");
		warningMsg->onButtonPress([=] {warningMsg->close(); OpenFileDialog("Sprite"); });
		gui.add(warningMsg);
		
	}
	else
	{
		std::sort(map.begin(), map.end(), [&](Tile a, Tile b) {
			return a.sprite.getPosition().y * tileSize * tileScaleFactor + a.sprite.getPosition().x <
				b.sprite.getPosition().y* tileSize* tileScaleFactor + b.sprite.getPosition().x;
			});

		std::ofstream of;
		of.open(newMapFilePath);
		if (of.is_open())
		{
			of << spriteSheetTextureDirectory << '/' << '\n'
				<< spriteSheetTextureName << '\n'
				<< mapSize.x << "\n"
				<< mapSize.y << "\n"
				<< tileSize << "\n"
				<< tileScaleFactor << '\n';

			for (auto t : map)
			{
				of << t.id << ','
					<< t.sprite.getPosition().x / (tileSize * tileScaleFactor) << ','
					<< t.sprite.getPosition().y / (tileSize * tileScaleFactor) << ',' << "\n";
			}
			saved = true;
			DBUG::Log("Map saved", DBUG::Type::INFO);
		}
		else
		{
			SaveFileDialog();
			saved = true;
		}
	}	
}

void Editor::ClearMap()
{
	map.clear();
	DBUG::Log("Map cleared",DBUG::Type::INFO);
}

void Editor::DrawMap()
{
	if (!map.empty())
	{
		for (auto t : map)
		{
			canvas->draw(t.sprite);
		}
	}
}

void Editor::SelectTile(const sf::Vector2i& mousePosition)
{
}

void Editor::AddTileToMap(const Tile& tile)
{
}

bool Editor::CheckLocationIsFree(const Tile& tile)
{
	return false;
}

void Editor::OverrideLocation(const Tile& tile)
{
}

void Editor::DrawMainGrid()
{
	float vLine = mapSize.y * tileSize * tileScaleFactor + 2.f;
	mainGrid.vLine.setSize({ 1.f,vLine });
	float hLine = mapSize.x * tileSize * tileScaleFactor;
	mainGrid.hLine.setSize({ hLine,1.f });
	
	mainGrid.vLine.setFillColor({ 106,104,102 });
	mainGrid.hLine.setFillColor({ 106,104,102 });

	for (size_t y = 0; y < mapSize.y + 1; y++)
	{
		mainGrid.hLine.setPosition(0.f, (float)y * tileSize * tileScaleFactor);
		canvas->draw(mainGrid.hLine);
	}
	for (size_t x = 0; x < mapSize.x + 1; x++)
	{
		mainGrid.vLine.setPosition((float)x * tileSize * tileScaleFactor, 0.f);
		canvas->draw(mainGrid.vLine);
	}
}

void Editor::SaveMsgBox()
{
	auto msgBox = tgui::MessageBox::create();
	msgBox->setPosition("50%");
	msgBox->setTitle("Warning!");
	msgBox->setTitleAlignment(tgui::MessageBox::TitleAlignment::Center);
	msgBox->setText("Do you want to save current map?");
	msgBox->addButton("save");
	msgBox->addButton("don't save");
	msgBox->onButtonPress(&Editor::SaveMsgBoxBtnClickedCallback, this);
	msgBox->onButtonPress(&Editor::CreateNewMap, this);
	msgBox->onButtonPress([&] {gui.remove(gui.get("savemsg")); });
	gui.add(msgBox, "savemsg");
}

void Editor::MenuBarItemClickedCallback(const tgui::String& item)
{
	// Map //
	if (item == "New")
	{
		if (!saved)
		{
			SaveMsgBox(); // calls CreateNewMap() if button pressed
		}
		if (saved)
		{
			CreateNewMap();
		}
	}
	else if (item == "Open")
	{
		OpenFileDialog("Map");
	}
	else if (item == "Save")
	{
		SaveMap();
	}
	else if (item == "Clear")
	{
		ClearMap();
	}
	// Sprite //
	else if (item == "Open sprite sheet")
	{
		OpenFileDialog("Sprite");
	}
}

void Editor::SaveMsgBoxBtnClickedCallback(const tgui::String& btn)
{
	btn == "save" ? SaveMap() : DBUG::Log("(msgBox) map not saved!",DBUG::Type::INFO);
}

void Editor::OpenFileDialog(std::string parent)
{
	if (parent == "Map")
	{
		auto openFileDialog = tgui::FileDialog::create("Open map", "Open");
		openFileDialog->setOrigin(0.5f, 0.5f);
		openFileDialog->setPosition("50%");

		openFileDialog->onFileSelect([=] {
			newMapFilePath = std::string(openFileDialog->getSelectedPaths()[0].asString()); 
			OpenMap();
			openFileDialog->close();
			});
		gui.add(openFileDialog);
	}
	else if (parent == "Sprite")
	{
		auto openFileDialog = tgui::FileDialog::create("Open sprite", "Open");
		openFileDialog->setOrigin(0.5f, 0.5f);
		openFileDialog->setPosition("50%");

		openFileDialog->onFileSelect([=] {
			spriteSheetTextureDirectory = std::string(openFileDialog->getSelectedPaths()[0].getParentPath().asString());
			spriteSheetTextureName = std::string(openFileDialog->getSelectedPaths()[0].getFilename());
			resManager.LoadTexture(spriteSheetTextureName, spriteSheetTextureDirectory + '/' + spriteSheetTextureName) == true ? 
				mapTextureLoaded = true : mapTextureLoaded = false;
			GuiLoadSpriteSheet();
			openFileDialog->close();
			});
		gui.add(openFileDialog);
	}
	else
	{
		DBUG::Log("openFileDialog", DBUG::Type::ERROR);
	}
	
}

void Editor::SaveFileDialog()
{
	auto saveFileDialog = tgui::FileDialog::create("Save file", "Save");
	saveFileDialog->setOrigin(0.5f, 0.5f);
	saveFileDialog->setPosition("50%");

	saveFileDialog->setFileMustExist(false);
	saveFileDialog->onFileSelect([=] {
		newMapFilePath = std::string(saveFileDialog->getSelectedPaths()[0].asString());
		SaveMap();
		saveFileDialog->close();
		});
	gui.add(saveFileDialog);
}

void Editor::GuiLoadSpriteSheet()
{	
	tgui::ScrollablePanel::Ptr mainPanel = gui.get<tgui::ScrollablePanel>("mainPanel");

	auto spriteSheetLable = tgui::Label::create();
	spriteSheetLable->setPosition(tgui::bindLeft(mainPanel) + (tgui::bindWidth(mainPanel) / 2.f), tgui::bindTop(mainPanel));
	spriteSheetLable->setText(spriteSheetTextureName);
	spriteSheetLable->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	auto splRenderer = spriteSheetLable->getRenderer();
	splRenderer->setTextColor(tgui::Color::White);
	splRenderer->setTextSize(12);

	auto spriteSheetImage = tgui::Picture::create(*resManager.GetTexture(spriteSheetTextureName));
	spriteSheetImage->setPosition(10, 50);
	spriteSheetImage->setSize(spriteSheetImage->getSize().x * 2 * tileScaleFactor, spriteSheetImage->getSize().y * 2*tileScaleFactor);
	gui.add(spriteSheetLable,"spl1");
	mainPanel->add(spriteSheetImage, "spi1");


	
}

void Editor::UpdateCanvasView(sf::Event& event)
{
	canvas->setView(currentView);
	// ZOOM -----------------------------------------------------------------------------------------------------------//
	auto curViewSize = canvas->getView().getSize();
	auto curCanvasSize = canvas->getSize();
	if (curViewSize.y > curCanvasSize.y)
	{
		float ratio = curCanvasSize.y / curViewSize.y;
		curViewSize.y *= ratio;
		curViewSize.x = curCanvasSize.x;
	}
	auto curViewCenter = canvas->getView().getCenter();
	float zoomValue ; // diff of view size befor and after zooming
	sf::Vector2f vel;
	sf::Vector2f viewFactor;
	sf::Vector2f sizeFactor;
	sf::View newView = canvas->getView();

	if (event.type == sf::Event::MouseWheelMoved)
	{
		int delta = event.mouseWheel.delta;
			
		
		auto oldVSize = newView.getSize();
		newView.zoom(1.f + (delta * 0.1));
		auto newVSize = newView.getSize();

		zoomValue = (newVSize.x * newVSize.y) / (oldVSize.x * oldVSize.y);
		std::cout << oldVSize.x << " " << oldVSize.y << std::endl
			<< newVSize.x << " " << newVSize.y << std::endl << zoomValue << std::endl;
		zoomTick =  zoomTick + delta * zoomTick * 0.1f;
		// update grid width to prevent artifact // perfect!
		mainGrid.hLine.setScale({ 1.f, newView.getSize().x / canvas->getSize().x });
		mainGrid.vLine.setScale( newView.getSize().x / canvas->getSize().x, 1.f);	
	}

	// DRAG -----------------------------------------------------------------------------------------------------------//
	tgui::Vector2f curMousePosition = (tgui::Vector2f)(tgui::Vector2i)sf::Mouse::getPosition(*window);

	viewFactor = { newView.getSize().x / canvas->getView().getSize().x,
	newView.getSize().y / canvas->getView().getSize().y };
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
		{	tgui::ScrollablePanel::Ptr mainPanel = gui.get<tgui::ScrollablePanel>("mainPanel");
			tgui::Picture::Ptr spriteSheetImage = gui.get<tgui::Picture>("spi1");
			if (mapTextureLoaded && mainPanel->isMouseOnWidget(curMousePosition)) // TODO: make a mouse released var so that btn must be repressed when switching wnd
			{
				tgui::Vector2f oldMousePosition = dragOldMousePosition;
				auto vel = curMousePosition - oldMousePosition;

				auto imgOldPositon = spriteSheetImage->getPosition();
				spriteSheetImage->setPosition(imgOldPositon + vel);
			}
		}
		if (canvas->isMouseOnWidget(curMousePosition))
		{
			vel = dragOldMousePosition - curMousePosition;
			newView.move(vel.x * viewFactor.x * zoomTick, vel.y * viewFactor.y * zoomTick);
		}
	}
	canvas->setView(newView);
	canvas->getViewport().setSize((sf::Vector2i)(sf::Vector2f)canvas->getSize());
	currentView = newView;
	dragOldMousePosition = curMousePosition;
	{
	std::stringstream out;
	out << "viewX: " << canvas->getView().getSize().x << " | " << "viewY: " << canvas->getView().getSize().y << std::endl
		<< "canvasX: " << canvas->getSize().x << " | " << "canvasY: " << canvas->getSize().y << std::endl
		<< "factorX: " << viewFactor.x << " | " << "factorY: " << viewFactor.y << std::endl
		<< "ViewportX: " << canvas->getViewport().getSize().x << " | " << "ViewportY: " << canvas->getViewport().getSize().y << std::endl << std::endl
		<< "vCenterX: " << newView.getCenter().x << " | " << "vCenterY: " << newView.getCenter().y << std::endl
		<< zoomTick << std::endl;

		if (!dbug->getWidgets().empty())
		{
			dbug->removeAllWidgets();
		}
		auto msg = tgui::MessageBox::create();
		msg->setText(out.str());
		dbug->add(msg);
	}
}

