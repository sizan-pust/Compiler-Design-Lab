// // #include <iostream>
// // #include <list>
// // #include <string>
// // using namespace std;

// // const int TABLE_SIZE = 10;

// // struct Symbol {
// //     string name;
// //     string dataType;
// // };

// // list<Symbol> ST[TABLE_SIZE];

// // int hashFunction(const string& key) {
// //     int sum = 0;
// //     for (char ch : key) {
// //         sum += ch;
// //     }
// //     return sum % TABLE_SIZE;
// // }


// // void insertSymbol(string key, string type) {
// //     int index = hashFunction(key);


// //     for (auto item : ST[index]) {
// //         if (item.name == key) {
// //             cout << key << " already exists.\n";
// //             return;
// //         }
// //     }

// //     ST[index].push_back({key, type});
// //     cout << key << " inserted at index " << index << endl;
// // }


// // void searchSymbol(string key) {
// //     int index = hashFunction(key);

// //     for (auto item : ST[index]) {
// //         if (item.name == key) {
// //             cout << key << " found at index " << index
// //                  << " (Type: " << item.dataType << ")\n";
// //             return;
// //         }
// //     }

// //     cout << key << " not found.\n";
// // }


// // void displayTable() {
// //     cout << "\nSymbol Table:\n";
// //     for (int i = 0; i < TABLE_SIZE; i++) {
// //         cout << i << " -> ";
// //         for (auto item : ST[i]) {
// //             cout << "(" << item.name << ", " << item.dataType << ") ";
// //         }
// //         cout << endl;
// //     }
// // }

// // int main() {

// //     insertSymbol("x", "int");
// //     insertSymbol("y", "float");
// //     insertSymbol("sum", "double");
// //     insertSymbol("count", "int");
// //     insertSymbol("x", "int");

// //     displayTable();

// //     searchSymbol("sum");
// //     searchSymbol("z");

// //     return 0;
// // }
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cctype>

using namespace std;

const int TABLE_SIZE = 101;

// 🔹 Symbol structure
struct Symbol {
    string name, idType, dataType, scope, value;
};

// 🔹 Hash table (chaining)
list<Symbol> symbolTable[TABLE_SIZE];

// 🔹 Hash function (better one)
int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % TABLE_SIZE;
    }
    return hash;
}

// 🔹 INSERT
void insertSymbol(string name, string idType, string dataType, string scope) {
    int index = hashFunction(name);

    for (auto &s : symbolTable[index]) {
        if (s.name == name && s.scope == scope)
            return; // already exists
    }

    symbolTable[index].push_back({name, idType, dataType, scope, ""});
}

// 🔹 SEARCH
Symbol* searchSymbol(string name, string scope) {
    int index = hashFunction(name);

    for (auto &s : symbolTable[index]) {
        if (s.name == name && s.scope == scope)
            return &s;
    }
    return NULL;
}

// 🔹 UPDATE
void updateSymbol(string name, string scope, string value) {
    Symbol* s = searchSymbol(name, scope);
    if (s != NULL) {
        s->value = value;
    }
}

// 🔹 Check datatype
bool isDataType(string s) {
    return s == "int" || s == "float" || s == "double" ||
           s == "char" || s == "void";
}

// 🔹 Check keyword
bool isKeyword(string s) {
    return isDataType(s) || s == "return";
}

// 🔹 Display table
void displayTable() {
    cout << "\nSymbol Table:\n";
    cout << "Name\tIdType\tDataType\tScope\tValue\n";

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (auto s : symbolTable[i]) {
            cout << s.name << "\t"
                 << s.idType << "\t"
                 << s.dataType << "\t\t"
                 << s.scope << "\t"
                 << s.value << endl;
        }
    }
}

// 🔹 MAIN
int main() {
    ifstream file("input.c");
    if (!file) {
        cout << "File not found\n";
        return 1;
    }

    char ch;
    string currentType = "";
    string currentScope = "global";
    string lastIdentifier = "";

    while (file.get(ch)) {

        // Skip spaces
        if (isspace(ch)) continue;
// Skip preprocessor directives (#include, #define, etc.)
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
            file.get();
            char prev = 0;
            while (file.get(ch)) {
                if (prev == '*' && ch == '/') break;
                prev = ch;
            }
            continue;
        }

        // Scope end
        if (ch == '}') {
            currentScope = "global";
            continue;
        }

        // Identifier / Keyword
        if (isalpha(ch) || ch == '_') {
            string lexeme(1, ch);
            while (isalnum(file.peek()) || file.peek() == '_') {
                lexeme += file.get();
            }

            if (isKeyword(lexeme)) {
                if (isDataType(lexeme)) {
                    currentType = lexeme;
                }
            } else {
                lastIdentifier = lexeme;

                if (file.peek() == '(') {
                    insertSymbol(lexeme, "func", currentType, "global");
                    currentScope = lexeme;
                } else {
                    insertSymbol(lexeme, "var", currentType, currentScope);
                }
            }
            continue;
        }

        // Assignment
        if (ch == '=' && file.peek() != '=') {
            string value = "";

            while (isspace(file.peek())) file.get();

            while (isdigit(file.peek()) || file.peek() == '.') {
                value += file.get();
            }

            updateSymbol(lastIdentifier, currentScope, value);
            continue;
        }
    }

    file.close();

    displayTable();

    return 0;
}
