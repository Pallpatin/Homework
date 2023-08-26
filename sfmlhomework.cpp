#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define randcolor rand()%(255),rand()%(255),rand()%(255),255

using namespace std;

const int Window_Width = 600;
const int Window_Height = 800;
const int Shape_Radius = 100.f;

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(Window_Width, Window_Height), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Magenta);
    
    vector<sf::CircleShape> shapes;
    int MaxCountShapes = ((Window_Height * Window_Width) / (4 * pow(Shape_Radius, 2)));
    shapes.resize(MaxCountShapes);
    cout << shapes.size();
    for (int i = 0,X=0,Y=0; i < shapes.size(); i++) {
        shapes[i].setRadius(Shape_Radius);
        shapes[i].setFillColor(sf::Color(randcolor));
        shapes[i].setPosition(X, Y);
        X += 2 * Shape_Radius;
        if (X + 2 * Shape_Radius > Window_Width) {
            X = 0;
            Y += 2 * Shape_Radius;
        }
    }
    bool FlagSpace = 0;
    bool FlagR = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.key.code==sf::Keyboard::Subtract&&shapes.size()!=0||FlagSpace) {
                if (FlagSpace == 0) {
                    shapes.pop_back();
                    FlagSpace = 1;
                    cout << endl << FlagSpace;
                }else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))FlagSpace = 0;
            }
            else if (event.key.code == sf::Keyboard::Add && shapes.size() < MaxCountShapes||FlagR) {
                if (!FlagR) {
                    FlagR = 1;
                    sf::CircleShape shape(Shape_Radius);
                    shape.setFillColor(sf::Color(randcolor));
                    int X, Y;
                    X = shapes.back().getPosition().x;
                    Y = shapes.back().getPosition().y;
                    X += 2 * Shape_Radius;
                    if (X + 2 * Shape_Radius > Window_Width) {
                        X = 0;
                        Y += 2 * Shape_Radius;
                    }
                    shape.setPosition(X, Y);
                    cout << shape.getPosition().x << " " << shape.getPosition().y;
                    shapes.push_back(shape);
                }
                else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Add))FlagR = 0;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int poz=0;
                for (int i = 0; i < shapes.size(); i++) {
                    if (shapes[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        shapes.erase(shapes.begin() + i);
                        poz = i;
                        break;
                    }
                }
                for (int i = poz+1,X,Y; i < shapes.size(); i++) {
                    X = shapes[i - 1].getPosition().x;
                    Y = shapes[i - 1].getPosition().y;
                    X += 2 * Shape_Radius;
                    if (X + 2 * Shape_Radius > Window_Width) {
                        X = 0;
                        Y += 2 * Shape_Radius;
                    }
                    shapes[i].setPosition(X, Y);
                }
            }

        }

        window.clear();
        for (auto el : shapes) {
            window.draw(el);
        }
        //window.draw(shape);
        window.display();
    }

    return 0;
}
