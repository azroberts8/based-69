#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

void print_usage(char *cmd) {
    printf("Usage: %s <encode | decode>\n", cmd);
}

wchar_t* take_input() {
    size_t size = 100;  // Initial buffer size
    size_t len = 0;     // Length of the input string
    wchar_t *str = malloc(size * sizeof(wchar_t));  // Allocate initial buffer

    if (!str) {
        fwprintf(stderr, L"Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    wint_t ch;
    while ((ch = fgetwc(stdin)) != L'\n' && ch != WEOF) {
        str[len++] = ch;

        // If the length of the input string exceeds the buffer size, reallocate
        if (len == size) {
            size *= 2;  // Double the buffer size
            str = realloc(str, size * sizeof(wchar_t));

            if (!str) {
                fwprintf(stderr, L"Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    str[len] = L'\0';  // Null-terminate the string
    return str;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Error: Too few arguments passed.\n");
        print_usage(argv[0]);
        return 1;
    }

    if(argc > 2) {
        printf("Error: Too many arguments passed.\n");
        print_usage(argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "help") == 0) {
        print_usage(argv[0]);
        return 0;
    } else if(strcmp(argv[1], "encode") == 0) {
        wchar_t* data = take_input();
        wprintf(L"%ls\n", data);
        return 0;
    } else if(strcmp(argv[1], "decode") == 0) {
        wchar_t* data = take_input();
        wprintf(L"%ls\n", data);
        return 0;
    } else {
        printf("Error: Unknown argument '%s'\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }
}