#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

bool isConstant(const char str[]) {
    int dot = 0, digit = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]))
            digit++;
        else if (str[i] == '.')
            dot++;
        else
            return false;
    }

    if (digit >= 1 && dot <= 1)
        return true;

    return false;
}

int main() {
    ifstream file("input.c");
    char ch, buffer[50];
    int i = 0;

    if (!file) {
        cout << "File not found" << endl;
        return 1;
    }

    while (file.get(ch)) {
        if (isdigit(ch) || ch == '.') {
            buffer[i++] = ch;
        } else {
            buffer[i] = '\0';

            if (strlen(buffer) > 0 && isConstant(buffer)) {
                cout << "Constant: " << buffer << endl;
            }
            i = 0;
        }
    }

    file.close();
    return 0;
}
