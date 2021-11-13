#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

// Вспомогательная функция, вычисляет расстояние между двумя точками
float distance(sf::Vector2f start, sf::Vector2f finish)
{
    return sqrtf((start.x - finish.x)*(start.x - finish.x) + (start.y - finish.y)*(start.y - finish.y));
}


int main()
{
    const int width = 800;
    const int height = 600;
    srand(time(0));
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Hello world!");
    window.setFramerateLimit(60);

    // Это для надписи вверху слева:
    sf::Font consolas_font;
    if (!consolas_font.loadFromFile("consolas.ttf"))
    {
        cout << "Can't load button font consolas.txt" << endl;
    }
    sf::Text title;
    title.setFont(consolas_font);
    title.setString("Movable rectangles!");
    title.setCharacterSize(28);

    vector<sf::RectangleShape> array_of_shapes;

    for(int i = 0; i < 20; i++)
    {
        sf::RectangleShape rect({200, 150});
        rect.setPosition({rand() % int(width - rect.getSize().x), rand() % int(height - rect.getSize().y)});
        rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        array_of_shapes.push_back(rect);
    }

    sf::RectangleShape * selected = nullptr;

    bool is_pressed = false;
    bool is_pressed_inside_rectangle = false;
    float old_x = 0;
    float old_y = 0;
    float new_x = 0;
    float new_y = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mouse_position = {(float)event.mouseMove.x, (float)event.mouseMove.y};
                // Вам нужно дописать поведение прямоугольника ниже

                // Новые координыты мышки
                new_x = (float)event.mouseMove.x;
                new_y = (float)event.mouseMove.y;

                if(selected)
                {
                    float delta_x = old_x - new_x;
                    float delta_y = old_y - new_y;

                    selected->setPosition({selected->getPosition().x - delta_x, selected->getPosition().y - delta_y});

                    old_x = new_x;
                    old_y = new_y;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse_position = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                // Вам нужно дописать поведение прямоугольника ниже

                auto mb = event.mouseButton;

                if(selected == nullptr)
                {
                    for(int i = 20; i > 0; i--)
                    {
                        if(array_of_shapes[i].getGlobalBounds().contains(mb.x, mb.y))
                        {
                            old_x = mb.x;
                            old_y = mb.y;

                            selected = &array_of_shapes[i];
                            break;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2f mouse_position = {(float)event.mouseButton.x, (float)event.mouseButton.y};

                if(selected)
                {
                    selected = nullptr;
                }

            }

        }


        window.clear(sf::Color::Black);

        for(int i = 0; i < 20; i++)
        {
            window.draw(array_of_shapes[i]);
        }

        window.draw(title);
        window.display();
    }

    return 0;
}