#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

bool isKeyword(const char str[]) {
    const char keywords[][100] = {
        "int", "float", "char", "double",
        "if", "else", "for", "while",
        "return", "void", "switch", "case",
        "break", "continue", "do", "static",
        "struct", "union", "typedef", "const",
        "unsigned", "signed", "long", "short", "main",
    };

    for (int i = 0; i < 101; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}

bool isIdentifier(const char str[]) {
    if (!(isalpha(str[0]) || str[0] == '_'))
        return false;

    for (int i = 1; str[i] != '\0'; i++) {
        if (!(isalnum(str[i]) || str[i] == '_'))
            return false;
    }
    return true;
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

        // Ignore preprocessor directives
        if (ch == '#') {
            while (file.get(ch) && ch != '\n');
            continue;
        }

        // Handle comments
        if (ch == '/') {
            char next;
            file.get(next);

            // Single-line comment
            if (next == '/') {
                while (file.get(ch) && ch != '\n');
                continue;
            }
            // Multi-line comment
            else if (next == '*') {
                char prev;
                while (file.get(prev) && file.get(ch)) {
                    if (prev == '*' && ch == '/')
                        break;
                }
                continue;
            }
            else {
                file.unget();
            }
        }

        // Collect identifiers
        if (isalnum(ch) || ch == '_') {
            buffer[i++] = ch;
        } else {
            buffer[i] = '\0';

            if (strlen(buffer) > 0 &&
                isIdentifier(buffer) &&
                !isKeyword(buffer)) {

                cout << "Identifier: " << buffer << endl;
            }
            i = 0;
        }
    }

    file.close();
    return 0;
}
