#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
map<pair<char,char>, string> table;

set<char> findFirst(char X) {
    if (!isupper(X)) return {X};
    if (!FIRST[X].empty()) return FIRST[X];

    for (auto prod : grammar[X]) {
        if (prod == "e") FIRST[X].insert('e');
        else {
            for (char c : prod) {
                set<char> temp = findFirst(c);
                for (char t : temp)
                    if (t != 'e') FIRST[X].insert(t);
                if (temp.find('e') == temp.end()) break;
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
                    if (i+1 < prod.size()) {
                        set<char> temp = findFirst(prod[i+1]);
                        for (char t : temp)
                            if (t != 'e') FOLLOW[X].insert(t);
                    } else {
                        FOLLOW[X].insert(FOLLOW[g.first].begin(), FOLLOW[g.first].end());
                    }
                }
            }
        }
    }
}

void buildTable() {
    for (auto g : grammar) {
        char A = g.first;

        for (auto prod : g.second) {
            set<char> firstSet;

            if (prod == "e") firstSet.insert('e');
            else firstSet = findFirst(prod[0]);

            for (char t : firstSet) {
                if (t != 'e')
                    table[{A,t}] = prod;
            }

            if (firstSet.find('e') != firstSet.end()) {
                for (char f : FOLLOW[A])
                    table[{A,f}] = "e";
            }
        }
    }
}

int main() {

    grammar['S'] = {"aXd"};
    grammar['X'] = {"YZ"};
    grammar['Y'] = {"b", "e"};
    grammar['Z'] = {"cX", "e"};

    for (auto g : grammar) findFirst(g.first);
    for (auto g : grammar) findFollow(g.first);

    buildTable();

    cout << "LL(1) Parsing Table:\n";
    for (auto t : table) {
        cout << "M[" << t.first.first << "," << t.first.second << "] = "
             << t.second << endl;
    }

    return 0;
}