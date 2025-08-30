#include "group.h"
#include "common.h"
#include "message.h"
#include "friend.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Group* groupList = NULL;
int groupCount = 0;

int createGroup(char* creator, char* groupName) {
    Group* current = groupList;
    while (current) {
        if (strcmp(current->groupName, groupName) == 0) {
            printf("Error: Group '%s' already exists.\n", groupName);
            clearScreen();
            return 0;
        }
        current = current->next;
    }
    if (groupCount >= 10) {
        printf("Error: Maximum group limit (10) reached.\n");
        clearScreen();
        return 0;
    }
    Group* newGroup = (Group*)malloc(sizeof(Group));
    strcpy(newGroup->groupName, groupName);
    newGroup->members = NULL;
    newGroup->messages = NULL;
    newGroup->next = groupList;
    groupList = newGroup;
    GroupMember* creatorMember = (GroupMember*)malloc(sizeof(GroupMember));
    strcpy(creatorMember->username, creator);
    creatorMember->next = newGroup->members;
    newGroup->members = creatorMember;
    groupCount++;
    printf("Group '%s' created successfully!\n", groupName);
    clearScreen();
    return 1;
}

int addMemberToGroup(char* groupName, char* username) {
    Group* group = groupList;
    while (group && strcmp(group->groupName, groupName) != 0) {
        group = group->next;
    }
    if (!group) {
        printf("Error: Group '%s' does not exist.\n", groupName);
        clearScreen();
        return 0;
    }
    GroupMember* member = group->members;
    while (member) {
        if (strcmp(member->username, username) == 0) {
            printf("Error: User '%s' is already a member of group '%s'.\n", username, groupName);
            clearScreen();
            return 0;
        }
        member = member->next;
    }
    GroupMember* newMember = (GroupMember*)malloc(sizeof(GroupMember));
    strcpy(newMember->username, username);
    newMember->next = group->members;
    group->members = newMember;
    printf("User '%s' added to group '%s'.\n", username, groupName);
    clearScreen();
    return 1;
}

void sendGroupMessage(char* sender, char* groupName, char* message) {
    Group* group = groupList;
    while (group && strcmp(group->groupName, groupName) != 0) {
        group = group->next;
    }
    if (!group) {
        printf("Error: Group '%s' does not exist.\n", groupName);
        clearScreen();
        return;
    }
    GroupMember* member = group->members;
    int isMember = 0;
    while (member) {
        if (strcmp(member->username, sender) == 0) {
            isMember = 1;
            break;
        }
        member = member->next;
    }
    if (!isMember) {
        printf("Error: You are not a member of group '%s'.\n", groupName);
        clearScreen();
        return;
    }
    char encryptedMessage[256];
    strcpy(encryptedMessage, message);
    xorCipher(encryptedMessage, sender);
    Message* newMessage = (Message*)malloc(sizeof(Message));
    strcpy(newMessage->sender, sender);
    strcpy(newMessage->message, encryptedMessage);
    newMessage->next = group->messages;
    group->messages = newMessage;
    member = group->members;
    while (member) {
        if (strcmp(member->username, sender) != 0) {
            sendMessage(sender, member->username, encryptedMessage);
        }
        member = member->next;
    }
    printf("Group message sent to '%s'.\n", groupName);
    clearScreen();
}

void displayGroupMessages(char* groupName) {
    Group* group = groupList;
    while (group && strcmp(group->groupName, groupName) != 0) {
        group = group->next;
    }
    if (!group) {
        printf("Error: Group '%s' does not exist.\n", groupName);
        clearScreen();
        return;
    }
    printf("Messages in group '%s':\n", groupName);
    Message* current = group->messages;
    if (!current) printf("No messages in group '%s'.\n", groupName);
    while (current) {
        char decryptedMessage[256];
        strcpy(decryptedMessage, current->message);
        xorCipher(decryptedMessage, current->sender);
        printf("From %s: %s\n", current->sender, decryptedMessage);
        current = current->next;
    }
    int ch = 0;
    do {
        printf("Enter 1 to return to home.\n");
        scanf("%d", &ch);
        getchar();
    } while (ch != 1);
    clearScreen();
}

