#include <iostream>
#include "pizza.h"

using namespace std;

/*
 * В рамках выполнения задания необходимо
 * продемонстрировать умение использовать
 * Ad-hoc полиморфизм: overloading/overriding
 */

int main() {
    Orders o;
    o.enterOrder();
    cout << o;
    return 0;
}
