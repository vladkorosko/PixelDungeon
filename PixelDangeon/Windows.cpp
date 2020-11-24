#include "Gameboard.h"

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

Player Generating(sf::RenderWindow& window, Player p = Player(100,20,30,30))
{
    time_t start = clock();
    while (window.isOpen())
    {
        time_t finish = clock();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                if (Exit())
                {
                    Menu(window);
                }
        }
        time_t wt = finish - start;
        if (wt >= 10000)
        {
            return p;
        }
        window.clear();
        string text = "Loading";
        switch ((wt / 500) % 3)
        {
        case 0:
            text = text + ".";
            break;
        case 1:
            text = text + "..";
            break;
        case 2:
            text = text + "...";
            break;
        default:
            break;
        }
        sf::Text text1;
        sf::Font font;
        font.loadFromFile("bold.ttf");
        text1.setCharacterSize(100);
        text1.setFont(font);
        text1.setFillColor(sf::Color::Blue);
        text1.setStyle(sf::Text::Bold);
        text1.setString(text);
        text1.setPosition(window.getSize().x / 2 - text.size() * 25, window.getSize().y / 2 - 50);
        window.draw(text1);
        window.display();
    }
}

void Game(sf::RenderWindow& window, Player &player)
{
    GameBoard Map(window.getSize().y/10, 1);
    Map.AutoGenerateWalls(1000, player);
    Map.AutoGenerateTraps(100, player);
    Map.AutoGenerateBonusHealth(50, player);
    Map.AutoGenerateBonusBlocks(10, player);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                if (Exit())
                {
                    Menu(window);
                }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
            {
                Move(Map, player, 1, CheckCurrentPositionPlayer);
                for (int i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    Move(Map, new_e, AI(Map, player, new_e), CheckCurrentPositionEnemy);
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
            {
                Move(Map, player, 0, CheckCurrentPositionPlayer);
                for (int i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    Move(Map, new_e, AI(Map, player, new_e), CheckCurrentPositionEnemy);
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
            {
                Move(Map, player, 2, CheckCurrentPositionPlayer);
                for (int i =0 ;i < Map.GetEnemies().size();i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    Move(Map, new_e, AI(Map, player, new_e), CheckCurrentPositionEnemy);
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
            {
                Move(Map, player, 3, CheckCurrentPositionPlayer);
                for (int i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    Move(Map, new_e, AI(Map, player, new_e), CheckCurrentPositionEnemy);
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Right))
            {
                Magic(event.mouseButton.x, event.mouseButton.y, player, Map);
                for (int i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    Move(Map, new_e, AI(Map, player, new_e), CheckCurrentPositionEnemy);
                    Map.SetEnemyIndex(new_e, i);
                }
            }
        }

        if (player.GetXPosition() / 10 == Map.GetXPortal() + 1 && player.GetYPosition() / 10 == Map.GetYPortal() + 1)
        {
            Generating(window, player);
            Game(window, player);
        }

        if (player.GetHealth() == 0)
        {
            Menu(window);
        }

        window.clear();
        Map.DrawVisionUpdated(window, player);
        player.DrawBody(window);
        player.DrawCharacteristics(window);

        window.display();
    }
}

void Menu(sf::RenderWindow& window)
{
    int position = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                if (Exit())
                {
                    window.close();
                }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
            {
                if (position == 4)
                    position = 1;
                else position++;
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
            {
                if (position == 1)
                    position = 4;
                else position--;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                Player p(100, 20, 30, 30);
                switch (position)
                {
                case 1:
                    p = Generating(window);
                    Game(window, p);
                    break;
                case 2:
                    //prev_game(4, window);
                    break;
                case 3:
                    //show_scores(window);
                    break;
                case 4:
                    if (Exit())
                        window.close();
                    break;
                }
            }
        }

        window.clear();

        sf::RectangleShape option;
        option.setFillColor(sf::Color::White);
        option.setSize(sf::Vector2f(600, 100));
        option.setPosition(200, 100);
        sf::Text text1;
        sf::Font font;
        font.loadFromFile("bold.ttf");
        text1.setCharacterSize(50);
        text1.setFont(font);
        text1.setFillColor(sf::Color::Blue);
        text1.setStyle(sf::Text::Bold);
        text1.setString("New Game");
        text1.setPosition(400, 110);
        sf::Text text2 = text1, text3 = text1, text4 = text1;
        switch (position)
        {
        case 1:
            text1.setFillColor(sf::Color::Yellow);
            text1.setStyle(sf::Text::Underlined);
            break;
        case 2:
            text2.setFillColor(sf::Color::Yellow);
            text2.setStyle(sf::Text::Underlined);
            break;
        case 3:
            text3.setFillColor(sf::Color::Yellow);
            text3.setStyle(sf::Text::Underlined);
            break;
        case 4:
            text4.setFillColor(sf::Color::Yellow);
            text4.setStyle(sf::Text::Underlined);
            break;
        }

        window.draw(option);
        window.draw(text1);
        
        option.setPosition(200, 250);
        text2.setString("Continue");
        text2.setPosition(410, 260);
        window.draw(option);
        window.draw(text2);

        option.setPosition(200, 400);
        text3.setString("Records");
        text3.setPosition(420, 410);
        window.draw(option);
        window.draw(text3);

        option.setPosition(200, 550);
        text4.setString("Exit");
        text4.setPosition(460, 560);
        window.draw(option);
        window.draw(text4);

        window.display();
    }
}