#ifndef GROUP_H
#define GROUP_H

typedef struct GroupMember {
    char username[50];
    struct GroupMember* next;
} GroupMember;

typedef struct Group {
    char groupName[50];
    GroupMember* members;
    struct Message* messages;
    struct Group* next;
} Group;

extern Group* groupList;
extern int groupCount;

int createGroup(char* creator, char* groupName);
int addMemberToGroup(char* groupName, char* username);
void sendGroupMessage(char* sender, char* groupName, char* message);
void displayGroupMessages(char* groupName);

#endif

