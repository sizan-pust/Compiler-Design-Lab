#include <iostream>
#include <cstring>

using namespace std;

char str[100];
int i = 0, f = 1;

void X();   // function prototype

// A → aXd
void A() {
    if (str[i] == 'a') {
        i++;        // match 'a'
        X();        // call X
        if (str[i] == 'd') {
            i++;    // match 'd'
            f = 1;
        } else {
            f = 0;
        }
    } else {
        f = 0;
    }
}

// X → bbX | bcX | ε
void X() {
    if (str[i] == 'b' && str[i + 1] == 'b') {
        i += 2;     // match "bb"
        X();        // recursive call
    }
    else if (str[i] == 'b' && str[i + 1] == 'c') {
        i += 2;     // match "bc"
        X();        // recursive call
    }
    else {
        // ε (do nothing)
        return;
    }
}

int main() {
    cout << "Enter string: ";
    cin >> str;

    A();

    if (f == 1 && i == strlen(str))
        cout << "String is accepted by the grammar.\n";
    else
        cout << "String is NOT accepted by the grammar.\n";

    return 0;
}
