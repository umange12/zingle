#ifndef FRIEND_H
#define FRIEND_H

typedef struct Friend {
    char username[50];
    struct Friend* next;
} Friend;

typedef struct Message {
    char sender[50];
    char message[256];
    struct Message* next;
} Message;

typedef struct UserNode {
    char username[50];
    Friend* friends;
    Message* messages;
    struct UserNode* next;
} UserNode;

extern UserNode* userGraph[100];
extern int userCount;

int addFriend(char* user, char* friend);
int removeFriend(char* user, char* friend);
void displayFriends(char* username);

#endif
