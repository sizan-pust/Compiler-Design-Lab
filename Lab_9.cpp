#include <iostream>
#include <cstring>

using namespace std;

char str[100];
int i = 0;
int len;

bool X();   // forward declaration
bool A();

bool A() {
    // A → a X d
    if (i < len && str[i] == 'a') {
        i++;                // match 'a'
        if (X()) {
            if (i < len && str[i] == 'd') {
                i++;        // match 'd'
                return true;
            }
        }
    }
    return false;
}

bool X() {
    // X → bbX | bcX | ε

    // bbX
    if (i + 1 < len && str[i] == 'b' && str[i + 1] == 'b') {
        i += 2;
        return X();
    }

    // bcX
    if (i + 1 < len && str[i] == 'b' && str[i + 1] == 'c') {
        i += 2;
        return X();
    }

    // ε (epsilon)
    return true;
}

int main() {
    cout << "Enter string: ";
    cin >> str;

    len = strlen(str);
    i = 0;

    if (A() && i == len)
        cout << "String is ACCEPTED" << endl;
    else
        cout << "String is REJECTED" << endl;

    return 0;
}
