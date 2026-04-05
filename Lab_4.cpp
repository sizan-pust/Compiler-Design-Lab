// #include <stdio.h>

// int main() {
//     FILE *fp;
//     char ch, next;

//     fp = fopen("input.c", "r");
//     if (fp == NULL) {
//         printf("File not found\n");
//         return 1;
//     }

//     while ((ch = fgetc(fp)) != EOF) {
//         if (ch == '/') {
//             next = fgetc(fp);

//             // Single-line comment
//             if (next == '/') {
//                 while ((ch = fgetc(fp)) != '\n' && ch != EOF);
//                 printf("\n");
//             }
//             // Multi-line comment
//             else if (next == '*') {
//                 while (1) {
//                     ch = fgetc(fp);
//                     next = fgetc(fp);
//                     if (ch == '*' && next == '/')
//                         break;
//                 }
//             }
//             else {
//                 printf("%c%c", ch, next);
//             }
//         }
//         else {
//             printf("%c", ch);
//         }
//     }

//     fclose(fp);
//     return 0;
// }
#include <stdio.h>

int main() {
    FILE *fp;
    char ch, next;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        if (ch == '/') {
            next = fgetc(fp);

            // Single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                printf("\n");   // keep line break
            }

            // Multi-line comment
            else if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
            }

            // Not a comment
            else {
                printf("%c", ch);
                ungetc(next, fp);
            }
        }
        else {
            printf("%c", ch);
        }
    }

    fclose(fp);
    return 0;
}
