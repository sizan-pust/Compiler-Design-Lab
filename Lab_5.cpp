#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int countLetters(const string &s) {
    int cnt = 0;
    for (unsigned char c : s) if (isalpha(c)) ++cnt;
    return cnt;
}

int main() {
    ifstream file("input.c");
    if (!file) { cerr << "Cannot open input.c\n"; return 1; }

    enum State { NORMAL, IN_STRING, IN_CHAR, IN_SL_COMMENT, IN_ML_COMMENT };
    State state = NORMAL;

    string cur;           // collects current comment text
    int commentNo = 0;
    int totalLetters = 0;
    char ch;

    while (file.get(ch)) {
        if (state == NORMAL) {
            if (ch == '"') state = IN_STRING;
            else if (ch == '\'') state = IN_CHAR;
            else if (ch == '/') {
                int p = file.peek();
                if (p == '/') { file.get(); state = IN_SL_COMMENT; cur.clear(); }
                else if (p == '*') { file.get(); state = IN_ML_COMMENT; cur.clear(); }
                // else it's just a '/' in code -- continue
            }
            // otherwise normal code char (ignored here)
        }
        else if (state == IN_STRING) {
            if (ch == '\\') { char tmp; if (!file.get(tmp)) break; } // skip escaped char
            else if (ch == '"') state = NORMAL;
        }
        else if (state == IN_CHAR) {
            if (ch == '\\') { char tmp; if (!file.get(tmp)) break; } // skip escaped char
            else if (ch == '\'') state = NORMAL;
        }
        else if (state == IN_SL_COMMENT) {
            if (ch == '\n') {
                ++commentNo;
                int letters = countLetters(cur);
                totalLetters += letters;
                cout << "Comment #" << commentNo << " (single-line): letters = " << letters << '\n';
                state = NORMAL;
            } else {
                cur.push_back(ch);
            }
        }
        else if (state == IN_ML_COMMENT) {
            if (ch == '*') {
                int p = file.peek();
                if (p == '/') {
                    file.get(); // consume '/'
                    ++commentNo;
                    int letters = countLetters(cur);
                    totalLetters += letters;
                    cout << "Comment #" << commentNo << " (multi-line): letters = " << letters << '\n';
                    state = NORMAL;
                } else {
                    cur.push_back(ch);
                }
            } else {
                cur.push_back(ch);
            }
        }
    }

    // If file ended while inside a comment, finalize it
    if (state == IN_SL_COMMENT && !cur.empty()) {
        ++commentNo;
        int letters = countLetters(cur);
        totalLetters += letters;
        cout << "Comment #" << commentNo << " (single-line, EOF): letters = " << letters << '\n';
    }
    if (state == IN_ML_COMMENT && !cur.empty()) {
        ++commentNo;
        int letters = countLetters(cur);
        totalLetters += letters;
        cout << "Comment #" << commentNo << " (multi-line, unterminated): letters = " << letters << '\n';
    }

    cout << "Total letters in all comments: " << totalLetters << '\n';
    file.close();
    return 0;
}
