
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Persone {
    string name;
    string homephone;
    string workphone;
    string mobilphone;
    string dopinfo;
public:
    string getName() {
        return name;
    }
    string getHomephone() {
        return homephone;
    }
    string getWorkphone(){
        return workphone;
    }
    string getMobilphone() {
        return mobilphone;
    }
    string getDopinfo() {
        return dopinfo;
    }
    void setName(string name) {
        this->name = name;
    }
    void setHomephone(string homephone) {
        this->homephone = homephone;
    }
    void setWorkphone(string workphone) {
        this->workphone = workphone;
    }
    void setMobilphone(string mobilphone) {
        this->mobilphone = mobilphone;
    }
    void setDopinfo(string dopinfo) {
        this->dopinfo = dopinfo;
    }
    void showPersone() {
        cout << name << endl;
        string nostr;

        if (homephone != nostr) {
            cout << "homephone { " << homephone << " }\n";
        }
        if (workphone != nostr) {
            cout << "workphone { " << workphone << " }\n";
        }
        if (mobilphone != nostr) {
            cout << "mobilphone { " << mobilphone << " }\n";
        }
        if (workphone != nostr) {
            cout << "dopinfo { " << dopinfo << " }\n";
        }
    }
};

class Telephonebook {
    Persone* arr = nullptr;
    string path = "telephones.txt";
    unsigned int count = 0;
private:
    static string* separate(string str){
        int count = 5;
        int siz = size(str);
        string* buf = new string[count];
        
        for (int i = 0, j = 0; i < count && j <= siz; j++) {
            if (str[j] == ';') {
                i++;
                continue;
            }
            buf[i] += str[j];
        }
        return buf;
    }
public:
    ~Telephonebook() {
        if (arr != nullptr) {
            delete[]arr;
        }
    }
    void savetofile() {
        ofstream out(path);
        out << to_string(count) << endl;
        for (int i = 0; i < count; i++) {
            out << arr->getName() << ';' << arr->getHomephone() << ';' << arr->getWorkphone() << ';' << arr->getMobilphone() << ';' << arr->getDopinfo() << endl;
        }
        out.close();
    }
    void loadfromfile() {
        ifstream in(path);
        if (in.is_open()) {
            string buf;
            getline(in, buf);
            count = stoi(buf);
            arr = new Persone[count];
            int i = 0;
            while (getline(in, buf)) {
                string* secbuf = Telephonebook::separate(buf);
                arr->setName(secbuf[0]);
                arr->setHomephone(secbuf[1]);
                arr->setWorkphone(secbuf[2]);
                arr->setMobilphone(secbuf[3]);
                arr->setDopinfo(secbuf[4]);
            }
        }
        in.close();
    }
    void addpersone(Persone contact) {
        Persone* buf = new Persone[count + 1];
        for (int i = 0; i < count; i++) {
            buf[i] = arr[i];
        }
        buf[count] = contact;
        count++;
        if (arr != nullptr) {
            delete[]arr;
        }
        arr = buf;
    }
    void showall() {
        for (int i = 0; i < count; i++) {
            arr->showPersone();
        }
    }
};

int main()
{
    Telephonebook Tau;
    Persone p;
    p.setName("anton");
    p.setMobilphone("6546489");
    Tau.addpersone(p);
    Tau.showall();
    Tau.savetofile();
    for (int i = 0; i < 3; i++) {
        cout << endl;
    }
    Telephonebook sec;
    sec.loadfromfile();
    sec.showall();
}

