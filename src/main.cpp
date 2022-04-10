#include "Editor.h"

int main()
{
	int fps = 0;
	float timeCounter = 0.f;
	sf::Clock clock;

	

	sf::RenderWindow window{ {1280, 720}, "TME"};
	Editor editor(window);
	while (window.isOpen())
	{
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();
		timeCounter += dt;
		++fps;
		if (timeCounter >= 1.f)
		{
			timeCounter -= timeCounter;
			//std::cout << fps << std::endl;
			fps = 0;
		}

		// Handle events //
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			editor.HandleEvents(event);
		}
		// Update //
		editor.Update();
		
		// Draw //
		window.clear({ 32,32,34 });
		editor.Draw();
		window.display();
	}
	
}