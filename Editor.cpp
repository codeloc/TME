#include "Editor.h"
#include <sstream>

Editor::Editor(sf::RenderWindow& windowRef)
	:
	window(&windowRef),
	mainGrid(64,{10,10}, camera)
{
	currWinSize = (sf::Vector2i)window->getSize();
	gui.Init(windowRef);
	canvas = tgui::CanvasSFML::create(); // maybe just a renderTarget?
	canvas->setSize("70%");
	canvas->setPosition(10, 35);

	gui.Add(canvas);

	currentView.setSize(canvas->getSize()) ;
	currentView.setCenter(currentView.getSize() / 2.f);
	camera.Init(windowRef, currentView);

	dbug = tgui::MessageBox::create();
	gui.Add(dbug);
}

void Editor::HandleEvents(sf::Event& event)
{
	//gui.HandleEvents(event);
	switch (event.type)
	{
	case sf::Event::Resized:
	{
		sf::Vector2i newSize = { (int)event.size.width , (int)event.size.height };
		ratio = sf::Vector2f((float)newSize.x / 1280.f, (float)newSize.y / 720.f);

		sf::Vector2f r = sf::Vector2f((float)newSize.x / currWinSize.x, (float)newSize.y / currWinSize.y);
		canvas->setPosition(canvas->getPosition().x / r.x, canvas->getPosition().y / r.y);
		currWinSize = newSize;
	}
		//canvas->setSize((float)event.size.width * 0.7f,(float)event.size.height * 0.7f);
		{
			/*canvas->setPosition(10, 35);
			sf::Vector2f newSize = { (float)event.size.width, (float)event.size.height };

			window->setView({ newSize / 2.f,newSize });
			std::cout << window->getSize().x << " " << window->getSize().y << std::endl;*/
			break;
		}
	default:
		break;
	}
	camera.HandleEvents(event);
	mainGrid.HandleEvents(event, ratio);
	
}

void Editor::Update()
{
	currentView = camera.GetUpdatedView();
	canvas->setView(currentView);

	mainGrid.Upadate();

	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f canvasSize = { (float)currWinSize.x * 0.7f + 0.5f, (float)currWinSize.y * 0.7f + 0.5f };
	sf::IntRect canvasRect = { canvasOffset ,sf::Vector2i(canvasSize)};
	if (canvasRect.contains(mousePosition))
	{
		sf::Vector2i point = mousePosition - canvasOffset;
		int index = mainGrid.GetClickedOnCellIndex(point);
	
		dbug->setText(mainGrid.GetDebugSStream());
	}
}

void Editor::Draw()
{


	canvas->clear();
	mainGrid.Draw(*canvas);
	gui.Draw();
	canvas->display();
}
