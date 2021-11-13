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
    srand(time(0));
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello world!");
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

    // Создаём прямоугольник:
    sf::RectangleShape rect({200, 150});
    rect.setPosition({300, 300});
    rect.setFillColor(sf::Color(95, 164, 143));
    // Чтобы получить левую верхнюю координату прямоугольника:
    // rect.getPosition()        (вернёт sf::Vector2f)
    // Чтобы получить размеры прямоугольника:
    // rect.getSize()            (вернёт sf::Vector2f)
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

                //Смещение мышки
                float delta_x = old_x - new_x;
                float delta_y = old_y - new_y;

                // Проверка на нажатие мышки и на нахождение курсора внутри прямоугогольника
                if(is_pressed == true && is_pressed_inside_rectangle == true)
                {
                	rect.setPosition({rect.getPosition().x - delta_x, rect.getPosition().y - delta_y});
                }

                // Переприсвоение старых координат
                old_x = new_x;
                old_y = new_y;

            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse_position = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                // Вам нужно дописать поведение прямоугольника ниже

                // Проверка на нахождение курсора внутри прямоугольника
                if(event.mouseButton.x >= rect.getPosition().x && event.mouseButton.x <= rect.getPosition().x + rect.getSize().x &&
                	event.mouseButton.y >= rect.getPosition().y && event.mouseButton.y <= rect.getPosition().y + rect.getSize().y)
                {
                	is_pressed_inside_rectangle = true;
                }
                else
                {
                	is_pressed_inside_rectangle = false;
                }

                // Кнопка мышки нажата
                is_pressed = true;

                // Запоминаем старые координаты
                old_x = (float)event.mouseButton.x;
                old_y = (float)event.mouseButton.y;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2f mouse_position = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                // Вам нужно дописать поведение прямоугольника ниже

                // Кнопка мышки отпущена
                is_pressed = false;

            }

        }

        window.clear(sf::Color::Black);
        window.draw(rect);
        window.draw(title);
        window.display();
    }

    return 0;
}