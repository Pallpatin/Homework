#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::string path = "D:\\top academy\\дз\\calculator\\calculator\\arial.ttf";
const int SIZEOFWIN = 600;
const int INTERVAL = SIZEOFWIN / 20;
const int RADIUS = (SIZEOFWIN + INTERVAL) / 12;
const float epsilon = 0.00000000001;

const int proz = 255;
sf::Color FIRSTCOL (164, 164, 164, proz);
sf::Color SECCOL(4, 4, 4, proz);
sf::Color THRIEDCOL(239, 146, 40, proz);
sf::Color FOURCOL(253, 246, 227, proz);
sf::Color FIFTHCOL(51, 51, 51, proz);
sf::Color SIXCOL(245, 245, 245, proz);
sf::Color NUMBERCOL(242, 242, 242, proz);

std::string NAMESOFBUTTONS[20]{ "AC","+/-","%","/","7","8","9","X","4","5","6","-","1","2","3","+","0","00",".","=" };


class Button {
    sf::Text NAMESHOWN;
    //sf::Font font;
public:
    sf::CircleShape shape;
    std::string getstr() {
        return NAMESHOWN.getString();
    }
    Button() {
        shape.setRadius(RADIUS);
    }
    void setSTRING(std::string name) {
        this->NAMESHOWN.setString(name); 
    }
    void setFont(sf::Font& font) {
        //this->font = font;
        NAMESHOWN.setFont(font);
    }
    void setSize(int numb) {
        this->NAMESHOWN.setCharacterSize(numb);
    }
    void setPozition(int X,int Y) {
        shape.setPosition(X, Y);
        NAMESHOWN.setPosition(shape.getPosition().x+(RADIUS - NAMESHOWN.getCharacterSize()/2), shape.getPosition().y+(RADIUS-NAMESHOWN.getCharacterSize()/2));
    }
    void render(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(NAMESHOWN);


    }
    void setcolor(sf::Color& col_but, sf::Color& text_col) {
        NAMESHOWN.setFillColor(text_col);
        shape.setFillColor(col_but);
    }
};

class Calculator {
    sf::Text written;
    
    sf::Font arial;
    std::vector<std::vector<Button>> buttons;
    float NumberShown = 0;
    void chek() {
        written.setString(std::to_string(NumberShown));
    }
public:
    Calculator() {
        arial.loadFromFile("D:\\top academy\\дз\\calculator\\calculator\\arial.ttf");
        buttons.resize(5);
        for (int i = 0; i < buttons.size(); i++) {
            buttons[i].resize(4);
        }
        int k = 0;
        for (int i = 0; i < buttons.size(); i++) {
            for (int j = 0; j < buttons[i].size(); j++) {
                buttons[i][j].setFont(arial);
                buttons[i][j].setSTRING(NAMESOFBUTTONS[k++]);
                if (i == 0 && j <= 2) {
                    buttons[i][j].setcolor(FIRSTCOL, SECCOL);
                }else if (j==3){ buttons[i][j].setcolor(THRIEDCOL, FOURCOL); }
                else {
                    buttons[i][j].setcolor(FIFTHCOL, SIXCOL);
                }
                buttons[i][j].setPozition(INTERVAL/2+ j*(INTERVAL+2*RADIUS), i * (INTERVAL + 2 * RADIUS)+ SIZEOFWIN/4);
                buttons[i][j].setSize(SIZEOFWIN / 30);
            }
        }
        written.setFont(arial);
        written.setPosition(INTERVAL, INTERVAL);
        written.setFillColor(NUMBERCOL);
        written.setCharacterSize(SIZEOFWIN / 10);
        written.setString(std::to_string(NumberShown));
    }
    void buttonpushed(Button butt) {
        int num = std::stoi(butt.getstr());
        if (std::fmod(num, 1.0) > epsilon && std::fmod(num, 1.0) < 1.0 - epsilon) {
            NumberShown += num / 10;
        }
        else {
            NumberShown *= 10;
            NumberShown += num;
        }
    }
    void Run() {
        sf::RenderWindow window(sf::VideoMode(SIZEOFWIN, SIZEOFWIN*1.4), "Calculator");
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    for (int i = 0; i < buttons.size(); i++) {
                        for (int j = 0; j < buttons[i].size(); j++) {
                            if (buttons[i][j].shape.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

                            }
                        }
                    }
                    
                }

            }
            window.clear();
        for (int i = 0; i < buttons.size(); i++) {
            for (int j = 0; j < buttons[i].size(); j++) {
                buttons[i][j].render(window);
            }
        }
        chek();
        window.draw(written);
        window.display();

        }
    }
};

int main()
{
    Calculator calcul;
    calcul.Run();

}