#include "Editor.h"
#include <sstream>

Editor::Editor(sf::RenderWindow& windowRef)
	:
	window(&windowRef),
	mainGrid(64,{10,10}, camera)
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
}

void Editor::HandleEvents(sf::Event& event)
{
	//gui.HandleEvents(event);
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

	mainGrid.Upadate();
}

void Editor::Draw()
{
	canvas->clear();
	mainGrid.Draw(*canvas);
	canvasManager.Draw();
	canvas->display();
}
