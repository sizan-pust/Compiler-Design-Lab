// #include <iostream>
// #include <fstream>
// #include <string>

// using namespace std;

// int main() {
//     ifstream file("input.c");
//     string line;
//     int lineNo = 0;
//     bool inMultiLine = false;

//     if (!file) {
//         cout << "File not found" << endl;
//         return 1;
//     }

//     while (getline(file, line)) {
//         lineNo++;

//         // Check single-line comment
//         if (line.find("//") != string::npos) {
//             cout << "Comment found at line: " << lineNo << endl;
//         }

//         // Check multi-line comment start
//         if (line.find("/*") != string::npos) {
//             cout << "Comment found at line: " << lineNo << endl;
//             inMultiLine = true;
//         }

//         // Check multi-line comment end
//         if (inMultiLine && line.find("*/") != string::npos) {
//             inMultiLine = false;
//         }
//     }

//     file.close();
//     return 0;
// }
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream file("input.c");
    string line;
    int lineNo = 0;
    bool inMultiLine = false;
    int startLine = 0;

    if (!file) {
        cout << "File not found" << endl;
        return 1;
    }

    while (getline(file, line)) {
        lineNo++;

        // Single-line comment
        if (!inMultiLine && line.find("//") != string::npos) {
            cout << "Comment found at line: " << lineNo << endl;
        }

        // Start of multi-line comment
        if (!inMultiLine && line.find("/*") != string::npos) {
            inMultiLine = true;
            startLine = lineNo;
        }

        // End of multi-line comment
        if (inMultiLine && line.find("*/") != string::npos) {
            cout << "Comment found at line: " << startLine << ", " << lineNo << endl;
            inMultiLine = false;
        }
    }

    file.close();
    return 0;
}
