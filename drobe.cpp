
#include <iostream>
using namespace std;
class Drobe {
private:
    int numerator;
    int denominator;
    void minimize() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        int big=denominator;
        if (numerator > denominator) { big = numerator; }
        big = sqrt(big);
        for (int i = 2; i < big; i++) {
            if (numerator % i == 0 && denominator % i == 0) {
                numerator /= i;
                denominator /= i;
                i--;
            }
        }
    }
public:
    Drobe(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }
    void setNumerator(int num)
    { numerator = num;
    minimize();
    }
    void setDenominator(int den) 
    { denominator = den;
    minimize();
    }
    void Show() {
        cout << numerator << '\\' << denominator;
    }
    Drobe Summ(Drobe fir, Drobe sec) {
        Drobe buf(fir.numerator * sec.denominator + sec.numerator * fir.denominator, sec.denominator * fir.denominator);
        buf.minimize();
        return buf;
    }
    Drobe Minus(Drobe fir, Drobe sec) {
        Drobe buf(fir.numerator * sec.denominator - sec.numerator * fir.denominator, sec.denominator * fir.denominator);
        buf.minimize();
        return buf;
    }
    Drobe Mult(Drobe fir, Drobe sec) {
        Drobe buf(fir.numerator * sec.numerator, fir.denominator * sec.denominator);
        buf.minimize();
        return buf;
    }
    Drobe Divide(Drobe fir, Drobe sec) {
        Drobe buf(fir.numerator * sec.denominator, fir.denominator * sec.numerator);
        buf.minimize();
        return buf;
    }
};



int main()
{
    Drobe one(2, 5);
    Drobe two(5, 2);
    one.Show();
    cout << endl;
    two.Show();
    cout << endl;
    one.setNumerator(50);
    one.Show();
    cout << endl;
    Drobe su =
}
