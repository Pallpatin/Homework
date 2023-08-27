//#include <SFML/Graphics.hpp>
//#include <string>
//#include <vector>
//using namespace std;
//
//const int WINDOW_WIDTH = 600;
//const int WINDOW_HEIGHT = WINDOW_WIDTH / 1.6180339887;
//
//
//class Button {
//    string name;
//    int X;
//    int Y;
//    int width = WINDOW_WIDTH / 16;
//    int height = WINDOW_HEIGHT / 5;
//    sf::Keyboard key;
//public:
//    Button(string name) {
//        this->name = name;
//    }
//    void setName(string name) {
//        this->name = name;
//    }
//    void setPozition(int X, int Y) {
//        this->X = X;
//        this->Y = Y;
//    }
//    void makewider(int k) {
//        width += (width / 2) * k;
//    }
//};
//
//class keyboard {
//    vector<vector<Button>>keys;
//public:
//    keyboard() {
//        keys.resize(5);
//        keys[0].resize(15);
//        keys[1].resize(15);
//        keys[2].resize(13);
//        keys[3].resize(11);
//        keys[4].resize(4);
//        keys[0]={"~","1","2","3","4" }
//    }
//};
//
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Keyboard");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Используем префикс std:: перед стандартными типами и функциями
const int WINDOW_WIDTH = 600; // Исправляем опечатку в слове WIDTH
const int WINDOW_HEIGHT = WINDOW_WIDTH / 1.6180339887;

class Button {
    std::string name;
    int X;
    int Y;
    int width = WINDOW_WIDTH / 16;
    int height = WINDOW_HEIGHT / 5;
    sf::Keyboard::Key key; // Используем тип sf::Keyboard::Key для хранения кода клавиши
    sf::RectangleShape shape; // Используем sf::RectangleShape для рисования кнопки
    sf::Text text; // Используем sf::Text для рисования текста на кнопке
public:
    Button(){}
    Button(std::string name, sf::Keyboard::Key key, sf::Font& font) {
        this->name = name;
        this->key = key;
        shape.setSize(sf::Vector2f(width, height)); // Задаем размер кнопки
        shape.setFillColor(sf::Color(200, 200, 200)); // Задаем цвет кнопки
        text.setString(name); // Задаем текст кнопки
        text.setFont(font); // Задаем шрифт текста
        text.setCharacterSize(24); // Задаем размер текста
        text.setFillColor(sf::Color::Black); // Задаем цвет текста
    }
    std::string getname() { return name; }
    int GetWidth() {
        return width;
    }
    int GetHeight() {
        return height;
    }
    void setName(std::string name) {
        this->name = name;
        text.setString(name); // Обновляем текст кнопки
    }
    void setPozition(int X, int Y) {
        this->X = X;
        this->Y = Y;
        shape.setPosition(X, Y); // Задаем позицию кнопки
        text.setPosition(X + width / 2 - text.getLocalBounds().width / 2, Y + height / 2 - text.getLocalBounds().height / 2); // Центрируем текст на кнопке
    }
    void makewider(int k) {
        width += (width / 2) * k;
        shape.setSize(sf::Vector2f(width, height)); // Обновляем размер кнопки
        text.setPosition(X + width / 2 - text.getLocalBounds().width / 2, Y + height / 2 - text.getLocalBounds().height / 2); // Центрируем текст на кнопке
    }
    void draw(sf::RenderWindow& window) {
        window.draw(shape); // Рисуем кнопку на окне
        window.draw(text); // Рисуем текст на кнопке
    }
    bool isPressed() {
        return sf::Keyboard::isKeyPressed(key); // Проверяем, нажата ли клавиша, соответствующая кнопке
    }
};

class keyboard {
    std::vector<std::vector<Button>>keys;
    sf::Font font; // Шрифт для текста на кнопках
public:
    keyboard() {
        keys.resize(5);
        keys[0].resize(15);
        keys[1].resize(15);
        keys[2].resize(13);
        keys[3].resize(11);
        keys[4].resize(4);
        // Загружаем шрифт из файла
        if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial\\Arial Regular")) {
            // Обрабатываем ошибку загрузки шрифта
            std::cout << "Error loading font\n";
        }
        // Заполняем вектор keys кнопками с именами и кодами клавиш
        keys[0] = { Button("~", sf::Keyboard::Tilde, font), Button("1", sf::Keyboard::Num1, font), Button("2", sf::Keyboard::Num2, font), Button("3", sf::Keyboard::Num3, font), Button("4", sf::Keyboard::Num4, font), Button("5", sf::Keyboard::Num5, font), Button("6", sf::Keyboard::Num6, font), Button("7", sf::Keyboard::Num7, font), Button("8", sf::Keyboard::Num8, font), Button("9", sf::Keyboard::Num9, font), Button("0", sf::Keyboard::Num0, font), Button("-", sf::Keyboard::Dash, font), Button("+", sf::Keyboard::Equal, font), Button("<-", sf::Keyboard::BackSpace, font) };
        keys[1] = { Button("Tab", sf::Keyboard::Tab, font), Button("Q", sf::Keyboard::Q, font), Button("W", sf::Keyboard::W, font), Button("E", sf::Keyboard::E, font), Button("R", sf::Keyboard::R, font), Button("T", sf::Keyboard::T, font), Button("Y", sf::Keyboard::Y, font), Button("U", sf::Keyboard::U, font), Button("I", sf::Keyboard::I, font), Button("O", sf::Keyboard::O, font), Button("P", sf::Keyboard::P, font), Button("[", sf::Keyboard::LBracket, font), Button("]", sf::Keyboard::RBracket, font), Button("\\", sf::Keyboard::Slash,font) };
        keys[2] = { Button("Caps", sf::Keyboard::Escape, font), Button("A", sf::Keyboard::A, font), Button("S", sf::Keyboard::S, font), Button("D", sf::Keyboard::D, font), Button("F", sf::Keyboard::F, font), Button("G", sf::Keyboard::G, font), Button("H", sf::Keyboard::H, font), Button("J", sf::Keyboard::J, font), Button("K", sf::Keyboard::K, font), Button("L", sf::Keyboard::L, font), Button(";", sf::Keyboard::SemiColon, font), Button("'", sf::Keyboard::Quote, font), Button("Enter", sf::Keyboard::Enter, font) };
        keys[3] = { Button("Shift", sf::Keyboard::LShift, font), Button("Z", sf::Keyboard::Z, font), Button("X", sf::Keyboard::X, font), Button("C", sf::Keyboard::C, font), Button("V", sf::Keyboard::V, font), Button("B", sf::Keyboard::B, font), Button("N", sf::Keyboard::N, font), Button("M", sf::Keyboard::M, font), Button(",", sf::Keyboard::Comma, font), Button(".", sf::Keyboard::Period, font), Button("/", sf::Keyboard::Slash, font) };
        keys[4] = { Button("Ctrl", sf::Keyboard::LControl, font), Button("Alt", sf::Keyboard::LAlt, font), Button("Space", sf::Keyboard::Space, font), Button("<-", sf::Keyboard::Left, font) };
        // Делаем некоторые кнопки шире
        keys[0][13].makewider(1);
        keys[1][0].makewider(1);
        keys[2][0].makewider(1);
        keys[2][12].makewider(1);
        keys[3][0].makewider(2);
        keys[4][0].makewider(1);
        keys[4][2].makewider(6);
        // Задаем позиции кнопок
        int x = 0;
        int y = 0;
        for (int i = 0; i < 5; i++) {
            x = 0;
            for (int j = 0; j < keys[i].size(); j++) {
                keys[i][j].setPozition(x, y);
                x += keys[i][j].GetWidth();
            }
            y += keys[i][0].GetHeight();
        }
    }
    void draw(sf::RenderWindow& window) {
        // Рисуем клавиатуру на окне
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < keys[i].size(); j++) {
                keys[i][j].draw(window);
            }
        }
    }
    void handleInput() {
        // Обрабатываем ввод пользователя
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < keys[i].size(); j++) {
                if (keys[i][j].isPressed()) {
                    // Выводим на консоль имя нажатой кнопки
                    std::cout << keys[i][j].getname() << "\n";
                }
            }
        }
    }
};


int main()
{
    // Создаем окно с заголовком "Клавиатура"
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Keyboard");
    // Создаем объект класса keyboard
    keyboard kbd;

    while (window.isOpen())
    {
        // Обрабатываем события окна
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); // Закрываем окно, если пользователь нажал на крестик
        }

        window.clear(); // Очищаем окно
        kbd.draw(window); // Рисуем клавиатуру на окне
        kbd.handleInput(); // Обрабатываем ввод пользователя
        window.display(); // Отображаем окно
    }

    return 0;
}

