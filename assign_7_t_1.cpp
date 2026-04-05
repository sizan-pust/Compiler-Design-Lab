#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

bool isKeyword(const string& s) {
    static const set<string> keywords = {
        "float", "double", "int", "char", "void",
        "return", "if", "else", "for", "while", "do",
        "switch", "case", "break", "continue", "struct",
        "union", "typedef", "const", "unsigned", "signed","main",
        "long", "short"
    };
    return keywords.count(s) > 0;
}

void addSymbol(const string& id,
               vector<string>& symbolTable,
               unordered_map<string, int>& pos) {
    if (pos.find(id) == pos.end()) {
        pos[id] = (int)symbolTable.size() + 1;
        symbolTable.push_back(id);
    }
}

int main() {
    ifstream file("input.c");
    if (!file) {
        cout << "File not found\n";
        return 1;
    }

    vector<string> symbolTable;
    unordered_map<string, int> pos;

    char ch;
    while (file.get(ch)) {
        // Skip whitespace
        if (isspace((unsigned char)ch))
            continue;

        // Skip preprocessor lines
        if (ch == '#') {
            while (file.get(ch) && ch != '\n');
            continue;
        }

        // Skip comments
        if (ch == '/' && file.peek() == '/') {
            while (file.get(ch) && ch != '\n');
            continue;
        }
        if (ch == '/' && file.peek() == '*') {
            file.get(); // consume '*'
            char prev = 0;
            while (file.get(ch)) {
                if (prev == '*' && ch == '/')
                    break;
                prev = ch;
            }
            continue;
        }

        // Identifier / Keyword
        if (isalpha((unsigned char)ch) || ch == '_') {
            string lexeme(1, ch);
            while (file.peek() != EOF) {
                char p = (char)file.peek();
                if (isalnum((unsigned char)p) || p == '_') {
                    lexeme += (char)file.get();
                } else {
                    break;
                }
            }

            if (isKeyword(lexeme)) {
                cout << "[" << lexeme << "] ";
            } else {
                cout << "[id " << lexeme << "] ";
                addSymbol(lexeme, symbolTable, pos);
            }
            continue;
        }

        // Number (integer / decimal)
        if (isdigit((unsigned char)ch)) {
            string num(1, ch);
            bool dotSeen = false;

            while (file.peek() != EOF) {
                char p = (char)file.peek();
                if (isdigit((unsigned char)p)) {
                    num += (char)file.get();
                } else if (p == '.' && !dotSeen) {
                    dotSeen = true;
                    num += (char)file.get();
                } else {
                    break;
                }
            }

            cout << "[" << num << "] ";
            continue;
        }

        // Two-character operators
        if ((ch == '=' || ch == '!' || ch == '<' || ch == '>') && file.peek() == '=') {
            string op;
            op += ch;
            op += (char)file.get();
            cout << "[" << op << "] ";
            continue;
        }

        // Single-character operators
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '%') {
            cout << "[" << ch << "] ";
            continue;
        }

        // Separators / punctuation
        if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',' || ch == '[' || ch == ']') {
            cout << "[" << ch << "] ";
            continue;
        }
    }

    cout << "\n\nSymbol Table:\n";
    for (int i = 0; i < (int)symbolTable.size(); i++) {
        cout << i + 1 << " -> " << symbolTable[i] << '\n';
    }

    file.close();
    return 0;
}