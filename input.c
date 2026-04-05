// #include <stdio.h>
// // This is a single line comment
// int main() {
//     int a = 10;
//     float b = 20.5;
//     /* multi-line
//        comment */
//     return 0; // This is a single line comment
// }
#include <stdio.h>
#include <string.h>

char str[100];
int i = 0;
int l = 0;

int A(); // returns 1 on success, 0 on failure
int B();
int S();

int A() {
    // A -> a | a A   (one or more 'a')
    if (i < l && str[i] == 'a') {
        // consume at least one 'a'
        while (i < l && str[i] == 'a') {
            i++;
        }
        return 1; // matched one or more a's
    }
    return 0; // no leading 'a' => fail
}

int B() {
    // B -> b
    if (i < l && str[i] == 'b') {
        i++;
        return 1;
    }
    return 0;
}

int S() {
    // S -> b | A B
    int save = i;

    // option 1: single 'b'
    if (i < l && str[i] == 'b') {
        i++;
        return 1;
    }

    // option 2: A B
    i = save; // restore (though unchanged)
    if (A()) {
        if (B()) return 1;
        else { i = save; return 0; }
    }
    // neither alternative matched
    i = save;
    return 0;
}

int main() {
    // examples to test
    char *tests[] = { "b", "ab", "aab", "aaab", "ad", "abb", "abx", " " };
    int n = sizeof(tests)/sizeof(tests[0]);
    for (int t = 0; t < n; ++t) {
        strcpy(str, tests[t]);
        l = strlen(str);
        i = 0;
        int ok = S();
        if (ok && i == l) printf("%s -> accepted\n", str);
        else printf("%s -> rejected\n", str);
    }
    return 0;
}
