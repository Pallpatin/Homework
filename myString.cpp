
#include <iostream>
#include <string>

using namespace std;

class MyString {
	char* arrayStr = nullptr;
	int size = 0;
	int maxSize = 10;
private:
	int countSymbol(const char array2[]) {
		int counter = 0;
		for (int i = 0; array2[i] != '\0'; i++) {
			counter++;
		}
		return counter;
	}
public:
	MyString() {
		arrayStr = new char[maxSize];
	}
	MyString(const char array2[]) :MyString() {

		operator = (array2);
	}
	MyString(const MyString &str) {
		this->maxSize = str.maxSize;
		this->size = str.size;
		delete[]arrayStr;
		arrayStr = new char[maxSize];
		for (int i = 0; i < size; i++) {
			this->arrayStr[i] = str.arrayStr[i];
		}
	}
	~MyString() {
		//cout << endl << this << " trying to delete";
		if (arrayStr != nullptr) delete[]arrayStr;
		//cout << endl << this << " deleted";
	}
	
	void operator = (const char array2[]) {
		int s2 = countSymbol(array2);
		size = s2;
		if (s2 > maxSize) {
			maxSize = s2;
			delete[]arrayStr;
			arrayStr = new char[maxSize];
		}
		for (int i = 0; i < s2; i++) {
			arrayStr[i] = array2[i];
		}
	}
	void operator +=(const char array2[]) {
		int s2 = countSymbol(array2);
		int newSize = s2 + size;
		if (newSize > maxSize) {
			maxSize = newSize;

		}
		char* buf = new char[maxSize];
		for (int i = 0; i < size; i++) {
			buf[i] = arrayStr[i];
		}
		for (int i = size, k = 0; i < newSize; i++) {
			buf[i] = array2[k++];
		}
		delete[]arrayStr;
		arrayStr = buf;
		size = newSize;

	}
	void operator += (const MyString &str) {
		int sizenew = this->size + str.size;
		char* buf = new char[sizenew];
		if (sizenew > this->maxSize) {
			this->maxSize = sizenew;
		}
		for (int i = 0; i < size; i++)buf[i] = arrayStr[i];
		for (int i = size, k = 0; i < sizenew; i++, k++)buf[i] = str.arrayStr[k];
		this->size = sizenew;
		if (arrayStr != nullptr) {
			delete[]arrayStr;
		}
		arrayStr = buf;
	}
	MyString operator + (const MyString &str) {
		MyString buf(*this);
		buf += str;
		return buf;
	}
	int stoi() {
		int num = 0;
		int index = 0;
		int k = 1;
		if (arrayStr[0] == '-') {
			k = -1;
			index = 1;
		}

		for (int i = index; i < size; i++) {
			num = num * 10 + arrayStr[i] - '0';
		}
		num *= k;
		return num;
	}
	void show() {
		for (int i = 0; i < size; i++) {
			std::cout << arrayStr[i];
		}
	}
	bool operator == (string str) {  //  for tests
		if (str.size() != size)return false;
		for (int i = 0; i < size; i++) {
			if (str[i] != arrayStr[i])return false;
		}
		return true;
	}
	bool operator != (const MyString &str) {
		if (this->maxSize != str.maxSize || this->size != str.size) {
			return true;
		}
		else {
			for (int i = 0; i < size; i++) {
				if (this->arrayStr[i] != str.arrayStr[i])return true;
			}
		}
		return false;
	}
	bool operator > (const MyString& str) {
		int siz = (this->size < str.size ? this->size : str.size);
		for (int i = 0; i < siz; i++) {
			if (this->arrayStr[i] <= str.arrayStr[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator < (const MyString& str) {
		return !(*this > str);
	}
	char operator [] (int i){
		return arrayStr[i];
	}
	bool empty() {
		return !size;
	}
	int getSize() {
		return size;
	}
	void clear() {
		delete[]this->arrayStr;
		arrayStr = new char[maxSize];
		size = 0;
	}
	void push_back(const char& str) {
		char c[2]{ str ,'\0'};
		MyString ar = c;
		operator += (ar);
	}
	void insert(MyString& str, int index) {
		if (index > size || index < 0)return;
		int newsize = this->size + str.size;
		if (newsize > maxSize)maxSize = newsize;
		int place = 0;
		char* buf = new char[maxSize];
		for (int i = 0; i < index; i++, place++) {
			buf[place] = this->arrayStr[i];
		}
		for (int i = 0; i < str.size; i++, place++) {
			buf[place] = str.arrayStr[i];
		}
		for (int i = index; i < size; i++, place++) {
			buf[place] = this->arrayStr[i];
		}
		
		size = newsize;
		//delete[] arrayStr;             // ?????????????????????????????? почему-то при очистке памяти ошибка  !!!!!!!!!!!!!!!!!!!!!!!!!!
		arrayStr = buf;
	}
	void pop() {
		arrayStr[size] = '\0';
		if (size > 0)size--;
	}
};
//constructor           +
//destructor            +
//constructor copy      +
//operator =            +
//operator !=           +
//operator +=           +
//operator +            +
//operator >            +
//operator <            +
//operator >=           +
//operator <=           +
//stoi                  +
//operator[]            +
//empty                 +
//size                  +
//clear                 +
//insert                +
//push                  +
//pop                   +



//template <typename A, typename B>
//void mytest(A &realstr, B &str, string nameoftest) {
//	if (str == realstr) cout << char(251) << "\t" << nameoftest << " passed " << char(251);
//	else cout << char(206) << "\t" << nameoftest << " NOT passed " << char(206);
//	cout << endl;
//}


void mytest(string &realstr, MyString &str, string nameoftest) {
	if (str == realstr) cout << char(251) << "\t" << nameoftest << " passed " << char(251);
	else cout << char(206) << "\t" << nameoftest << " NOT passed " << char(206);
	cout << endl;
}
void mytest(bool realstr, bool str, string nameoftest) {
	if (str == realstr) cout << char(251) << "\t" << nameoftest << " passed " << char(251);
	else cout << char(206) << "\t" << nameoftest << " NOT passed " << char(206);
	cout << endl;
}
void mytest(int realstr, int str, string nameoftest) {
	if (str == realstr) cout << char(251) << "\t" << nameoftest << " passed " << char(251);
	else cout << char(206) << "\t" << nameoftest << " NOT passed " << char(206);
	cout << endl;
}
int main()
{
	MyString str1 = "abc";
	string realstr1 = "abc";
	mytest(realstr1, str1, "mytest");
	MyString str2 = "defg";
	string realstr2 = "defg";
	
	mytest(str1 > str2,realstr1 > realstr2, ">");
	mytest(realstr1 > realstr2, str1 > str2, ">");
	mytest(realstr2 > realstr1, str2 > str1, ">");
	mytest(str1 < str2, realstr1 < realstr2, "<");
	mytest(realstr1 < realstr2, str1 < str2, "<");
	mytest(realstr2 < realstr1, str2 < str1, "<");
	str1 = "50";
	realstr1 = "50";
	mytest(str1.stoi(), stoi(realstr1), "stoi");
	mytest(str1[0], realstr1[0], "[] operator");
	mytest(str1.empty(), realstr1.empty(), "empty");
	mytest(str1.getSize(), realstr1.size(), "size");
	str1.clear();
	realstr1.clear();

	mytest(realstr1, str1, "clear");
	str1.push_back('0');
	realstr1.push_back('0');
	mytest(realstr1, str1, "push_back");
	str1 = "deus";
	realstr1 = "deus";
	str2 = "mae";
	realstr2 = "mae";
	realstr1.insert(1, "mae");
	str1.insert(str2, 1);
	mytest(realstr1, str1, "insert");
	realstr1.pop_back();
	str1.pop();
	mytest(realstr1, str1, "pop");

}
