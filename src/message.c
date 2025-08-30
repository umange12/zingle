#include "message.h"
#include "common.h"
#include "friend.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sendMessage(char* sender, char* receiver, char* message) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userGraph[i]->username, receiver) == 0) {
            Message* newMessage = (Message*)malloc(sizeof(Message));
            strcpy(newMessage->sender, sender);
            strcpy(newMessage->message, message);
            newMessage->next = NULL;

            if (userGraph[i]->messages == NULL) {
                userGraph[i]->messages = newMessage;
            } else {
                Message* temp = userGraph[i]->messages;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newMessage;
            }

            printf("Message sent to %s\n", receiver);
            clearScreen();
            return;
        }
    }
    printf("Receiver not found!\n");
    clearScreen();
}

void displayMessages(char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userGraph[i]->username, username) == 0) {
            Message* currentMessage = userGraph[i]->messages;
            printf("Messages for %s:\n", username);
            if (!currentMessage) printf("No messages found.\n");
            while (currentMessage) {
                char decryptedMessage[256];
                strcpy(decryptedMessage, currentMessage->message);
                xorCipher(decryptedMessage, currentMessage->sender);
                printf("From %s: %s\n", currentMessage->sender, decryptedMessage);
                currentMessage = currentMessage->next;
            }
            int ch = 0;
            do {
                printf("Enter 1 to return to home.\n");
                scanf("%d", &ch);
                getchar();
            } while (ch != 1);
            clearScreen();
            return;
        }
    }
    printf("User not found!\n");
    clearScreen();
}

