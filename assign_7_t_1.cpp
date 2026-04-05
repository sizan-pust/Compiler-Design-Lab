// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <set>
// #include <cctype>

// using namespace std;

// bool isKeyword(const string& s) {
//     static const set<string> keywords = {
//         "float", "double", "int", "char", "void",
//         "return", "if", "else", "for", "while", "do",
//         "switch", "case", "break", "continue", "struct",
//         "union", "typedef", "const", "unsigned", "signed","main",
//         "long", "short"
//     };
//     return keywords.count(s) > 0;
// }

// struct Symbol {
//     int sl;
//     string name, idType, dataType, scope, value;
// };

// vector<Symbol> symbolTable;
// int counter = 1;

// void addSymbol(string name, string idType, string dataType, string scope, string value="") {
//     for (auto &s : symbolTable) {
//         if (s.name == name && s.scope == scope)
//             return;
//     }
//     symbolTable.push_back({counter++, name, idType, dataType, scope, value});
// }

// int main() {
//     ifstream file("input.c");
//     if (!file) {
//         cout << "File not found\n";
//         return 1;
//     }

//     string currentType = "";
//     string currentScope = "global";

//     char ch;
//     while (file.get(ch)) {
//         // Skip whitespace
//         if (isspace((unsigned char)ch))
//             continue;

//         // Skip preprocessor lines
//         if (ch == '#') {
//             while (file.get(ch) && ch != '\n');
//             continue;
//         }

//         // Skip comments
//         if (ch == '/' && file.peek() == '/') {
//             while (file.get(ch) && ch != '\n');
//             continue;
//         }
//         if (ch == '/' && file.peek() == '*') {
//             file.get(); // consume '*'
//             char prev = 0;
//             while (file.get(ch)) {
//                 if (prev == '*' && ch == '/')
//                     break;
//                 prev = ch;
//             }
//             continue;
//         }
//         if (ch == '=') {
//             string value = "";

//             // skip whitespace after '='
//             while (true) {
//                 int ip = file.peek();
//                 if (ip == EOF) break;
//                 char p = (char)ip;
//                 if (isspace((unsigned char)p)) { file.get(); continue; }
//                 break;
//             }

//             // optional sign
//             if (file.peek() != EOF) {
//                 int ip = file.peek();
//                 char p = (char)ip;
//                 if (p == '+' || p == '-') value += (char)file.get();
//             }

//             bool dotSeen = false;
//             // read number (integer or decimal)
//             while (true) {
//                 int ip = file.peek();
//                 if (ip == EOF) break;
//                 char p = (char)ip;
//                 if (isdigit((unsigned char)p)) {
//                     value += (char)file.get();
//                 } else if (p == '.' && !dotSeen) {
//                     dotSeen = true;
//                     value += (char)file.get();
//                 } else break;
//             }

//             // assign value to last variable (if we actually read one)
//             if (!value.empty() && !symbolTable.empty()) {
//                 symbolTable.back().value = value;
//             }

//             continue;
//         }

//         // Identifier / Keyword
//         if (isalpha((unsigned char)ch) || ch == '_') {
//             string lexeme(1, ch);
//             while (file.peek() != EOF) {
//                 char p = (char)file.peek();
//                 if (isalnum((unsigned char)p) || p == '_') {
//                     lexeme += (char)file.get();
//                 } else {
//                     break;
//                 }
//             }
//             if (ch == '}') {
//     currentScope = "global";
// }

//             if (isKeyword(lexeme)) {
//     cout << "[" << lexeme << "] ";

//     // store datatype
//     if (lexeme == "int" || lexeme == "float" || lexeme == "double" || lexeme == "char" || lexeme == "void") {
//         currentType = lexeme;
//     }
// }
// else {
//     cout << "[id " << lexeme << "] ";

//     // Check if function
//     if (file.peek() == '(') {
//         addSymbol(lexeme, "func", currentType, "global");
//         currentScope = lexeme;
//     }
//     else {
//         addSymbol(lexeme, "var", currentType, currentScope);
//     }
// }
//             continue;
//         }

//         // Number (integer / decimal)
//         if (isdigit((unsigned char)ch)) {
//             string num(1, ch);
//             bool dotSeen = false;

//             while (file.peek() != EOF) {
//                 char p = (char)file.peek();
//                 if (isdigit((unsigned char)p)) {
//                     num += (char)file.get();
//                 } else if (p == '.' && !dotSeen) {
//                     dotSeen = true;
//                     num += (char)file.get();
//                 } else {
//                     break;
//                 }
//             }

//             cout << "[" << num << "] ";
//             continue;
//         }

//         // Two-character operators
//         if ((ch == '=' || ch == '!' || ch == '<' || ch == '>') && file.peek() == '=') {
//             string op;
//             op += ch;
//             op += (char)file.get();
//             cout << "[" << op << "] ";
//             continue;
//         }

//         // Single-character operators
//         if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '%') {
//             cout << "[" << ch << "] ";
//             continue;
//         }

//         // Separators / punctuation
//         if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',' || ch == '[' || ch == ']') {
//             cout << "[" << ch << "] ";
//             continue;
//         }
//     }

//    cout << "\n\nSymbol Table:\n";
// cout << "Sl.No\tName\tId Type\tData Type\tScope\tValue\n";

// for (auto &s : symbolTable) {
//     cout << s.sl << "\t"
//          << s.name << "\t"
//          << s.idType << "\t"
//          << s.dataType << "\t\t"
//          << s.scope << "\t"
//          << s.value << endl;
// }

//     file.close();
//     return 0;
// }
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

// Checks if a string is a C keyword
bool isKeyword(const string& s) {
    static const set<string> keywords = {
        "float", "double", "int", "char", "void", "return", "if", "else", 
        "for", "while", "do", "switch", "case", "break", "continue", 
        "struct", "union", "typedef", "const", "unsigned", "signed", 
        "main", "long", "short"
    };
    return keywords.count(s) > 0;
}

// Symbol Table Structure
struct Symbol {
    int sl;
    string name, idType, dataType, scope, value;
};

vector<Symbol> symbolTable;
int counter = 1;

// Adds a symbol to the table if it doesn't already exist in the current scope
void addSymbol(string name, string idType, string dataType, string scope, string value="") {
    for (auto &s : symbolTable) {
        if (s.name == name && s.scope == scope) return;
    }
    symbolTable.push_back({counter++, name, idType, dataType, scope, value});
}

int main() {
    ifstream file("input.c");
    if (!file) {
        cout << "File not found\n";
        return 1;
    }

    string currentType = "";
    string currentScope = "global";
    char ch;

    while (file.get(ch)) {
        // 1. Skip Whitespace
        if (isspace(ch)) continue;

        // 2. Skip Preprocessor Directives (#)
        if (ch == '#') {
            while (file.get(ch) && ch != '\n');
            continue;
        }

        // 3. Skip Comments (// and /* */)
        if (ch == '/') {
            if (file.peek() == '/') {
                while (file.get(ch) && ch != '\n');
                continue;
            } else if (file.peek() == '*') {
                file.get(); // consume '*'
                char prev = 0;
                while (file.get(ch)) {
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
                continue;
            }
        }

        // 4. Handle Scope Exit ('}')
        if (ch == '}') {
            currentScope = "global";
            cout << "[}] ";
            continue;
        }

        // 5. Handle Value Assignment (=)
        if (ch == '=' && file.peek() != '=') {
            string value = "";
            
            // Skip spaces after '='
            while (isspace(file.peek())) file.get();

            // Check for optional sign (+ or -)
            if (file.peek() == '+' || file.peek() == '-') {
                value += (char)file.get();
            }

            // Read numeric value
            bool dotSeen = false;
            while (isdigit(file.peek()) || (file.peek() == '.' && !dotSeen)) {
                if (file.peek() == '.') dotSeen = true;
                value += (char)file.get();
            }

            // Assign value to the last added variable in the symbol table
            if (!value.empty() && !symbolTable.empty()) {
                symbolTable.back().value = value;
            } else {
                cout << "[=] "; // Just print the operator if no value follows
            }
            continue; 
        }

        // 6. Handle Identifiers and Keywords
        if (isalpha(ch) || ch == '_') {
            string lexeme(1, ch);
            while (isalnum(file.peek()) || file.peek() == '_') {
                lexeme += (char)file.get();
            }

            if (isKeyword(lexeme)) {
                cout << "[" << lexeme << "] ";
                // Update current datatype context
                if (lexeme == "int" || lexeme == "float" || lexeme == "double" || 
                    lexeme == "char" || lexeme == "void") {
                    currentType = lexeme;
                }
            } else {
                cout << "[id " << lexeme << "] ";
                // Check if it's a function by looking for '('
                if (file.peek() == '(') {
                    addSymbol(lexeme, "func", currentType, "global");
                    currentScope = lexeme;
                } else {
                    addSymbol(lexeme, "var", currentType, currentScope);
                }
            }
            continue;
        }

        // 7. Handle Standalone Numbers
        if (isdigit(ch)) {
            string num(1, ch);
            bool dotSeen = false;
            while (isdigit(file.peek()) || (file.peek() == '.' && !dotSeen)) {
                if (file.peek() == '.') dotSeen = true;
                num += (char)file.get();
            }
            cout << "[" << num << "] ";
            continue;
        }

        // 8. Handle Two-Character Operators (==, !=, <=, >=)
        if ((ch == '=' || ch == '!' || ch == '<' || ch == '>') && file.peek() == '=') {
            cout << "[" << ch << (char)file.get() << "] ";
            continue;
        }

        // 9. Handle Single-Character Operators and Separators
        string symbols = "+-*/%<>()[]{};,";
        if (symbols.find(ch) != string::npos) {
            cout << "[" << ch << "] ";
            continue;
        }
    }

    // 10. Print the Final Symbol Table
    cout << "\n\nSymbol Table:\n";
    cout << "Sl.No\tName\tId Type\tData Type\tScope\tValue\n";

    for (auto &s : symbolTable) {
        cout << s.sl << "\t"
             << s.name << "\t"
             << s.idType << "\t"
             << s.dataType << "\t\t"
             << s.scope << "\t"
             << s.value << "\n";
    }

    file.close();
    return 0;
}