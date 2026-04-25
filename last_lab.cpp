#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    for (size_t i = 0; i < expr.size(); ) {
        if (isspace((unsigned char)expr[i])) {
            i++;
            continue;
        }

        if (isalnum((unsigned char)expr[i]) || expr[i] == '_') {
            string tok;
            while (i < expr.size() &&
                   (isalnum((unsigned char)expr[i]) || expr[i] == '_')) {
                tok += expr[i++];
            }
            tokens.push_back(tok);
        } else {
            tokens.push_back(string(1, expr[i]));
            i++;
        }
    }
    return tokens;
}

int main() {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    size_t pos = input.find('=');
    if (pos == string::npos) {
        cout << "Invalid input. No '=' found.\n";
        return 0;
    }

    string lhs = input.substr(0, pos);
    string rhs = input.substr(pos + 1);

    // remove spaces from lhs
    string leftVar;
    for (char c : lhs) {
        if (!isspace((unsigned char)c))
            leftVar += c;
    }

    vector<string> tokens = tokenize(rhs);

    // Infix to postfix
    vector<string> postfix;
    stack<string> ops;

    for (string tok : tokens) {
        if (tok == "(") {
            ops.push(tok);
        }
        else if (tok == ")") {
            while (!ops.empty() && ops.top() != "(") {
                postfix.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop(); // remove '('
        }
        else if (isOperator(tok)) {
            while (!ops.empty() && isOperator(ops.top()) &&
                   precedence(ops.top()) >= precedence(tok)) {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push(tok);
        }
        else {
            postfix.push_back(tok);
        }
    }

    while (!ops.empty()) {
        postfix.push_back(ops.top());
        ops.pop();
    }

    // Generate 3-address code from postfix
    stack<string> st;
    int tempCount = 1;

    cout << "\n3-Address Code:\n";

    for (string tok : postfix) {
        if (!isOperator(tok)) {
            st.push(tok);
        } else {
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();

            string temp = "T" + to_string(tempCount++);
            cout << temp << " = " << op1 << " " << tok << " " << op2 << endl;

            st.push(temp);
        }
    }

    if (!st.empty()) {
        cout << leftVar << " = " << st.top() << endl;
    }

    return 0;
}