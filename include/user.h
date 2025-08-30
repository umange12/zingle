#ifndef USER_H
#define USER_H

#define HASH_SIZE 101

typedef struct User {
    char username[50];
    char password[50];
    struct User* next;
} User;

extern User* hashTable[HASH_SIZE];

int usernameExists(char* username);
int registerUser(char* username, char* password);
int loginUser(char* username, char* password);

#endif

