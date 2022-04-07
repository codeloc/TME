#include "Camera.h"

void Camera::Init(const sf::RenderWindow& in_window, sf::View in_view)
{
	window = &in_window;
	view = in_view;
	view.setCenter(0.f, 0.f);
	state = State::NONE;
	panningAnchor = { 0,0 };
	zoomLevel = 1.f;
	auto canvasCenter = GetScreenCenter() * 0.7f;

	zoomOffset = MapScreenToWorld(sf::Vector2f(canvasCenter.x + 0.5f, canvasCenter.y + 0.5f));
	moveOffset = { 0.f, 0.f };
}

void Camera::HandleEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		// pan the camerea //
		if (state == State::PANNING)
		{
			sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*window) - panningAnchor);
			moveOffset += (-1.f * pos * zoomLevel);
			view.move(-1.f * pos * zoomLevel);
			panningAnchor = sf::Mouse::getPosition(*window);
		}
		break;
	case sf::Event::MouseButtonPressed:
		// start panning // 
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			if (state != State::PANNING)
			{
				state = State::PANNING;
				panningAnchor = sf::Mouse::getPosition(*window);
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		// stop panning //
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			state = State::NONE;
		}
		break;
	case sf::Event::MouseWheelMoved:
		// zoom the view //
		if (event.mouseWheel.delta < 0)
		{
			view.zoom(1.1f);
			zoomLevel *= 1.1f;
		}
		else
		{
			view.zoom(0.9f);
			zoomLevel *= 0.9f;
		}
		zoomOffset = MapScreenToWorld((sf::Vector2f)(GetScreenCenter() * 0.7f));
		break;
	case sf::Event::Resized:
		// resize the window //
		view.setSize(event.size.width * 0.7f, event.size.height * 0.7f);
		view.zoom(zoomLevel);
		zoomOffset = MapScreenToWorld((sf::Vector2f)(GetScreenCenter() * 0.7f));
		break;

	default: break;
	}
}

const sf::View& Camera::GetUpdatedView()
{
	return view;
}

float Camera::GetZoomLevel()
{
	return zoomLevel;
}

sf::Vector2f Camera::GetOffset()
{
	return zoomOffset - moveOffset;
}

sf::Vector2f Camera::MapScreenToWorld(sf::Vector2f screenPoint)
{
	return { screenPoint.x * zoomLevel, screenPoint.y * zoomLevel };
}

sf::Vector2i Camera::MapWorldToScreen(sf::Vector2f worldPoint)
{
	return { int(worldPoint.x / zoomLevel + 0.5f), int(worldPoint.y / zoomLevel + 0.5f) };
}

const sf::View& Camera::GetView()
{
	return view;
}

const sf::Vector2f Camera::GetScreenCenter()
{
	return (sf::Vector2f)window->getSize() / 2.f;
}
