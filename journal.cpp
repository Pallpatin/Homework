#include <iostream>
using namespace std;

class Discipline {
    string name;
    char* marks = nullptr;
public:
    Discipline() {};
    Discipline(string name) {
        this->name = name;
    }
    ~Discipline() {
        if (marks != nullptr) { delete[]marks; }
    }
    void addmark(char mark) {
        if (marks == nullptr) {
            marks = new char[1];
            marks[0] = mark;
        }
        else {
            unsigned int size = _msize(marks);
            char* buf = new char [size + 1];
            for (int i = 0; i < size; i++) {
                buf[i] = marks[i];
            }
            buf[size] = mark;
            delete[]marks;
            marks = buf;
        }
    }
    string getName() {
        return name;
    }
    void showmarks() {
        int siz = _msize(marks) / 4;
        for (int i = 0; i < siz; i++)cout << marks[i] << " ";
    }
    char getmediumchar() {
        int sred = 0;
        char a = '0';
        if (marks != nullptr) {
            int siz = _msize(marks);
            for (int i = 0; i < siz; i++) {
                sred += marks[i] - 48;
            }
            sred /= siz;
        }
        return sred;
    }
};
class Student {
    static unsigned int ids;
    unsigned int id;
    string name;
    string phone;
    Discipline* disciplines = nullptr;
    int CountDisc = 0;

public:
    Student(string name) {
        this->name = name;
        this->id = ids++;
    }
    ~Student() {
        if (disciplines != nullptr){
            delete[] disciplines;
        }
    }
    void adddiscipline(Discipline disc) {
        if (disciplines == nullptr) {
            disciplines = new Discipline[1]{ disc };
            CountDisc = 1;
        }
        else {
            
            Discipline* buf = new Discipline[CountDisc + 1];
            for (int i = 0; i < CountDisc; i++) {
                buf[i] = disciplines[i];
            }
            buf[CountDisc] = disc;
            delete[]disciplines;
            disciplines = buf;
        }
    }
    string getPhone() {
        return phone;
    }
    void setPhone(string phone) {
        this->phone = phone;
    }
};
unsigned int Student :: ids = 1;
int main()
{
    std::cout << "Hello World!\n";
}
