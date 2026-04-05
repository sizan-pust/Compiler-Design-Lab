// #include <iostream>
// #include <fstream>

// using namespace std;

// int main() {
//     ifstream file("input.c");
//     if (!file) {
//         cout << "File not found\n";
//         return 1;
//     }

//     char ch;
//     bool inString = false;
//     bool inChar = false;
//     bool inSingleComment = false;
//     bool inMultiComment = false;

//     while (file.get(ch)) {

//         // End of single-line comment
//         if (inSingleComment && ch == '\n') {
//             inSingleComment = false;
//         }

//         // End of multi-line comment
//         if (inMultiComment && ch == '*' && file.peek() == '/') {
//             file.get();              // consume '/'
//             inMultiComment = false;
//             continue;
//         }

//         // Inside comment → skip
//         if (inSingleComment || inMultiComment)
//             continue;

//         // Handle string literals
//         if (ch == '"' && !inChar) {
//             inString = !inString;
//             continue;
//         }

//         // Handle character literals
//         if (ch == '\'' && !inString) {
//             inChar = !inChar;
//             continue;
//         }

//         // Ignore comment detection inside strings or chars
//         if (inString || inChar)
//             continue;

//         // Detect comments
//         if (ch == '/') {
//             char next = file.peek();

//             if (next == '/') {
//                 file.get();          // consume second '/'
//                 cout << "Single-line comment found\n";
//                 inSingleComment = true;
//             }
//             else if (next == '*') {
//                 file.get();          // consume '*'
//                 cout << "Multi-line comment found\n";
//                 inMultiComment = true;
//             }
//         }
//     }

//     file.close();
//     return 0;
// }
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream file("input.c");
    if (!file) {
        cout << "File not found\n";
        return 1;
    }

    char ch, next;
    string comment;

    while (file.get(ch)) {
        if (ch == '/') {
            next = file.peek();

            // Single-line comment
            if (next == '/') {
                file.get();   // consume second '/'
                comment = "";

                while (file.get(ch) && ch != '\n') {
                    comment += ch;
                }

                cout << "Single-line comment:" << comment << endl;
            }

            // Multi-line comment
            else if (next == '*') {
                file.get();   // consume '*'
                comment = "";

                while (file.get(ch)) {
                    if (ch == '*' && file.peek() == '/') {
                        file.get(); // consume '/'
                        break;
                    }
                    comment += ch;
                }

                cout << "Multi-line comment:" << comment << endl;
            }
        }
    }

    file.close();
    return 0;
}
