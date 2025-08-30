#include "friend.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UserNode* userGraph[100] = {NULL};
int userCount = 0;

int addFriend(char* user, char* friend) {
    UserNode* userNode = NULL;
    UserNode* friendNode = NULL;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(userGraph[i]->username, user) == 0) {
            userNode = userGraph[i];
        }
        if (strcmp(userGraph[i]->username, friend) == 0) {
            friendNode = userGraph[i];
        }
    }

    if (!friendNode) {
        printf("Error: User '%s' does not exist.\n", friend);
        clearScreen();
        return 0;
    }

    Friend* temp = userNode->friends;
    while (temp) {
        if (strcmp(temp->username, friend) == 0) {
            printf("You are already friends with %s\n", friend);
            clearScreen();
            return 0;
        }
        temp = temp->next;
    }

    Friend* newFriend1 = (Friend*)malloc(sizeof(Friend));
    strcpy(newFriend1->username, friend);
    newFriend1->next = userNode->friends;
    userNode->friends = newFriend1;

    Friend* newFriend2 = (Friend*)malloc(sizeof(Friend));
    strcpy(newFriend2->username, user);
    newFriend2->next = friendNode->friends;
    friendNode->friends = newFriend2;

    printf("%s and %s are now friends!\n", user, friend);
    clearScreen();
    return 1;
}

void removeFromFriendList(UserNode* userNode, char* friendName) {
    Friend* current = userNode->friends;
    Friend* previous = NULL;
    while (current) {
        if (strcmp(current->username, friendName) == 0) {
            if (previous) previous->next = current->next;
            else userNode->friends = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

int removeFriend(char* user, char* friend) {
    UserNode* userNode = NULL;
    UserNode* friendNode = NULL;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(userGraph[i]->username, user) == 0) {
            userNode = userGraph[i];
        }
        if (strcmp(userGraph[i]->username, friend) == 0) {
            friendNode = userGraph[i];
        }
    }

    if (!friendNode) {
        printf("Error: User '%s' does not exist.\n", friend);
        clearScreen();
        return 0;
    }

    Friend* temp = userNode->friends;
    int found = 0;
    while (temp) {
        if (strcmp(temp->username, friend) == 0) {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Error: '%s' is not in your friend list.\n", friend);
        clearScreen();
        return 0;
    }

    removeFromFriendList(userNode, friend);
    removeFromFriendList(friendNode, user);

    printf("%s and %s are no longer friends.\n", user, friend);
    clearScreen();
    return 1;
}

void displayFriends(char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userGraph[i]->username, username) == 0) {
            Friend* currentFriend = userGraph[i]->friends;
            printf("Friends of %s:\n", username);
            if (!currentFriend) printf("No friends found.\n");
            while (currentFriend) {
                printf("%s\n", currentFriend->username);
                currentFriend = currentFriend->next;
            }
            clearScreen();
            return;
        }
    }
    printf("User not found!\n");
    clearScreen();
}

