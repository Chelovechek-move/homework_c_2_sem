#include <iostream>
#include <cmath>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

// Вспомогательные функции, вычисляет расстояние между двумя точками
float distance(sf::Vector2f start, sf::Vector2f finish)
{
    return sqrtf((start.x - finish.x)*(start.x - finish.x) + (start.y - finish.y)*(start.y - finish.y));
}

// Вспомогательные функции, рисует линию на холсте окна window
void draw_line(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White)
{
    sf::Vertex line_vertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}

class Button
{
private:
    // Статические поля класса, это поля общие для всех экземпляров класса
    // Они могут быть как константными так и не константными
    static const sf::Color default_color;
    static const sf::Color hover_color;
    static const sf::Color pressed_color;

    // Тонкий момент: мы храним ссылку на шрифт sf::Font
    // Шрифт может занимать много памяти
    // Чтобы не копировать его для каждой кнопки, мы храним ссылку
    sf::Font& font;

    sf::Text text;
    sf::RectangleShape shape;
    
    // Когда кнопка находится в нажатом состоянии, то is_pressed = true
    // (Пользователь зажал кнопку и держит)
    bool is_pressed = false;

public:

    // Конструктор: ссылку нужно обязательно инициализировать в списке инициализации, поэтому font(font)
    Button(int x, int y, int width, int height, sf::Font& font, std::string text_data) : font(font)
    {
        text.setFont(font);
        text.setString(text_data);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect text_size = text.getLocalBounds();
        text.setPosition(x + (width - text_size.width)/2, y + height/2 - text_size.height);

        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(default_color);

        is_pressed = false;
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
        window.draw(text);
    }

    bool checkCollision(int x, int y)
    {
        return (x > shape.getPosition().x && 
                x < shape.getPosition().x + shape.getSize().x &&
                y > shape.getPosition().y &&
                y < shape.getPosition().y + shape.getSize().y);
    }

    void onMouseHover(sf::Event& event)
    {
        if (is_pressed)
            return;
        if (checkCollision(event.mouseMove.x, event.mouseMove.y))
        {
            shape.setFillColor(hover_color);
        }
        else
        {
            shape.setFillColor(default_color);
        }
    }

    void onMousePressed(sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (checkCollision(event.mouseButton.x, event.mouseButton.y))
            {
                is_pressed = true;
                shape.setFillColor(pressed_color);
            }
        }
    }

    bool onMouseReleased(sf::Event& event)
    {
        bool is_activated = false;
        if (is_pressed)
        {
            if (checkCollision(event.mouseButton.x, event.mouseButton.y))
            {
                shape.setFillColor(hover_color);
                is_activated = true;
            }
            else
            {
                shape.setFillColor(default_color);
                is_activated = false;
            }
            is_pressed = false;
        }
        return is_activated;
    }
};

// Зададим константы класса:
const sf::Color Button::default_color = sf::Color(40, 110, 100);
const sf::Color Button::hover_color = sf::Color(60, 150, 120);
const sf::Color Button::pressed_color = sf::Color(100, 220, 220);

class ContextMenu
{
private:
    static const sf::Color default_color;
    static const sf::Color hover_color;
    static const sf::Color text_color;
    static const int button_size_y;
    static const int character_size;

    sf::RectangleShape shape;
    sf::RectangleShape hover_shape;
    sf::Font& font;
    sf::Text text;

    std::vector<std::string> buttons;

    bool is_opened = false;
    bool is_updated = false;
    int hover_position = -1;

public:

    ContextMenu(sf::Font& font) : font(font)
    {   
        text.setFont(font);

        text.setCharacterSize(character_size);
        text.setFillColor(sf::Color::Black);

        shape.setFillColor(default_color);
        hover_shape.setFillColor(hover_color);

        is_opened = false;
        is_updated = false;
        hover_position = -1;
    }

    void addButton(std::string name)
    {
        buttons.push_back(name);
        is_updated = false;
    }

    void deleteButton(std::string name)
    {
        for (std::vector<std::string>::iterator it = buttons.begin(); it != buttons.end();)
        {
            if (*it == name)
                it = buttons.erase(it);
            else
                it++;
        }
    }

    void draw(sf::RenderWindow& window)
    {
        if (is_opened)
        {
            if (!is_updated)
            {
                int max_button_size_x = 0;
                for (int i = 0; i < buttons.size(); i++)
                {
                    text.setString(buttons[i]);
                    if (text.getLocalBounds().width > max_button_size_x)
                        max_button_size_x = text.getLocalBounds().width;
                }
                max_button_size_x *= 1.2;
                shape.setSize({(float)max_button_size_x, (float)(button_size_y * buttons.size())});
                hover_shape.setSize({(float)max_button_size_x, (float)(button_size_y)});
                is_updated = true;

            }


            window.draw(shape);
            if (hover_position >= 0)
            {
                hover_shape.setPosition(shape.getPosition().x, shape.getPosition().y + hover_position * button_size_y);
                window.draw(hover_shape);
            }
            for (int i = 0; i < buttons.size(); i++)
            {
                text.setString(buttons[i]);
                text.setPosition(shape.getPosition().x, shape.getPosition().y + i * button_size_y);
                window.draw(text);
            }
        }
    }

    bool checkCollision(int x, int y)
    {
        return (x > shape.getPosition().x && 
                x < shape.getPosition().x + shape.getSize().x &&
                y > shape.getPosition().y &&
                y < shape.getPosition().y + shape.getSize().y);
    }

    int onMousePressed(sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            is_opened = true;
            shape.setPosition({(float)event.mouseButton.x, (float)event.mouseButton.y});
        }
        if (event.mouseButton.button == sf::Mouse::Left && is_opened)
        {
            is_opened = false;
            return hover_position;
        }
        return -1;
    }

    void onMouseHover(sf::Event& event, sf::RenderWindow& window)
    {
        if (!is_opened)
            return;
        if (checkCollision(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        {
            hover_position = (sf::Mouse::getPosition(window).y - shape.getPosition().y) / button_size_y;
        }
        else
        {
            hover_position = -1;
        }
    }

};


const sf::Color ContextMenu::default_color = sf::Color(190, 210, 190);
const sf::Color ContextMenu::hover_color = sf::Color(150, 170, 150);
const sf::Color ContextMenu::text_color = sf::Color::Red;
const int ContextMenu::character_size = 16;
const int ContextMenu::button_size_y = 20;

struct Color
{
    int r, g, b;
};


// Вспомагательный класс, описывет шарик
// position - положение шарика; radius - радиус
// is_choosen - говорит о том, выбран ли шарик или нет
struct Ball
{
    sf::Vector2f position;
    float radius;
    bool is_choosen;
    Color color;

    Ball(sf::Vector2f position, float radius, Color color) : position(position), radius(radius), color(color)
    {
        is_choosen = false;
    }

    void setPosition(float new_x, float new_y)
    {
        position.x = new_x;
        position.y = new_y;
    }

    void setColor(int red, int green, int blue)
    {
        color.r = red;
        color.g = green;
        color.b = blue;
    }

    void setRadius(float new_radius)
    {
        radius = new_radius;
    }

    bool is_inside_rectangle(const sf::RectangleShape& rect)
    {
        float rect_x1 = rect.getPosition().x;
        float rect_y1 = rect.getPosition().y;

        float rect_x2 = rect_x1 + rect.getSize().x;
        float rect_y2 = rect_y1 + rect.getSize().y;

        if(rect_x1 > rect_x2)
        {
            float k = rect_x1;
            rect_x1 = rect_x2;
            rect_x2 = k;
        }

        if(rect_y1 > rect_y2)
        {
            float k = rect_y1;
            rect_y1 = rect_y2;
            rect_y2 = k;
        }

        // 1
        if((position.x >= rect_x1 && position.x <= rect_x2) && position.y <= rect_y1)
        {
            if(position.y + radius >= rect_y1)
            {
                return true;
            }
        }
        // 2
        if(position.x < rect_x1 && position.y < rect_y1)
        {
            if(distance(position, rect.getPosition()) <= radius)
            {
                return true;
            }
        }
        // 3
        if(position.x <= rect_x1 && (position.y >= rect_y1 && position.y <= rect_y2))
        {
            if(position.x + radius >= rect_x1)
            {
                return true;
            }
        }  
        // 4
        if(position.x < rect_x1 && position.y > rect_y2)
        {
            if(distance(position, {rect_x1, rect_y2}) <= radius)
            {
                return true;
            }
        }
        // 5
        if((position.x >= rect_x1 && position.x <= rect_x2) && position.y >= rect_y2)
        {
            if(position.y - radius <= rect_y2)
            {
                return true;
            }
        }
        // 6
        if(position.x > rect_x2 && position.y > rect_y2)
        {
            if(distance(position, {rect_x2, rect_y2}) <= radius)
            {
                return true;
            }
        }  
        // 7
        if(position.x >= rect_x2 && (position.y >= rect_y1 && position.y <= rect_y2))
        {
            if(position.x - radius <= rect_x1)
            {
                return true;
            }
        }
        // 8
        if(position.x > rect_x2 && position.y < rect_y1)
        {
            if(distance(position, {rect_x2, rect_y1}) <= radius)
            {
                return true;
            }
        } 
        // 9
        if((position.x > rect_x1 && position.x < rect_x2) && (position.y > rect_y1 && position.y < rect_y2))
        {
            return true;
        }   
    }

    // Метод, который рисует шарик на холстек окна window
    void draw(sf::RenderWindow& window)
    {
        // Тут рисуем белый кружочек
        sf::CircleShape circle(radius);
        circle.setFillColor({color.r, color.g, color.b});
        circle.setOrigin({radius, radius});
        circle.setPosition(position);
        window.draw(circle);

        // Если шарик выбран
        if (is_choosen)
        {
            // То рисуем "уголки"
            float fraction = 0.7;
            draw_line(window, {position.x - radius, position.y + radius}, {position.x - radius, position.y + radius*fraction});
            draw_line(window, {position.x - radius, position.y + radius}, {position.x - fraction * radius, position.y + radius});

            draw_line(window, {position.x + radius, position.y + radius}, {position.x + radius, position.y + radius*fraction});
            draw_line(window, {position.x + radius, position.y + radius}, {position.x + radius*fraction, position.y + radius});

            draw_line(window, {position.x + radius, position.y - radius}, {position.x + radius*fraction, position.y - radius});
            draw_line(window, {position.x + radius, position.y - radius}, {position.x + radius, position.y - radius*fraction});

            draw_line(window, {position.x - radius, position.y - radius}, {position.x - radius*fraction, position.y - radius});
            draw_line(window, {position.x - radius, position.y - radius}, {position.x - radius, position.y - radius*fraction});
        }
    }
};


int main()
{
    srand(time(0));
    const int width = 800;
    const int height = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Move and Delete!", sf::Style::Close, settings);
    window.setFramerateLimit(60);


    // Создаём связный список из шариков
    // Связыный список -- потому что нам нужно будет постоянно удалять и добавлять в этот список
    std::list<Ball> balls;
    balls.push_back(Ball({200, 200}, 26, {255, 255, 255}));
    balls.push_back(Ball({400, 300}, 20, {255, 255, 255}));
    balls.push_back(Ball({500, 100}, 16, {255, 255, 255}));
    balls.push_back(Ball({200, 400}, 18, {255, 255, 255}));
    balls.push_back(Ball({350, 150}, 22, {255, 255, 255}));
    balls.push_back(Ball({750, 400}, 21, {255, 255, 255}));

    // Создаём прямоугольник выделения
    // Обратите внимание на четвёртый параметр sf::Color(150, 150, 240, 50)
    // Это alpha - прозрачность      0 = полностью прозрачный     255 = непрозрачный
    sf::RectangleShape selection_rect;
    selection_rect.setFillColor(sf::Color(150, 150, 240, 50));
    selection_rect.setOutlineColor(sf::Color(200, 200, 255));
    selection_rect.setOutlineThickness(1);

    // Специальная переменная, которая будет показывать, что мы находимся в режиме выделения
    bool is_selecting = false;
    bool some_ball_is_choosen = false;
    bool is_moving = false;
    bool is_released = false;
    bool clicking_on_the_circle = false;

    float old_x = 0;
    float old_y = 0;
    float new_x = 0;
    float new_y = 0;

    sf::Font font;
    if (!font.loadFromFile("consolas.ttf"))
    {
        cout << "Can't load button font" << endl;
    }

    ContextMenu context_menu(font);
    context_menu.addButton("Paste");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка на нажатие клавиши Delete и удаление шарика
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Delete) 
                {
                    for (std::list<Ball>::iterator it = balls.begin(); it != balls.end();)
                    {
                        if (((*it).is_choosen) == true)
                            it = balls.erase(it);
                        else
                            it++;
                    }
                }
            }

            // Проверка на нажатие Пробел и перекрашивание выделенных шаров
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space) 
                {
                    for (std::list<Ball>::iterator it = balls.begin(); it != balls.end(); it++)
                    {
                        if((*it).is_choosen == true)
                        {
                            int r = rand() % 255;
                            int g = rand() % 255;
                            int b = rand() % 255;
                            (*it).setColor(r, g, b);
                        }
                    }
                }
            }

            // При движении мыши
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mouse_position = {(float)event.mouseMove.x, (float)event.mouseMove.y};

                context_menu.onMouseHover(event, window);
                
                // Если мы находимся в режиме выделения, то меняем прямоугольник выделения
                if (is_selecting)
                {
                    selection_rect.setSize(mouse_position - selection_rect.getPosition());

                    // Проходимся по массиву и опредляем выбран ли шарик
                    for (Ball& b : balls)
                    {   
                        if(b.is_inside_rectangle(selection_rect) == true)
                        {
                            b.is_choosen = true;
                        }
                        else
                        {
                            b.is_choosen = false;
                        }
                    }
                } 
                
                // Если мы находимся врежиме перемещения
                if(is_moving == true)
                {
                    //Новые координаты мышки
                    new_x = (float)event.mouseMove.x;
                    new_y = (float)event.mouseMove.y;

                    //Нахождение смещения мышки
                    float delta_x = new_x - old_x;
                    float delta_y = new_y - old_y;

                    //Перемещение каждого выделенного шарика
                    for (Ball& b : balls)
                    {
                        if(b.is_choosen == true)
                        {
                            b.setPosition(b.position.x + delta_x, b.position.y + delta_y);
                        }
                    }

                    // Переприсвоение старых координат
                    old_x = new_x;
                    old_y = new_y;
                
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse_position = {(float)event.mouseButton.x, (float)event.mouseButton.y};

                // Запоминаем старые координаты
                old_x = (float)event.mouseButton.x;
                old_y = (float)event.mouseButton.y;

                int context_menu_press_result = context_menu.onMousePressed(event);
                
                // Работа с контекстным меню
                for(std::list<Ball>::iterator it = balls.begin(); it != balls.end();)
                {
                    if((*it).is_choosen == true || context_menu_press_result == 0)
                    {
                        // Начало работы с контекстным меню:
                        if (context_menu_press_result == 0)
                        {
                            std::cout << "Paste" << std::endl;
                            balls.push_back(Ball(mouse_position, 5 + rand() % 40, {255, 255, 255}));
                            it++;
                            break;                        
                        }
                        if (context_menu_press_result == 1)
                        {
                            std::cout << "Delete" << std::endl;
                            it = balls.erase(it);
                        }
                        if (context_menu_press_result == 2)
                        {
                            std::cout << "Change color" << std::endl;
                            int red = rand() % 255;
                            int green = rand() % 255;
                            int blue = rand() % 255;
                            (*it).setColor(red, green, blue);
                            it++;
                        }
                        if (context_menu_press_result == 3)
                        {
                            std::cout << "Change radius" << std::endl;
                            (*it).setRadius(rand() % 60);
                            it++;
                        }
                        else
                        {
                            it++;
                        }
                    }
                    else
                    {
                        it++;
                    }
                }

                // При нажатии левой кнопки мыши:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool is_clicking_on_the_selected_ball = false;

                    for (Ball& b : balls)
                    {
                        if (distance(mouse_position, b.position) < b.radius && b.is_choosen == true)
                        {
                            is_clicking_on_the_selected_ball = true;
                            break;
                        }
                    }

                    // Если не зажат левый Control, то снимаем все выделения при нажатии
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && is_clicking_on_the_selected_ball == false)
                    {
                        for (Ball& b : balls)
                            b.is_choosen = false;
                        some_ball_is_choosen = false;
                    }

                    // Проверяем попал ли курсор в какой-нибудь шарик, если попал - выделяем
                    for (Ball& b : balls)
                    {
                        if (distance(mouse_position, b.position) < b.radius)
                        {
                            b.is_choosen = true;
                            some_ball_is_choosen = true;
                            break;
                        }
                    }

                    // Проверка для перехода в режим перемещения
                    if(some_ball_is_choosen == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        is_moving = true;
                    }

                    // Задаём новое положения прямоугольника выделения и проверяем не начали ли мы выделение на шарике
                    if(some_ball_is_choosen == true)
                    {
                        is_selecting = false;
                    }
                    else
                    {
                        is_selecting = true;
                        selection_rect.setPosition(mouse_position);
                        selection_rect.setSize({0, 0});
                    }

                    is_released = false;
                }

                // Обработка нажатия на правую кнопку мыши:
                if (event.mouseButton.button == sf::Mouse::Right)
                {   
                    sf::Vector2f position_of_ball;
                    float radius_of_ball;

                    // Удаляем выделение на всех шариках, при каждом нажатии на правую кнопку
                    if (some_ball_is_choosen == true)
                    {
                        for (Ball& b : balls)
                        {
                            b.is_choosen = false;
                        }
                        some_ball_is_choosen = false;
                    }

                    // Проверяем попал ли курсор в какой-нибудь шарик, если попал - выделяем
                    for (Ball& b : balls)
                    {
                        if (distance(mouse_position, b.position) < b.radius)
                        {
                            b.is_choosen = true;
                            some_ball_is_choosen = true;
                            position_of_ball = b.position;
                            radius_of_ball = b.radius;
                            break;
                        }
                    }

                    if (distance(mouse_position, position_of_ball) < radius_of_ball && clicking_on_the_circle == false)
                    {
                        clicking_on_the_circle = true;
                        context_menu.addButton("Delete");
                        context_menu.addButton("Change color");
                        context_menu.addButton("Change radius");
                    }
                    else
                    {
                        if(distance(mouse_position, position_of_ball) > radius_of_ball && clicking_on_the_circle == true)
                        {
                            clicking_on_the_circle = false;
                            context_menu.deleteButton("Delete");
                            context_menu.deleteButton("Change color");
                            context_menu.deleteButton("Change radius");
                        }
                    }
                    
                }
            }

            // При отпускании кнопки мыши
            if (event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2f mouse_position = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                // Выходим из режима выделения
                is_selecting = false;
                is_released = true;
                is_moving = false;
            }

        }

        window.clear(sf::Color::Black);
        
        // Рисуем все шарики
        for (Ball& b : balls)
        {
            b.draw(window);
        }

        // Рисуем прямоугольник выделения
        if (is_selecting)
            window.draw(selection_rect);
        context_menu.draw(window);

        window.display();
    }

    return 0;
}