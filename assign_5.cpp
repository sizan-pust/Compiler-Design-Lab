#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> tokens;
int i = 0;

// Utility
bool match(string t) {
    if (i < tokens.size() && tokens[i] == t) {
        i++;
        return true;
    }
    return false;
}

bool isID() {
    if (i < tokens.size() && tokens[i] == "id") {
        i++;
        return true;
    }
    return false;
}

bool isRelop() {
    string r[] = {"==", "!=", "<=", ">=", "<", ">"};
    for (string op : r) {
        if (i < tokens.size() && tokens[i] == op) {
            i++;
            return true;
        }
    }
    return false;
}

// Grammar functions
bool stat();
bool asgn_stat();
bool expn();
bool extn();
bool dcsn_stat();
bool extn1();
bool loop_stat();
bool smpl_expn();

// <stat>
bool stat() {
    int save = i;
    if (asgn_stat()) return true;
    i = save;
    if (dcsn_stat()) return true;
    i = save;
    if (loop_stat()) return true;
    return false;
}

// <asgn_stat> → id = <expn>
bool asgn_stat() {
    int save = i;
    if (isID() && match("=") && expn())
        return true;
    i = save;
    return false;
}

// <expn> → <smpl_expn> <extn>
bool expn() {
    if (smpl_expn())
        return extn();
    return false;
}

// <extn> → <relop> <smpl_expn> | ε
bool extn() {
    int save = i;
    if (isRelop() && smpl_expn())
        return true;
    i = save;
    return true; // ε
}

// <smpl_expn> → id | num
bool smpl_expn() {
    if (isID()) return true;
    if (i < tokens.size() && tokens[i] == "num") {
        i++;
        return true;
    }
    return false;
}

// <dcsn_stat>
bool dcsn_stat() {
    int save = i;
    if (match("if") && match("(") && expn() && match(")") && stat() && extn1())
        return true;
    i = save;
    return false;
}

// <extn1> → else <stat> | ε
bool extn1() {
    int save = i;
    if (match("else") && stat())
        return true;
    i = save;
    return true; // ε
}

// <loop_stat>
bool loop_stat() {
    int save = i;

    // while loop
    if (match("while") && match("(") && expn() && match(")") && stat())
        return true;

    i = save;

    // for loop
    if (match("for") && match("(") && asgn_stat() && match(";") &&
        expn() && match(";") && asgn_stat() &&
        match(")") && stat())
        return true;

    i = save;
    return false;
}

int main() {
    cout << "Enter tokens (space separated, end with #):\n";

    string t;
    while (cin >> t && t != "#")
        tokens.push_back(t);

    if (stat() && i == tokens.size())
        cout << "Syntax is VALID\n";
    else
        cout << "Syntax is INVALID\n";

    return 0;
}
