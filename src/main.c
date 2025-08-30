#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "friend.h"
#include "message.h"
#include "group.h"
#include "common.h"

void loadingBar() {
    printf("Loading...");
    for (int i = 0; i < 10; i++) {
        fflush(stdout);
        #ifdef _WIN32
            Sleep(100);
        #else
            sleep(1);
        #endif
        printf(".");
    }
    printf("\n");
    clearScreen();
}

int main() {
    int choice;
    char username[50], password[50], friend[50], groupName[50], message[256];

    while (1) {
        printf("\033[1;31m");
        printf("==================================\n");
        printf("|          \\     /               |\n");
        printf("|           \\ _ /                |\n");
        printf("|         --('v')--              |\n");
        printf("|          ((   ))               |\n");
        printf("|          --\"-\"--               |\n");
        printf("|   Welcome to Zingle-Zingle     |\n");
        printf("==================================\n");
        printf("\033[0m");
        loadingBar();
        printf("1. Login\n2. New User Registration\n3. Exit\n\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                trimNewline(username);
                printf("Enter password: ");
                fgets(password, sizeof(password), stdin);
                trimNewline(password);

                if (loginUser(username, password)) {
                    printf("Login successful!\n");
                    int userChoice;
                    while (1) {
                        printf("1. Add Friend\n2. Remove Friend\n3. Message\n4. Display Friends\n5. Display Messages\n6. Create Group\n7. Add Member to Group\n8. Send Group Message\n9. Display Group Messages\n10. Logout\n");
                        scanf("%d", &userChoice);
                        getchar();

                        if (userChoice == 10) {
                            clearScreen();
                            break;
                        }

                        switch (userChoice) {
                            case 1:
                                printf("Enter friend's username: ");
                                fgets(friend, sizeof(friend), stdin);
                                trimNewline(friend);
                                addFriend(username, friend);
                                break;
                            case 2:
                                printf("Enter friend's username to remove: ");
                                fgets(friend, sizeof(friend), stdin);
                                trimNewline(friend);
                                if (removeFriend(username, friend)) {
                                    printf("Friend removed successfully!\n");
                                } else {
                                    printf("Friend not found!\n");
                                }
                                break;
                            case 3:
                                printf("Enter receiver's username: ");
                                fgets(friend, sizeof(friend), stdin);
                                trimNewline(friend);
                                printf("Enter message: ");
                                fgets(message, sizeof(message), stdin);
                                trimNewline(message);
                                xorCipher(message, username);
                                sendMessage(username, friend, message);
                                break;
                            case 4:
                                displayFriends(username);
                                break;
                            case 5:
                                displayMessages(username);
                                break;
                            case 6:
                                printf("Enter group name: ");
                                fgets(groupName, sizeof(groupName), stdin);
                                trimNewline(groupName);
                                createGroup(username, groupName);
                                break;
                            case 7:
                                printf("Enter group name: ");
                                fgets(groupName, sizeof(groupName), stdin);
                                trimNewline(groupName);
                                printf("Enter username to add: ");
                                fgets(friend, sizeof(friend), stdin);
                                trimNewline(friend);
                                addMemberToGroup(groupName, friend);
                                break;
                            case 8:
                                printf("Enter group name: ");
                                fgets(groupName, sizeof(groupName), stdin);
                                trimNewline(groupName);
                                printf("Enter message: ");
                                fgets(message, sizeof(message), stdin);
                                trimNewline(message);
                                sendGroupMessage(username, groupName, message);
                                break;
                            case 9:
                                printf("Enter group name: ");
                                fgets(groupName, sizeof(groupName), stdin);
                                trimNewline(groupName);
                                displayGroupMessages(groupName);
                                break;
                            default:
                                printf("Invalid choice!\n");
                                clearScreen();
                        }
                    }
                } else {
                    printf("Invalid username or password!\n");
                    clearScreen();
                }
                break;

            case 2:
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                trimNewline(username);
                printf("Enter password: ");
                fgets(password, sizeof(password), stdin);
                trimNewline(password);
                registerUser(username, password);
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice!\n");
                clearScreen();
        }
    }

    return 0;
}

