#include "Editor.h"

int main()
{
	Editor editor;

	

	sf::RenderWindow window{ {1280, 720}, "TGUI example - SFML_GRAPHICS backend"};
	editor.Init(window);
	while (window.isOpen())
	{
		// Handle events //
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// Update //
			editor.Update(event);

		}
		// Draw //
		window.clear({ 66,64,62 });
		editor.Draw();
		window.display();
	}
	
}