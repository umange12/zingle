#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct Message {
    char sender[50];
    char message[256];
    struct Message* next;
} Message;

void sendMessage(char* sender, char* receiver, char* message);
void displayMessages(char* username);

#endif

