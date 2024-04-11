#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Given a string (char*) of words separated
/// by whitespaces reverse the order of words
// char *reverse_word(char *str) {
//     size_t last = strlen(str);
//     size_t start = last;
//
//     char *return_string = malloc(last + 1);
//
//     while (last > 0) {
//         while (start > 0 && str[start - 1] == ' ') {
//             start--;
//         }
//         // make the last char the first non whitespace encountered
//         last = start;
//         // find the start of the current word pointed
//         while (start > 0 && str[start - 1] != ' ') {
//             // printf("string of start = %s\n", &str[start]);
//             start--;
//         }
//         // copy the word into the return string
//         strncpy(return_string, &str[start], last - start);
//         return_string[last - start] = '\0';
//         // if not last word append a space
//         if (start > 0) {
//             strcat(return_string, " ");
//         }
//         last = start;
//     }
//     return return_string;
// }

char *reverse_word(char *str) {
    size_t last = strlen(str);
    size_t start = last;

    char *return_string = malloc(last + 1);

    while (last > 0) {
        while (start > 0 && str[start - 1] == ' ') {
            start--;
        }
        // make the last char the first non whitespace encountered
        last = start;
        // find the start of the current word pointed
        while (start > 0 && str[start - 1] != ' ') {
            start--;
        }
        // copy the word into the return string
        strncpy(return_string + strlen(return_string), &str[start],
                last - start);
        return_string[strlen(return_string) + last - start] = '\0';
        // append a space if not the last
        if (start > 0) {
            strcat(return_string, " ");
        }
        last = start;
    }

    size_t result_len = strlen(return_string);
    if (return_string[result_len - 1] == ' ') {
        return_string[result_len - 1] = '\0';
    }

    return return_string;
}

int main() {
    char input[] = "   Hello   World!   ";
    char *output = reverse_word(input);
    if (output != NULL) {
        printf("Reversed: \"%s\"\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}
