#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
#include "common.h"

void trimNewline(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void clearScreen() {
    #ifdef _WIN32
        Sleep(3000);
        system("cls");
    #else
        sleep(3);
        system("clear");
    #endif
}

unsigned int hash(char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % 101;
}

void xorCipher(char* message, char* key) {
    size_t keyLen = strlen(key);
    for (size_t i = 0; i < strlen(message); i++) {
        message[i] ^= key[i % keyLen];
    }
}

