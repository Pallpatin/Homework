

#include <iostream>
#include <Windows.h>
#include <map>
#include <string>

// Получение данных с сервера, или объекта с большой задержкой, ускорение этого времени путём записи данных в кэш.
using namespace std;


class FarawayServer {
    map<unsigned int,string> info;
    unsigned int DelayTime = 3000; // время задержки в миллисекундах
    unsigned int TimeSinceUpdated ;// время
public:
    FarawayServer() {
        for (int i = 0; i < 100; i++) {
            info.emplace(i, "data " + to_string(rand() % 500));
        }
        TimeSinceUpdated = time(0);
    }
    string tofind(unsigned int id) {
        Sleep(DelayTime);
        return info.find(id)->second;
    }
    unsigned int getTime() {
        return TimeSinceUpdated;
    }
};

class Proxy {
    FarawayServer* serv;
    map<unsigned int, string> cash;
    unsigned int TimeSinceUpdated;
public:
    Proxy(FarawayServer* serv) {
        this->serv = serv;
        TimeSinceUpdated = time(0);
    }
    string getinfo(int id) {
        if (this->TimeSinceUpdated < serv->getTime())cash.clear(); // отчистка кэша,при обновлении сервера
        {
            auto it = cash.find(id);
            if (it != cash.end()) {
                cout << " was cashed ";
                return it->second;
            }
        }
        string it = serv->tofind(id);
        cash.emplace(id, it);
        return it;
    }
};

int main()
{
    FarawayServer* serv = new FarawayServer;
    Proxy prox(serv);
    
    for (int i = 0,random; i < 100; i++) {
        random = rand() % 20;
        cout <<random<<" is " << prox.getinfo(random) << endl;
    }

}



