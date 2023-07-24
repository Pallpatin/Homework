

#include <iostream>
#include <map>;
#include <fstream>
#include <string>

using namespace std;

//Задание №2
//Используя контейнер map реализовать программу – словарь.
//Основные возможности :
//■ поиск слова;
//■ добавление, удаление, редактирование слов;
//■ чтение и запись словаря в файл.

class Slovar {
    map<string, string> samslovar;
    string pathtofile = "pathtoslovar.txt";
public:
    void inputVord() {
        string k,v;
        cout << "\ninput word - ";
        cin >> k;
        cout << "input value of " << k << " - ";
        cin >> v;
        samslovar.emplace(k, v);
    }
    void findword() {
        cout << "\ninput word to find ";
        string word;
        cin >> word;
        auto result = samslovar.find(word);
        if (result == samslovar.end())cout << " word doesn't found ";
        else cout << result->second << endl;
    }
    void savetofile() {
        ofstream out(pathtofile);
        if (out.is_open()) {
            for (auto el : samslovar) {
                out << el.first << '{' << el.second << "};" << endl;
            }
            out.close();
        }
        else throw "file did not open";
    }
    void loadfromfile() {
        ifstream in(pathtofile);
        if (in.is_open()) {
            string key;
            string mean;
            string buf;
            int i;
            while (getline(in, buf)) {
                i = 0;
                key = "";
                mean = "";
                while (buf[i] != '{') {
                    key += buf[i++];
                }
                i++;
                while (buf[i] != '}' && buf[i + 1] != ';') {
                    mean += buf[i++];
                }
                samslovar.emplace(key, mean);
            }
            in.close();
        }
        else {
            cout << "no data recorded\n";
            ofstream out(pathtofile);
            out.close();
        }
        
    }
};

int main()
{
    Slovar s;
    s.loadfromfile();
    int act;
    while (1) {
        cout << "input action button\n 1 - to input word\n 2 - to find word\n 0 - to save\n";
        do {
            cin >> act;
        } while (act < 0 || act>3);
        switch (act) {
        case 1:
            s.inputVord();
            break;
        case 2:
            s.findword();
            break;
        case 0:
            s.savetofile();
            break;
        }
    }
}
