
#include <iostream>
#include <stack> //для очереди монстров-легковесов
#include <windows.h> //для симмуляции битвы (sleep())

#define random(a,b) (a+rand()%(b-a+1))
using namespace std;
// легковес реализует монстров

const float lvlupK = 5; // коэффициент при поднятии уровня


class Monster {
protected:
    string name;
    int damadge;
    unsigned int MaxHp;
    float fast;
public:
    int getDamadge() { return damadge; }
    unsigned int getMaxHp() {
        return MaxHp;
    }
    float getFast() {
        return fast;
    }
    virtual void appear() = 0;
    virtual int deathAction() = 0;
    string getname() {
        return name;
    }


};

class Slime :public Monster {
public:
    Slime() {
        this->MaxHp = 10;
        this->fast = 2.6;
        this->damadge = 10;
        this->name = "Slime";
    }
    void appear() {
        cout << endl << "slime appeared";
    }
    int deathAction() {
        cout << endl << "slime defeated";
        return 150;
    }
};

class Goblin :public Monster {
public:
    Goblin() {
        this->MaxHp = 30;
        this->fast = 1;
        this->damadge = 20;
        this->name = "Goblin";
    }
    void appear() {
        cout << endl << "Goblin appeared";
    }
    int deathAction() {
        cout << endl << "Goblin defeated";
        return 300;
    }
};

class Spider :public Monster {
public:
    Spider() {
        this->MaxHp = 50;
        this->fast = 0.5;
        this->damadge = 30;
        this->name = "Spider";
    }
    void appear() {
        cout << endl << "Spider appeared";
    }
    int deathAction() {
        cout << endl << "Spider defeated";
        return 700;
    }
};

class Flyweightmonster {                             // легковес
    Monster* monsterTemplate = nullptr;
public:
    float currentHP;
    float getFast() {
        return monsterTemplate->getFast();
    }
    Flyweightmonster(Monster* typeofmonster) {
        monsterTemplate = typeofmonster;
        currentHP = monsterTemplate->getMaxHp();
    }
    int death() {
        return monsterTemplate->deathAction();
    }
    int getDamadge() { return monsterTemplate->getDamadge(); }
    string getName() { return monsterTemplate->getname(); }
};

class Hero {
    string name;
    unsigned int MaxHp;
    int CurrentHp;
    unsigned int ExpearenceTonextLevel;
    unsigned int TotalExpearence=0;
    float fast;
    int damadge;
    int level;
    bool dead = 0;
public:
    void trainhard() {
        int i = 0;
        while (!levelup()) {
            Sleep(100);
            TotalExpearence += 10 + (level * CurrentHp / 10) + i++;
            cout << "you train hard " << i << " time\n";
        }
    }
    void heal() {
        while (CurrentHp < MaxHp) {
            Sleep(100);
            CurrentHp += 1 + level;
            cout << "you heal yourselve " << 1 + level << " restored\n";
        }
        CurrentHp = MaxHp;
    }
    
    int getCurrentHp() {
        return CurrentHp;
    }
    bool isDead() {
        return dead;
    }
    Hero(string name) {
        this->name = name;
        MaxHp = 100;
        CurrentHp = 50;
        fast = 2;
        damadge = 10;
        level = 0;
        ExpearenceTonextLevel = 100;
    }
    void Fight(Flyweightmonster beast) {
        int monstertime = beast.getFast() * 1000;
        int herotime = fast * 1000;
        while (1) {
            Sleep(100);
            monstertime -= 100;
            herotime -= 100;
            if (herotime <= 0) {
                herotime = fast * 1000;
                beast.currentHP -= damadge;
                cout << "you hit the monster " << beast.getName() << " takes " << damadge << " damadge" << " and has " << beast.currentHP << "total HP";
                if (beast.currentHP <= 0) {
                    TotalExpearence += beast.death();
                    break;
                }
            }
            if (monstertime <= 0) {
                monstertime = beast.getFast() * 1000;
                CurrentHp -= beast.getDamadge();
                cout << beast.getName() << " hit you and deal " << beast.getDamadge() << " damadge. You have " << CurrentHp << " left.\n";
                if (CurrentHp <= 0) {
                    system("cls");
                    cout << "\n Your journey it began because \n YOU DIED\n";
                    dead = 1;
                    break;
                }
            }
        }
        levelup();
    }
    bool levelup(){
        if (TotalExpearence >= ExpearenceTonextLevel) {
            TotalExpearence -= ExpearenceTonextLevel;
            ExpearenceTonextLevel *= 1.1;
            level++;
            MaxHp *= 1 + (lvlupK / 100);
            CurrentHp += (MaxHp - CurrentHp) / 2;
            fast *= (1 - lvlupK / 100);
            damadge += lvlupK;
            cout << "\n\nLVL UP !!!\ncurrent lvl is " << level << endl;
            levelup();
            return 1;
        }
        else return 0;
    }
};

Flyweightmonster monstergen(Monster* masterMonster1, Monster* masterMonster2, Monster* masterMonster3) {
    int randomed = random(0, 100);
    if (randomed < 45) return Flyweightmonster(masterMonster1);
    else if (randomed < 80) return Flyweightmonster(masterMonster2);
    else return Flyweightmonster(masterMonster3);
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "");
    cout << "Введите имя героя\n";
    string name;
    cin >> name;
    Hero gamehero(name);

    // создание шаблонов монстров
    Monster* masterSlime = new Slime;
    Monster* masterGoblin = new Goblin;
    Monster* masterSpider = new Spider;

    int CountOfMonstersGenerated = 100;
    stack <Flyweightmonster> AllMonsters;
    for (int i = 0; i < CountOfMonstersGenerated; i++) {
        AllMonsters.push(monstergen(masterSlime, masterGoblin, masterSpider));
    }
    int desizion=1;
    while (!AllMonsters.empty()) {
        cout << "\n\ndeside what to do\n you have " << gamehero.getCurrentHp() << "HP"<<" \n\t 1-to fight\n\t 2-to heal\n\t 3-to train\n";
        do
        {
            //cin >> desizion;
        } while (desizion <= 0 && desizion >= 4);
        switch (desizion) {
        case 1:
            {
                gamehero.Fight(AllMonsters.top());
                if (gamehero.isDead())break;
                AllMonsters.pop();
                Sleep(100);
            }
            break;
        case 2:
        {
            gamehero.heal();
        }
        break;
        case 3:
            gamehero.trainhard();
            break;
        }
        if (gamehero.isDead())break;
    }
    if (AllMonsters.empty()) {
        cout << "You win \n";
     }
    cout << "game over";
}
