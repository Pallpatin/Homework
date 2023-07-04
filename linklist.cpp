
#include <iostream>
using namespace std;

// дополнить созданную в классе структуру list
// реализовать методы :
// clear             +
// insert            +
// push_back         +
// push_front        +
// pop_back          +
// pop_front         +
// empty             +
// size              +
// front             +
// back              +
//
// https ://en.cppreference.com/w/cpp/container/list

template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
    Node* previous = nullptr;
    Node(T data) {
        this->data = data;
    }
};

template<typename T>
class List {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    unsigned int count = 0;
public:
    void push_back(T data) {
        Node <T>* nn = new Node <T>(data);
        if (count == 0) {
            head = nn;
            tail = nn;
        }
        else {
            tail->next = nn;
            nn->previous = tail;
            tail = nn;
        }
        count++;
    }
    void push_front(T data) {
        Node <T>* nn = new Node <T>(data);
        if (count == 0) {
            head = nn;
            tail = nn;
        }
        else {
            head->previous = nn;
            nn->next = head;
            head = nn;
        }
        count++;
    }
    void pop_back() {
        Node<T>* point = tail->previous;
        if (count > 1) {
            delete tail;
            tail = point;
            tail->next = nullptr;
            count--;
        }
        else if (count == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count--;
        }
    }
    void pop_front() {
        Node<T>* point = head->next;
        if (count > 1) {
            delete head;
            head = point;
            head->previous = nullptr;
            count--;
        }
        else if (count == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count--;
        }
    }
    void insert(T data,unsigned int num) {
        Node <T>* nn = new Node <T>(data);
        Node<T>* point = nullptr;
        if (num >= 0 && num <= count) {
            if (num < count / 2) {
                point = head;
                for (int i = 0; i < num; i++) {
                    point = point->next;
                }
            }
            else {
                point = tail;
                for (int i = count; i > count - num; i--)point = point->previous;
            }
            nn->next = point->next;
            nn->previous = point;
            if (point->next != nullptr) point->next->previous = nn;
            point->next = nn;
            count++;
        }
    }
    ~List() {
        Node<T>* point = head;
        while (head!=tail) {
            head = head->next;
            delete point;
            point = head;
            count--;
        }
        delete head;
        count--;
    }
    void show() {
        Node <T>* point = head;
        for (int i = 0; i < count; i++) {
            cout << point->data << "\t";
            point = point->next;
        }
    }
    bool empty() {
        return bool(!count);
    }
    bool size() {
        return count;
    }
    T front() {
        return head->data;
    }
    T back() {
        return tail->data;
    }
    void clear() {
        Node<T>* point = head;
        while (head != tail) {
            head = head->next;
            delete point;
            point = head;
            count--;
        }
        delete head;
        head = nullptr;
        tail = nullptr;
        count--;
    }
    
};

int main()
{

    List<int>* test = new List<int>;
    test->push_back(1);
    test->push_back(2);
    test->push_back(3);
    test->push_back(4);
    test->show();
    cout << endl;
    test->insert(0, 2);
    test->show();

}
