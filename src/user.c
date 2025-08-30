#include "user.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

User* hashTable[HASH_SIZE] = {NULL};

int usernameExists(char* username) {
    unsigned int index = hash(username);
    User* current = hashTable[index];
    while (current) {
        if (strcmp(current->username, username) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int registerUser(char* username, char* password) {
    if (usernameExists(username)) {
        printf("Error: Username '%s' already exists!\n", username);
        clearScreen();
        return 0;
    }

    unsigned int index = hash(username);
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->next = hashTable[index];
    hashTable[index] = newUser;
    printf("User registered successfully!\n");
    clearScreen();
    return 1;
}

int loginUser(char* username, char* password) {
    unsigned int index = hash(username);
    User* current = hashTable[index];
    while (current) {
        if (strcmp(current->username, username) == 0 &&
            strcmp(current->password, password) == 0) {
            clearScreen();
            return 1;
        }
        current = current->next;
    }
    return 0;
}

