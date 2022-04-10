#include "TMGui.h"

void TMGui::Init(sf::RenderWindow& windowRef)
{
	window = &windowRef;
	window->setFramerateLimit(60);
	gui.setWindow(*window);
	gui.setFont(tgui::Font::Font("./Assets/consola.ttf"));
	gui.getFont().setSmooth(true);
	
}

void TMGui::HandleEvents(sf::Event& event) // check for order
{
	gui.handleEvent(event);
	if (event.type == sf::Event::Resized)
	{
		float newWidth = event.size.width;
		float ratio = 1.f;
		ratio = (float) window->getSize().y / (float)window->getSize().x;
		float newHeight = newWidth * ratio;
		window->setSize(sf::Vector2u(newWidth, newHeight));
	}
}

void TMGui::Update()
{
}

void TMGui::Draw()
{
	gui.draw();
}

void TMGui::Add(const tgui::Widget::Ptr& widgetPtr, const tgui::String& widgetName)
{
	gui.add(widgetPtr, widgetName);
}
