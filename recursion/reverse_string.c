#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printReverse(const char *str) {
    if (!*str)
        return;
    printReverse(str + 1);
    putchar(*str);
}

// Function to reverse a string
void reverse(char *str, char *rev) {
    if (!*str) {
        *rev = '\0';
        return;
    }
    reverse(str + 1, rev);
    strncat(rev, str, 1);
}

int main() {
    char str[] = "Test";
    char *rev = malloc(sizeof(str));
    reverse(str, rev);
    printf("Original string: %s\n", str);
    printf("Reversed string: %s\n", rev);
    return 0;
}
