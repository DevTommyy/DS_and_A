#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// util function that make the whole word lowercase
void make_lowercase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// utils function that strips both whitespaces and punctuation
char *strip(char *str) {
    char *stripped = malloc(strlen(str));
    char *stripped_ptr = stripped;

    while (*str) {
        if (isalpha(*str)) {
            *stripped_ptr = *str;
            stripped_ptr++;
        }
        str++;
    }
    *stripped_ptr = '\0';
    return stripped;
}

// check if the word is palindrome by using the 2 pointers technique
bool is_palindrome(char *word) {
    char *stripped = strip(word);
    make_lowercase(stripped);

    size_t left = 0;
    size_t right = strlen(stripped) - 1;

    while (left < right) {
        if (stripped[left] != stripped[right]) {
            free(stripped);
            return false; // not a palindrome
        }
        left++;
        right--;
    }

    free(stripped);
    return true; // palindrome
}

int main() {

    char sentence[] = "A man, a plan, a canal, Panama!";
    if (is_palindrome(sentence)) {
        printf("'%s' is a palindrome.\n", sentence);
    } else {
        printf("'%s' is not a palindrome.\n", sentence);
    }

    return 0;
}
