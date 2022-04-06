#pragma once
#include "SFML/Graphics.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
class TMGui
{
public:
	void Init(sf::RenderWindow& windowRef);
	void HandleEvents(sf::Event& event);
	void Update();
	void Draw();
public:
	void Add(const tgui::Widget::Ptr& widgetPtr, const tgui::String& widgetName = "");
private:
	tgui::Gui gui;
	sf::RenderWindow* window;
};

