#include <iostream>
#include <map>
#include <stack>
using namespace std;

map<pair<char,char>, string> table;

void parse(string input) {

    stack<char> st;
    st.push('$');
    st.push('S');

    int i = 0;

    cout << "Parsing Steps:\n";

    while (!st.empty()) {
        char top = st.top();
        char current = input[i];

        cout << "Top: " << top << " , Input: " << current << endl;

        if (top == current) {
            st.pop();
            i++;
        }
        else if (!isupper(top)) {
            cout << "Error!\n";
            return;
        }
        else {
            if (table.find({top,current}) == table.end()) {
                cout << "Error!\n";
                return;
            }

            string prod = table[{top,current}];
            st.pop();

            if (prod != "e") {
                for (int j = prod.size()-1; j >= 0; j--)
                    st.push(prod[j]);
            }

            cout << top << " -> " << prod << endl;
        }
    }

    if (input[i] == '$')
        cout << "Accepted ✅\n";
    else
        cout << "Rejected ❌\n";
}

int main() {

    // Hardcoded table
    table[{'S','a'}] = "aXd";

    table[{'X','b'}] = "YZ";
    table[{'X','c'}] = "YZ";
    table[{'X','d'}] = "YZ";

    table[{'Y','b'}] = "b";
    table[{'Y','c'}] = "e";
    table[{'Y','d'}] = "e";

    table[{'Z','c'}] = "cX";
    table[{'Z','d'}] = "e";

    string input = "abcd$";

    parse(input);

    return 0;
}