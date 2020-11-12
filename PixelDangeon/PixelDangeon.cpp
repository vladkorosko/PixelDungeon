#include"Structs.h"

int main()
{
    srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "PixelDangeon");
    GameBoard Map(100);
    Player player(100, 20, 30, 30);
    Map.AutoGenerateWalls(1000, player);
    Map.AutoGenerateTraps(100, player);
    Map.AutoGenerateBonusHealth(50,player);
    Map.AutoGenerateBonusBlocks(10,player);
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
                Move(Map, player, 1);
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
            {
                Move(Map, player, 0);
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
            {
                Move(Map, player, 2);
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
            {
                Move(Map, player, 3);
            }
            if (event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Right))
            {
                Magic(event.mouseButton.x, event.mouseButton.y, player, Map);
            }
        }

        window.clear();
        Map.DrawVision(window,player,Wall,Free,Trap);
        player.Draw(window);

        window.display();
    }
}