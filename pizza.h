#pragma once
// P.S. прочёл где-то, что классы принято писать в заголовочных классах,
// а внутренние методы отдельно только тогда, когда они описаны вне класса :D

#include <iostream>
#include <vector>

using namespace std;

class Pizza {
private:
protected:
    string type[4] = {"Мексиканская", "Азиатская", "Пепперони", "Гавайская"};
// inline убирает предупреждения о неиспользуемых статичных переменных/функций,
// но т.к. в конструкторе я всё же объявляю вектор, мне бояться нечего
// с помощью static я увеличиваю продолжительность жизни вектора, чтобы мой перегруженный оператор вывода видел его
    inline static vector<string> description; //описание пиццы
    int size[4] = {25, 30, 35, 40};

public:

    //заполнение вектора
    Pizza() {
        description.emplace_back("Ароматная грудинка, обжаренная с помидорами черри, "
                                 "\nболгарским перцем, репчатым луком и пикантным соусом, "
                                 "\nзапекается на вкуснейшей пышной лепешке под слоем ароматного "
                                 "\nсыра моцарелла."); //Мексиканская
        description.emplace_back("Нежнейшая креветка с сочными цукини и репчатым луком, "
                                 "\nзаправленные белым соусом и сладким соусом чили, "
                                 "\nзапекаются под сыром моцарелла, а семена кунжута на краю лепешки "
                                 "\nпридают изысканный вкус."); //Азиатская
        description.emplace_back("Колбаса пепперони в сочетании с оригинальным красным соусом "
                                 "\nне оставит равнодушными тех, кто любит погорячее."); //Пепперони
        description.emplace_back("Аппетитная ветчина с сочными кусочками ананаса, "
                                 "\nзапечённая под сыром моцарелла, придаёт этой "
                                 "\nпицце экзотический вкус."); //Гавайская
    }

    ~Pizza() = default;
};

//абстрактный класс
class Order : public Pizza {
private:
    //На Linux/Unix выделение может не работать, там используются "[1m" и "[0m"
    static std::ostream &bold_on(std::ostream &os) {
        return os << "\e[1m";
    }

    static std::ostream &bold_off(std::ostream &os) {
        return os << "\e[0m";
    }

    void makeCost() {
        int first_cost = typeCost[set.type - 1];
        auto size_per_cent = (float) ((float) set.size / (float) size[0]);

        //магичиская формула вычисления общей стоимости пиццы
        set.cost = ((size_per_cent * (float) first_cost) + (float) (set.salt * 5) + (float) (set.cheese * 10));///10;

    }

protected:

    int typeCost[4] = {405, 380, 405, 295};
    struct Settings {
        int type;
        int salt = 0;
        int cheese = 0;
        int size;
        string costylType[4] = {"Мексиканская", "Азиатская", "Пепперони", "Гавайская"};
        float cost;
    };

    Settings set;
public:

    Order() = default;

    static void welcome() {
        cout << bold_on << "Добро пожаловать в Пиццерию 'У Егорика'!" << bold_off << endl;

        cout << "\nВ нашем ассортименте имеется 4 вида пиццы. "
                "\nУ каждой пиццы вы можете выбрать размер. По желанию подсолить N раз и добавить сыра M раз.\n"
             << endl;
        cout << "Введите '1', чтобы приступить к составлению заказа!" << endl;
    }

    void menu() {
        for (int i = 0; i < 4; ++i) {
            cout << bold_on << i + 1 << ") " << type[i] << bold_off << '\n' << description[i]
                 << '\n';
        }
        cout << endl;
    }

    virtual void enterOrder() {
        unsigned int enter = 0;
        bool check = false;
        do {
            cin >> enter;
        } while (enter != 1);
        enter = 0;

        cout << "Приступим к составлению заказа. Сейчас я покажу вам все наши пиццы с кратким описанием:\n";
        newOrder(enter, check);

    }

    void newOrder(unsigned int enter, bool check) {
        menu();
        cout << "Чтобы выбрать пиццу, введите её порядковый номер: " << endl;

        do {
            if (check)
                cout << "Вы ввели некоректный номер, повторите попытку: " << endl;
            cin >> enter;
            check = true;
        } while ((enter != 1) && (enter != 2) && (enter != 3) && (enter != 4));

        set.type = enter;
        check = false;
        enter = 0;

        cout << "Выберите один из 4-х размеров пиццы - 25, 30, 35, 40:" << endl;
        do {
            if (check)
                cout << "Вы ввели некоректный размер, повторите попытку: " << endl;
            cin >> enter;
            check = true;
        } while ((enter != 25) && (enter != 30) && (enter != 35) && (enter != 40));

        set.size = enter;
        enter = 0;
        check = false;

        char new_enter;
        cout << "Хотите ли вы посоль пиццу? (+,-): " << endl;
        do {
            if (check)
                cout << "Вы ввели некоректный символ, повторите попытку: " << endl;
            cin >> new_enter;
            check = true;
        } while ((new_enter != '+') && (new_enter != '-'));

        check = false;
        if (new_enter == '+') {
            cout << "Сколько раз посолить вашу пиццу? Подсолить можно максимум 100 раз" << endl;
            do {
                if (check)
                    cout << "Вы ввели некорректное число раз, повторите попытку: " << endl;
                cin >> enter;
                check = true;
            } while ((enter < 1) || (enter > 100));
        }

        set.salt = enter;
        enter = 0;
        check = false;

        cout << "Хотите ли вы добавить сыра в пиццу? (+,-): " << endl;
        do {
            if (check)
                cout << "Вы ввели некоректный символ, повторите попытку: " << endl;
            cin >> new_enter;
            check = true;
        } while ((new_enter != '+') && (new_enter != '-'));

        check = false;
        if (new_enter == '+') {
            cout << "Сколько добавить сыра в вашу пиццу? Добавить сыра можно максимум 100 раз" << endl;
            do {
                if (check)
                    cout << "Вы ввели число, повторите попытку: " << endl;
                cin >> enter;
                check = true;
            } while ((enter < 1) || (enter > 100));;
        }

        set.cheese = enter;
        enter = 0;
        check = false;

        makeCost();
    }

    //Чисто виртуальная функция
    virtual void defaultOrder() = 0;

};

class Orders : public Order {
private:
    inline static Settings *sett;
    int sizeSett = 0;
    inline static float all_sum = 0;

    static string getDescription() {
        string str = description[sett[0].type - 1];
        return str;
    }

    //Overriding
    //добавление новой пиццы в заказ
    void defaultOrder() override {
        int enter = 0;
        bool check = false;

        cout << "1) Добавить ещё одну пиццу в заказ\n2) Распечатать чек" << endl;
        do {
            if (check) {
                cout << "Вы ввели некоректное число, повторите попытку: " << endl;
            }
            cin >> enter;
            check = true;
        } while ((enter != 1) && (enter != 2));

        check = false;

        if (enter == 1) {
            newOrder(enter, check);
            defaultOrder();
            sizeSett++;
            Settings *help_sett = sett;
            sett = new Settings[sizeSett];
            for (int i = 0; i < sizeSett - 1; ++i) {
                sett[i] = help_sett[i];
            }
            sett[sizeSett - 1] = set;
            all_sum += sett[sizeSett - 1].cost;
        }
    }

protected:
public:

    Orders() {
        sett = new Settings[1];
    }

    //Oveloading operator<< для класса
    friend ostream &operator<<(std::ostream &out, const Orders &ord) {
        out << "------------------ЧЕК------------------" << endl;
        for (int i = 0; i < ord.sizeSett; ++i) {
            out << ord.sett[i].costylType[ord.sett[i].type - 1] << '\n' << getDescription() << '\n'
                << "\nразмер - " << ord.sett->size <<
                "\nколичество соли - " << ord.sett[i].salt << "\nколичество сыра - "
                << ord.sett[i].cheese << "\n" << ord.sett[i].cost << "p" << endl;
            if (i != ord.sizeSett - 1)
                out << "--------------------------------" << endl;
        }
        out << "=====================================" << endl;
        out << "Вся сумма заказа составила: " << all_sum << 'p' << endl;
        return out;
    }

    //Overriding
    //добавление первой пиццы в заказ
    void enterOrder() {
        welcome();
        Order::enterOrder();
        sett[0] = set;
        sizeSett++;
        all_sum = sett[0].cost;
        defaultOrder();
    }

    ~Orders() {
        delete[] sett;
    };
};
