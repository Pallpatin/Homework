
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;



class Student {
    string name;
    unsigned int id;
    vector<char> marks;
    static unsigned int idtogive;
public:
    Student(string name) {
        this->name = name;
        this->id = idtogive++;
    }
    Student(string name, unsigned int id, vector<char> marks) {
        if (id >= idtogive)idtogive = id + 1;
        this->id = id;
        this->name = name;
        this->marks = marks;
    }
    void addmark(char mark) {
        marks.push_back(mark);
    }
    float sredBall() {
        float sred = 0;
        for (auto el : marks) {
            sred += el - 48;
        }
        sred /= marks.size();
        return sred;
    }
    void showStudent() {
        cout << "id (" << id << ") " << "name = \"" << name << "\" marks = ( ";
        for (auto el : marks) {
            cout << el << ",";
        }
        cout << "\b )";
        cout << " sred ball = " << sredBall();
    }
    string getName() { return name; }
    unsigned int getId() { return id; }
    vector<char> getMarks(){ return marks; }
};
unsigned int Student::idtogive = 1;

class Journal {
    string path = "students.txt";
    string name="No Name";
    vector<Student> students;
public:
    void addstudent(string name) {
        Student newone(name);
        students.push_back(newone);
    }
    void showstudents() {
        cout << endl << name << " students :\n";
        for (auto el : students) {
            el.showStudent();
            cout << endl;
        }
    }
    void savetofile() {
        ofstream out(path);
        out << "name = (" << name << ")";
        for (auto el : students) {
            out << endl;
            out << el.getId() << ";" << el.getName() << ";";
            vector<char> marks = el.getMarks();
            for (auto el : marks)out << el;
        }
        out.close();
    }
    void getfromfile() {
        ifstream in(path);
        if (in.is_open()) {
            string buf;
            getline(in, buf);
            this->name = "";
            {
                int num = 8;
                while (buf[num] != ')') {
                    name += buf[num++];
                }
            }
            while (getline(in, buf)) {
                string newid = "";
                int i = 0;
                while (buf[i] != ';')newid += buf[i++];
                unsigned int id = stoi(newid);
                i++;
                string newname = "";
                while (buf[i] != ';')newname += buf[i++];
                i++;
                vector<char> marks;
                while (buf[i] != '\0')marks.push_back(buf[i++]);
                students.push_back(Student(newname, id, marks));
            }
        }
    }
    void setName(string name) {
        this->name = name;
    }
    int countofstudents() { return students.size(); }
    unsigned int id(int i) {
        return students[i].getId();
    }
    Student* getstudent(int i) {
        return &students[i];
    }
};

int main()
{
    cout << "LOADING";
    Journal thatjournal;
    thatjournal.getfromfile();
    while (1) {
        system("cls");
        int code;
        cout << "input\n1 to show all\n2 to add new student\n3 to give mark to a student\n0 to set your name";
        cin >> code;
        switch (code)
        {
        case 1:
            thatjournal.showstudents();
            system("pause");
            break;
        case 2:
        {
            string name;
            cout << "\n\ninput name of new student : ";
            cin >> name;
            thatjournal.addstudent(name);
            thatjournal.savetofile();
            break;
        }
        case 3:
        {
            thatjournal.showstudents();
            cout << "\n input id of student to give mark : ";
            unsigned int id;
            cin >> id;
            Student* thatstudent = nullptr;
            for (int i = 0; i < thatjournal.countofstudents(); i++) {
                if (id == thatjournal.id(i)) {
                    thatstudent = thatjournal.getstudent(i);
                    break;
                }
            }
            if (thatstudent != nullptr) {
                cout << "\ninput mark(1-5) : ";
                char newmark;
                do {
                    cout << endl;
                    cin >> newmark;
                } while (newmark <= '1' && newmark >= '5');
                thatstudent->addmark(newmark);
                
            }
            else {
                cout << "\n uncorrect id " << endl;
                system("pause");
            }
            break;

                
        }
        case 0:
        {
            string name;
            cout << "\n\ninput your name  : ";
            cin >> name;
            thatjournal.setName(name);
            thatjournal.savetofile();
            break;
        }
        default:
            break;
        }
    }

    
}
