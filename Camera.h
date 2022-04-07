#pragma once
#include "SFML/Graphics.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
enum class State
{
	PANNING,NONE
};

class Camera
{
public:
	void Init(const sf::RenderWindow& in_window, sf::View in_view);
	void HandleEvents(sf::Event& event);

	const sf::View& GetUpdatedView();
	float GetZoomLevel();
	sf::Vector2f GetOffset();
	sf::Vector2f MapScreenToWorld(sf::Vector2f screenPoint);
	sf::Vector2i MapWorldToScreen(sf::Vector2f worldPoint);
	const sf::View& GetView();
	const sf::Vector2f GetScreenCenter();
private:
	const  sf::RenderWindow* window;
	sf::View view;
	State state;
	sf::Vector2i panningAnchor;
	float zoomLevel;
	sf::Vector2f offset;
	sf::Vector2f moveOffset;
	sf::Vector2f zoomOffset;
};

