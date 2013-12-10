//
//  UserInformation.c
//  Test
//
//  Created by JiSoo Kim on 13. 12. 8..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#include "UserInformation.h"

UserInformation *_user = NULL;

void initUserInformation(const char* fileName){
    FILE *pFile = fopen(_DEFAULT_USER_FILE_,"r");
    char name[20];
    char phoneNumber[15];
    int point,dirthDay;
    if(pFile == NULL) return;
    while(fscanf(pFile, "%[^ ] %[^ ] %d %d",name,phoneNumber,&dirthDay,&point) != -1){
        fgetc(pFile);
        _user = createUserStruct(name, phoneNumber,dirthDay,point);
    }
	_user = getUserHeadNode();
}
void refreshUserInformation(){
    writeAllUser();
    _user = getUserHeadNode();
    if(_user == NULL);
    else
        while (_user->next != NULL) {
            _user = _user->next;
            free(_user->prev);
        }
    if(_user != NULL) free(_user);
    _user = NULL;
    initUserInformation(_DEFAULT_USER_FILE_);
}

UserInformation* createUserStruct(char *name, char *phoneNumber,int dirthDay,int point){
    UserInformation *user = (UserInformation*)malloc(sizeof(UserInformation));
	user->prev = NULL;
	user->next = NULL;
    if(name != NULL)
        setStringName(user->name, name);
    if(phoneNumber != NULL)
        setStringName(user->phoneNumber, phoneNumber);
    user->point = point;
    user->birthDay = dirthDay;
    connectUserNode(getUserTailNode(), user);
    if(user->prev == NULL) user->index = 1;
    else user->index = user->prev->index + 1;
    return user;
}
void createNewUser(){
    char name[20];
    char phoneNumber[20];
    int birthDay;
	printf("------ new user ------\n");
    printf("이름 : ");
    scanf("%s",name);
    printf("번호 : ");
    scanf("%s",phoneNumber);
    printf("생일 : ");
    scanf("%d",&birthDay);
    createUserStruct(name, phoneNumber, birthDay, 0);
}
void connectUserNode(UserInformation* prevNode, UserInformation* presentNode){
	presentNode -> prev = NULL;
	presentNode -> next = NULL;
    if(prevNode != NULL){
        prevNode -> next = presentNode;
        presentNode -> prev = prevNode;
    }
    else{
        _user = presentNode;
    }
}
UserInformation* getUserHeadNode(){
    if(_user == NULL) return NULL;
    else{
        while(_user->prev != NULL){
            _user = _user -> prev;
        }
        return _user;
    }
}

UserInformation* getUserTailNode(){
    if(_user == NULL) return NULL;
    else{
        while(_user->next != NULL){
            _user = _user -> next;
        }
        return _user;
    }
}
UserInformation *getUserByIndex(int index){
    if(_user == NULL) return NULL;
    else{
        UserInformation *head = getUserHeadNode(); // head 부터 tail 까지 순차적 순회를 합니다.
        while(head != NULL){
            if(head -> index == index) return head;
            else head = head -> next;
        }
        return head; // index 와 일치하는 값이 없을경우 NULL 을 리턴합니다.
    }
}
void printAllUser(){
	UserInformation *temp = getUserHeadNode();
    clear();
    if( temp == NULL) printf("회원이 없습니다.\n");
    else{
		printf("index\tname\t\tphone\t\tbirthday\tpoint\n");
        while (temp != NULL) {
            printf("%2d\t%-10s\t%-14s\t%-10d\t%-10d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
            temp = temp->next;
        }
    }
}
int editUserPoint(char variation,int index, int point){
    UserInformation *temp = getUserByIndex(index);
    if(temp == NULL) return 0;
    if(variation == '+'){
        temp -> point += point;
        writeAllUser();
        return 1;
    }else if(variation == '-'){
        if(temp -> point - point >= 0){
            temp->point -= point;
            writeAllUser();
            return 1;
        }
        else return 0;
        
    }else return 0;
}
void findUser(char *number,int birthDay){
    UserInformation *temp = getUserHeadNode();
    while (temp != NULL) {
        if(birthDay != 0 && temp->birthDay == birthDay && isContainString(temp->phoneNumber, number)){
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
        }else if(birthDay == 0 && isContainString(temp->phoneNumber, number)){
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
        }else if(number == NULL && temp->birthDay == birthDay)
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
        temp = temp->next;
    }
}
void writeAllUser(){
    FILE *pFile = fopen(_DEFAULT_USER_FILE_, "w");
    UserInformation *temp = getUserHeadNode();
    while (temp != NULL) {
        fprintf(pFile, "%s %s %d %d\n",temp->name,temp->phoneNumber,temp->birthDay,temp->point);
        if(temp->next == NULL)break;
        temp = temp->next;
    }
    fclose(pFile);
}
void showUserRecord(const char *name){
	FILE *user;
	char temp[50] = "user\\";
	int price,count,first, i = 1;
	strcat(temp,name);
	strcat(temp,".txt");
	user = fopen(temp,"r");
	if(user == NULL) {printf("not record\n"); return;}
	while(fscanf(user,"%[^0-9] %d %d",name,&price,&count) != -1){
		fgetc(user);
		if(name[0] == '.'){first = 1;continue;}
		else if(name[0] == '-'){
			int amount,point;
			fscanf(user,"%d %d",&amount,&point);
			fgetc(user);
			printf("buy : %d\tpoint : %d\n\n",amount,point);
			continue;
		}
		if(first == 1){first = 0; printf("----- %d -----\n",i++);}
		printf("%-10s\t%-5d\t%2d\n",name,price,count);
	}
	fclose(user);
}