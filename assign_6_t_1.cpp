#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;

set<char> findFirst(char X) {
    if (!isupper(X)) return {X};

    if (!FIRST[X].empty()) return FIRST[X];

    for (auto prod : grammar[X]) {
        if (prod == "e") {
            FIRST[X].insert('e');
        } else {
            for (char c : prod) {
                set<char> temp = findFirst(c);
                for (char t : temp) {
                    if (t != 'e') FIRST[X].insert(t);
                }
                if (temp.find('e') == temp.end())
                    break;
            }
        }
    }
    return FIRST[X];
}

void findFollow(char X) {
    if (X == 'S') FOLLOW[X].insert('$');

    for (auto g : grammar) {
        for (auto prod : g.second) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == X) {
                    if (i + 1 < prod.size()) {
                        set<char> temp = findFirst(prod[i+1]);
                        for (char t : temp) {
                            if (t != 'e') FOLLOW[X].insert(t);
                        }
                        if (temp.find('e') != temp.end())
                            FOLLOW[X].insert(FOLLOW[g.first].begin(), FOLLOW[g.first].end());
                    } else {
                        if (X != g.first)
                            FOLLOW[X].insert(FOLLOW[g.first].begin(), FOLLOW[g.first].end());
                    }
                }
            }
        }
    }
}

int main() {

    grammar['S'] = {"aXd"};
    grammar['X'] = {"YZ"};
    grammar['Y'] = {"b", "e"};
    grammar['Z'] = {"cX", "e"};

    
    for (auto g : grammar)
        findFirst(g.first);

    cout << "FIRST Sets:\n";
    for (auto f : FIRST) {
        cout << f.first << " = { ";
        for (char c : f.second) cout << c << " ";
        cout << "}\n";
    }

    
    for (auto g : grammar)
        findFollow(g.first);

    cout << "\nFOLLOW Sets:\n";
    for (auto f : FOLLOW) {
        cout << f.first << " = { ";
        for (char c : f.second) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}