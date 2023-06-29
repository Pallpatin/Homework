#include <iostream>
#define random(min,max) (min+rand()%(max-min+1))
using namespace std;

// создать класс машина
// описан
// марка
// цвет
// гос номер(уникальный)
//
// создать класс парковка
// реализовать метод добавления машин и удаления по гос - номеру
//
// предположить что мы можем копировать машину(но при
//    копировании новая машину будет с уникальным гос номером)




string marks[5]{ "lada","uaz","kamaz","jiguli","oka" };
string colours[5]{ "leopard","zebra","snake","tiger","crocodile" };
char bukva[12]{ 'A','B','E','K','M','H','O','P','C','T','Y','X'};

class Car {
    static string* numbers;
    static unsigned int countOfNumbers;
    string mark;
    string colour;
    string number;

    string generatenumber() {
        string buf;
        while (1) {
            buf = {bukva[random(0,11)],char(random('0','9')),char(random('0','9')),char(random('0','9')),bukva[random(0,11)], bukva[random(0,11)],'1','6','1'};
            if (numbers == nullptr) {
                numbers = new string[1]{ buf };
                countOfNumbers = 1;
                break;
            }
            else {
                for (int i = 0; i < countOfNumbers; i++) {
                    if (buf == numbers[i]) {
                        continue;
                    }
                }
                string* buffer = new string[countOfNumbers + 1];
                for (int i = 0; i < countOfNumbers; i++) {
                    buffer[i] = numbers[i];
                }
                buffer[countOfNumbers] = buf;
                countOfNumbers++;
                delete[]numbers;
                numbers = buffer;
                break;
            }

        }
        return buf;
    }
public:
    Car() {
        this->number = generatenumber();
        this->colour = colours[random(0, 4)];
        this->mark = marks[random(0, 4)];
    };
    void showcar() {
        cout << number << '\t' << mark <<'\t' << colour << endl;
    }
    void newnumber() {
        this->number = generatenumber();
    }
};
string* Car::numbers = nullptr;
unsigned int Car::countOfNumbers = 0;

class Parking {
    Car* cars = nullptr;
    unsigned int countofcars = 0;
public:
    void addcar(Car newcar) {
        if (cars == nullptr) {
            cars = new Car[1]{ newcar };
            countofcars++;
        }
        else {
            Car* buf = new Car[countofcars + 1];
            for (int i = 0; i < countofcars; i++) {
                buf[i] = cars[i];
            }
            buf[countofcars] = newcar;
            countofcars++;
            delete[]cars;
            cars = buf;
        }
    }
    void copycar(Car newcar) {
        newcar.newnumber();
        if (cars == nullptr) {
            cars = new Car[1]{ newcar };
            countofcars++;
        }
        else {
            Car* buf = new Car[countofcars + 1];
            for (int i = 0; i < countofcars; i++) {
                buf[i] = cars[i];
            }
            buf[countofcars] = newcar;
            countofcars++;
            delete[]cars;
            cars = buf;
        }
    }
};
int main()
{
    srand(time(0));
    const int siz = 100;
    Car cars[siz];
    for (int i = 0; i < siz; i++) {
        cars[i].showcar();
    }
    
}
