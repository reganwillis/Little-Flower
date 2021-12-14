#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//using namespaces sf;

int main()
{
    std::cout << "Hello Game Dev" << std::endl;

    sf::RenderWindow window(sf::VideoMode(640, 480), "Little Flower", sf::Style::Titlebar | sf::Style::Close);
    //sf::Window window(sf::VideoMode(640, 480), "Little Flower", sf::Style::Default);

    sf::Event ev;
    while (window.isOpen()) {
        //event polling
        while(window.pollEvent(ev)) {
            switch(ev.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
            }
        }

        //update

        //render
        window.clear(sf::Color::Blue);
        window.display();
    }
    return 0;
}