#include "Structs.h"

bool Exit()
{
	sf::RenderWindow window(sf::VideoMode(400, 200), "EXIT");
	int position = 1;
	bool res = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
			{
				if (position == 1)
					position = 2;
				else position--;
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
			{
				if (position == 2)
					position = 1;
				else position++;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
				switch (position)
				{
				case 1:
					window.close();
					res = true;
					break;
				case 2:
					window.close();
					res = false;
					break;
				}
		}
		window.clear();
		sf::Text text;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text.setCharacterSize(20);
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setStyle(sf::Text::Bold);
		text.setString("Do you want to left game?");
		text.setPosition(70, 30);

		sf::Text yes = text, no = text;
		switch (position)
		{
		case 1:
			yes.setFillColor(sf::Color::Yellow);
			yes.setStyle(sf::Text::Underlined);
			break;
		case 2:
			no.setFillColor(sf::Color::Yellow);
			no.setStyle(sf::Text::Underlined);
			break;
		}

		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(400, 200));
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(0, 0);
		window.draw(rect);
		window.draw(text);

		yes.setPosition(30, 160);
		no.setPosition(330, 160);
		yes.setString("Yes");
		no.setString("No");
		window.draw(yes);
		window.draw(no);
		window.display();
	}
	return res;
}