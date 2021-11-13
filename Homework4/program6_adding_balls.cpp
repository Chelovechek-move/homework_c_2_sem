#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


struct Ball
{
    float radius;
    int charge;
    float weight;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

float sqr(float a)
{
    return a * a;
}

int main()
{
    srand(time(0));
    
    const int width = 1920;
    const int height = 1080;
    const float k = 0.9;
    const double G = 0.0000000000667;
    const float min_distance = 40;

    int n_balls = 500;

    // Шаг по времени
    const float delta_t = 0.1;

    // Создаём экземпляр класса окно
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    // Задаём максимальное количество кадров в секунду
    window.setFramerateLimit(60);

    // Так как sf::CircleShape занимает много памяти, создаём всего 1 экземпляр
    sf::CircleShape circle(50.0f);
//    circle.setFillColor({200, 216, 200});

    std::vector<Ball> balls;
    balls.resize(n_balls);
    for (int i = 0; i < n_balls; i++)
    {
        balls[i].radius = 4 + rand() % 8;
        balls[i].position = {(float)(rand() % width), (float)(rand() % height)};
        balls[i].velocity = {(float)(rand() % 100 - 50), (float)(rand() % 100 - 50)};
        balls[i].charge = (rand() % 510) - 255;
        balls[i].weight = 1000000000000 * sqr(balls[i].radius);
    }

    for (int i = 0; i < n_balls; i++)
    {
        if (balls[i].position.x - balls[i].radius <= 0)
            balls[i].position.x += 2 * balls[i].radius;
        if (balls[i].position.x + balls[i].radius >= width)
            balls[i].velocity.x -= 2 * balls[i].radius;
        if (balls[i].position.y - balls[i].radius <= 0)
            balls[i].velocity.y += 2 * balls[i].radius;
        if (balls[i].position.y + balls[i].radius >= height)
            balls[i].velocity.y -= 2 * balls[i].radius;
    }

    bool factor = false;
    int x = 1;

    while (window.isOpen())
    {
        window.setKeyRepeatEnabled(false);

        sf::Event event;
        while (window.pollEvent(event))
        {
            // В данном примере проверяем окно на закрытие
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                factor = true;
            }
            else
            {
                factor = false;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if(factor == true)
                {
                    x = -1;
                }
                else
                {
                    x = 1;
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    n_balls += 1;

                    balls[n_balls - 1].radius = 20;
                    balls[n_balls - 1].position = {event.mouseButton.x, event.mouseButton.y};
                    balls[n_balls - 1].velocity = {(float)(rand() % 100 - 50), (float)(rand() % 100 - 50)};
                    balls[n_balls - 1].charge = x * 255;
                    balls[n_balls - 1].weight = 1000000000000 * sqr(balls[n_balls - 1].radius);
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    n_balls += 1;

                    balls[n_balls - 1].radius = 5;
                    balls[n_balls - 1].position = {event.mouseButton.x, event.mouseButton.y};
                    balls[n_balls - 1].velocity = {(float)(rand() % 100 - 50), (float)(rand() % 100 - 50)};
                    balls[n_balls - 1].charge = x * 128;
                    balls[n_balls - 1].weight = 1000000000000 * sqr(balls[n_balls - 1].radius);
                }
            }
        }

        // очистить скрытый холст черным цветом
        window.clear(sf::Color::Black);

        for (int i = 0; i < n_balls; i++)
        {
            for(int j = 0; j < n_balls; j++)
            {
                if(j != i)
                {
                    float R = sqrt(sqr(balls[i].position.x - balls[j].position.x) + sqr(balls[i].position.y - balls[j].position.y));

                    if(R >= min_distance)
                    {
                        float delta_x = balls[j].position.x - balls[i].position.x;
                        float delta_y = balls[j].position.y - balls[i].position.y;
                        float cos_alfa = delta_x / R;
                        float cos_beta = delta_y / R;

                        float delta_v_x = (-1) * (k * balls[i].charge * balls[j].charge * cos_alfa * delta_t) / sqr(R);
                        float delta_v_y = (-1) * (k * balls[i].charge * balls[j].charge * cos_beta * delta_t) / sqr(R);

                        delta_v_x += (G * balls[i].weight * cos_alfa * delta_t) / sqr(R);
                        delta_v_y += (G * balls[i].weight * cos_beta * delta_t) / sqr(R);

                        balls[i].velocity.x += delta_v_x;
                        balls[i].velocity.y += delta_v_y;
                    }
                }
            }

            balls[i].position += balls[i].velocity * delta_t;

            
            if (balls[i].position.x - balls[i].radius < 0)
                balls[i].velocity.x *= -1;
            if (balls[i].position.x + balls[i].radius > width)
                balls[i].velocity.x *= -1;
            if (balls[i].position.y - balls[i].radius < 0)
                balls[i].velocity.y *= -1;
            if (balls[i].position.y + balls[i].radius > height)
                balls[i].velocity.y *= -1;
            

            // Используем 1 sf::CircleShape, чтобы нарисовать все шары
            circle.setRadius(balls[i].radius);
            // setOrigin - задаёт центр объекта
            // По умолчанию центр - в левом верхнем угле объекта
            // Строка ниже устанавливает центр в центре шарика
            // В дальнейшем функция, setPosition устанавливает положение шарика так, 
            // чтобы его центр был в точке balls[i].position
            circle.setOrigin(balls[i].radius, balls[i].radius);
            circle.setPosition(balls[i].position);

            if(balls[i].charge >= 0)
            {
                circle.setFillColor({255 - balls[i].charge, 0, balls[i].charge});
            }
            else
            {
                circle.setFillColor({abs(balls[i].charge), 0, 255 - abs(balls[i].charge)});
            }
            
            window.draw(circle);
        }

        // отображаем содержимое скрытого холста на экран
        window.display();
    }

    return 0;
}