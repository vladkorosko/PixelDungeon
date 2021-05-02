#include "Menu.h"

bool HaveFile(std::string path)
{
    std::ifstream file(path);
    return file.good();
}

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
        std::string text = "Loading";
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
        text1.setPosition(static_cast<float>(window.getSize().x / 2 - text.size() * 25), static_cast<float>(window.getSize().y / 2 - 50));
        window.draw(text1);
        window.display();
    }
}

void SaveGame(const GameBoard& map, const Player& p)
{
    std::ofstream fout("Saved Game.txt");
    fout << p.GetHealth() << std::endl;
    fout << p.GetAmmo() << std::endl;
    fout << p.GetLimitAmmo() << std::endl;
    fout << p.GetXPosition() << std::endl;
    fout << p.GetYPosition() << std::endl;
    fout << p.GetScore() << std::endl;
    fout << map.GetXPortal() << std::endl;
    fout << map.GetYPortal() << std::endl;
    fout << map.GetMap().size() << std::endl;
    for (size_t i = 0; i < map.GetMap().size(); i++)
    {
        for (size_t j = 0; j < map.GetMap().size(); j++)
            fout << map.GetMap()[i][j] << " ";
        fout << std::endl;
    }
    for (size_t i = 0; i < map.GetMap().size(); i++)
    {
        for (size_t j = 0; j < map.GetMap().size(); j++)
            fout << map.GetBackGround()[i][j] << " ";
        fout << std::endl;
    }
    fout << map.GetEnemies().size() << std::endl;
    for (size_t i = 0; i < map.GetEnemies().size(); i++)
    {
        fout << map.GetEnemies()[i].GetHealth() << std::endl;
        fout << map.GetEnemies()[i].GetAmmo() << std::endl;
        fout << map.GetEnemies()[i].GetLimitAmmo() << std::endl;
        fout << map.GetEnemies()[i].GetXPosition() << std::endl;
        fout << map.GetEnemies()[i].GetYPosition() << std::endl;
    }
}

void EndGame(sf::RenderWindow& window, int score)
{
    std::vector<int> scores;
    if (HaveFile("score.txt"))
    {
        std::ifstream file("score.txt");
        int number;
        file >> number;
        while (number)
        {
            int points;
            file >> points;
            scores.push_back(points);
            number--;
        }
        file.close();
    }

    scores.push_back(score);
    sort(scores.begin(),scores.end());

    if (scores.size() > 10)
    {
        scores.erase(scores.begin() + 10);
    }

    std::ofstream fout("score.txt");
    fout << scores.size() << std::endl;
    for (size_t i = 0; i < scores.size(); i++)
        fout << scores[i] << std::endl;

    fout.close();

    bool cont = true;
    while (cont)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                cont = false;
        }

        window.clear();

        sf::Text text1;
        sf::Font font;
        font.loadFromFile("bold.ttf");
        text1.setCharacterSize(100);
        text1.setFont(font);
        text1.setFillColor(sf::Color::Red);
        text1.setStyle(sf::Text::Bold);

        std::string text = "Game over";
        text1.setString(text);
        text1.setPosition(static_cast<float>(500 - 55 * text.size()) / 2, 100);
        window.draw(text1);

        text = "Score: " + std::to_string(score);
        text1.setString(text);
        text1.setFillColor(sf::Color::Blue);
        text1.setPosition(static_cast<float>(500 - 50 * text.size() / 2), 300);
        window.draw(text1);

        text = "Press Esc to go to the Menu.";
        text1.setString(text);
        text1.setCharacterSize(60);
        text1.setFillColor(sf::Color::Green);
        text1.setPosition(70, 500);
        window.draw(text1);

        window.display();
    }

    Menu(window);
}

void ShowScores(sf::RenderWindow& window)
{
    std::vector<int> scores;
    if (HaveFile("score.txt"))
    {
        std::ifstream file("score.txt");
        int number;
        file >> number;
        while (number)
        {
            int points;
            file >> points;
            scores.push_back(points);
            number--;
        }
        file.close();
    }

    bool cont = true;
    while (cont && scores.size())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                cont = false;
        }

        window.clear();

        sf::Text text1;
        sf::Font font;
        font.loadFromFile("bold.ttf");
        text1.setCharacterSize(100);
        text1.setFont(font);
        text1.setFillColor(sf::Color::Green);
        text1.setStyle(sf::Text::Bold);

        std::string text = "You records:";
        text1.setString(text);
        text1.setPosition(static_cast<float>(500 - 50 * text.size() / 2), 0);
        window.draw(text1);

        text1.setCharacterSize(50);
        for (size_t i = 0; i < scores.size(); i++)
        {
            text = "Score: " + std::to_string(scores[i]);
            text1.setString(text);
            text1.setFillColor(sf::Color::Blue);
            text1.setPosition(static_cast<float>(400 * (i % 2 + 1) - 50 * text.size() / 2), static_cast<float>(100 * (i / 2 + 1)));
            window.draw(text1);
        }

        text = "Press Esc to go to the Menu.";
        text1.setString(text);
        text1.setCharacterSize(60);
        text1.setFillColor(sf::Color::Green);
        text1.setPosition(70, 600);
        window.draw(text1);

        window.display();
    }

    Menu(window);
}

void LoadGame(GameBoard& map, Player& p)
{
    bool is_file = HaveFile("Saved Game.txt");
    if (is_file)
    {
        std::ifstream fin("Saved Game.txt");
        int var;
        fin >> var;
        p.SetHealth(var);
        fin >> var;
        p.SetAmmo(var);
        fin >> var;
        p.SetLimitAmmo(var);
        fin >> var;
        p.SetXPosition(var);
        fin >> var;
        p.SetYPosition(var);
        fin >> var;
        p.SetScore(var);
        fin >> var;
        map.SetXPortal(var);
        fin >> var;
        map.SetYPortal(var);
        int size;
        fin >> size;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                fin >> var;
                Place pl;
                switch (var)
                {
                case 0:
                    pl = WALL;
                    break;
                case 1:
                    pl = SPACE;
                    break;
                case 2:
                    pl = TRAP;
                    break;
                case 3:
                    pl = INCREASEHP;
                    break;
                case 4:
                    pl = IMPROVEBAG;
                    break;
                default:
                    pl = PORTAL;
                    break;
                }
                map.SetMapElement(i, j, pl);
            }
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                fin >> var;
                Place pl;
                switch (var)
                {
                case 0:
                    pl = WALL;
                    break;
                case 1:
                    pl = SPACE;
                    break;
                case 2:
                    pl = TRAP;
                    break;
                case 3:
                    pl = INCREASEHP;
                    break;
                case 4:
                    pl = IMPROVEBAG;
                    break;
                default:
                    pl = PORTAL;
                    break;
                }
                map.SetBackGroundElement(i, j, pl);
            }
        fin >> size;
        for (int i = 0; i < size; i++)
        {
            Enemy e(0, 0, 0, 0);
            int hp,am,lim,x,y;
            fin >> hp >> am >> lim >> x >> y;
            e.SetHealth(hp);
            e.SetAmmo(am);
            e.SetLimitAmmo(lim);
            e.SetXPosition(x);
            e.SetYPosition(y);
        }
        fin.close();
    }
}

void Game(sf::RenderWindow& window, Player& player, GameBoard& Map)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                if (Exit())
                {
                    SaveGame(Map, player);
                    Menu(window);
                }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
            {
                MovePlayer(Map, player, 1);
                for (size_t i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    MoveEnemy(Map, new_e, player, AI(Map, player, new_e));
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
            {
                MovePlayer(Map, player, 0);
                for (size_t i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    MoveEnemy(Map, new_e, player, AI(Map, player, new_e));
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
            {
                MovePlayer(Map, player, 2);
                for (size_t i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    MoveEnemy(Map, new_e, player, AI(Map, player, new_e));
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
            {
                MovePlayer(Map, player, 3);
                for (size_t i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    MoveEnemy(Map, new_e, player, AI(Map, player, new_e));
                    Map.SetEnemyIndex(new_e, i);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Right))
            {
                Magic(event.mouseButton.x, event.mouseButton.y, player, Map);
                for (size_t i = 0; i < Map.GetEnemies().size(); i++)
                {
                    Enemy new_e = Map.GetEnemies()[i];
                    MoveEnemy(Map, new_e, player, AI(Map, player, new_e));
                    Map.SetEnemyIndex(new_e, i);
                }
            }
        }

        int sc = player.GetScore();
        int numflour = sc / (2 * window.getSize().y);
        int x = abs(player.GetXPosition() - (Map.GetXPortal() + 1) * 10);
        int y = abs(player.GetYPosition() - (Map.GetYPortal() + 1) * 10);
        player.SetScore(numflour * (2 * window.getSize().y) + (2 * window.getSize().y) - x - y);

        if (player.GetXPosition() / 10 == Map.GetXPortal() + 1 && player.GetYPosition() / 10 == Map.GetYPortal() + 1)
        {
            Generating(window, player);
            NewGame(window, player);
        }

        if (player.GetHealth() < 0)
        {
            break;
        }

        window.clear();
        Map.DrawVisionUpdated(window, player);
        player.DrawBody(window);
        player.DrawCharacteristics(window);

        window.display();
    }

    EndGame(window, player.GetScore());
}

void NewGame(sf::RenderWindow& window, Player& player)
{
    GameBoard Map(window.getSize().y / 10, 10);
    Map.AutoGenerateWalls(1000, player);
    Map.AutoGenerateTraps(100, player);
    Map.AutoGenerateBonusHealth(50, player);
    Map.AutoGenerateBonusBlocks(10, player);
    Game(window, player, Map);
}

void ContinueGame(sf::RenderWindow& window, Player& player)
{
    GameBoard Map(window.getSize().y / 10, 10);
    Map.AutoGenerateWalls(1000, player);
    Map.AutoGenerateTraps(100, player);
    Map.AutoGenerateBonusHealth(50, player);
    Map.AutoGenerateBonusBlocks(10, player);
    LoadGame(Map, player);
    Game(window, player, Map);
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
                    NewGame(window, p);
                    break;
                case 2:
                    p = Generating(window);
                    ContinueGame(window, p);
                    break;
                case 3:
                    ShowScores(window);
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