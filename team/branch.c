#include<stdio.h>
#include<stdlib.h>
#include "BaseFunction.h"
#include "MenuStruct.h"
#include "ChainManage.h"

void Permission();
void Order();
void OrderState();
void printMenu();
void printOrderMenu();
int getAmountMoney();
void allsell();
char name[_NAME_MAX_];
int i=1;

int main(){
	int a=1;
	init();
	Permission();
	while(a){
		printf("안녕하세요.  커피니 %s점입니다.\n",name);
		printf("	┌───────┐\n");
		printf("	│  1.주문      │\n");
		printf("	│  2.총매출    │\n");
		printf("	│  3.종료      │\n");
		printf("	└───────┘\n");
		scanf("%d",&a);
		system("cls");
		switch(a){
            case 1 :
                Order();
                system("PAUSE");
                system("cls");
                break;
                
            case 2:
                allsell();
                system("PAUSE");
                system("cls");
                break;
                
            case 3:
                a=0;
                system("PAUSE");
                system("cls");
                break;
            case 0:
                a=-1;
                system("PAUSE");
                system("cls");
                break;
		}
	}
}

void Permission(){
	int i=0;
	char YN;
	int PWD;
	printf("지점의 이름을 적어주세요.");
	scanf("%s",name);
	clearBuffer();
	clear();
	PWD = getPermission(name);
	while(1){
		printAllChainList();
		if(PWD == 0){
			printf("요청하시겠습니까?(Y/N)");
			scanf("%c",&YN);
			if(YN == 'Y' || YN == 'y'){
				requestChain(name);
				PWD = 1;
				//신청 완료
			}
			continue;
		}
		else if(PWD == 1){
			PWD = getPermission(name);
			if(PWD == 0) PWD = 1;
			printf("신청한지점 : %s\n",name);
			printf("Wait...%d\n",++i);
			pause();
			clear();
			continue;
		}else if(PWD == 2){
			break;
		}else {
			printf("%d",PWD);
		}
        
	}
	clear();
}

void Order(){
    
	int index,count;
	char answer;
	int k[1000]={0};
	Menu *temp;
    
	while(1){
        
		printf("\n(%2d)──┬──<주문>──┬───┬───\n",i);
		printMenu();
		printf("────┴ 주문완료(0)─┴───┴───");
		printf("\n\n번호:");
		scanf("%d",&index);
		if(index==0){
			printf("계산하시겠습니까?(Y/N)");
			clearBuffer();
			scanf("%c",&answer);
			if(answer=='Y'||answer=='y'){
				k[i] = writeChainMenuList("cau.txt");
				i++;
				printf("%d원 입니다.",k[i-1]);
				
			}
			else{
				printf("Goodbye See you later.");
			}
			break;
		}
		printf("\n갯수:");
		scanf("%d",&count);
		temp = getIndexOfNode(index);
		if(temp == NULL){
            
		}
		addSellCountByIndex(index,count);
		system("cls");
		printOrderMenu();
        
		system("cls");
	}
}
/*
 void OrderState(){
 for(j=0;j<i;j++){
 printf();
 }
 }
 */
void allsell(const char*fileName){
    
	writeChainMenuList(fileName);
}
void printMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n");
	else{
		printf("  Index │ MenuName\t│Price │Order\n");
		printf("────┼───────┼───┼───\n");
		while (temp != NULL) {
			printf("    %2d  │ %-12s\t│%d\t│%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

void printOrderMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n");
	else{
		printf("  Index │ MenuName\t│Price │Order\n"); //1count
		printf("────┼───────┼───┼───\n");
		while (temp != NULL) { // 1->n
			if(temp -> sellCount > 0)
				printf("    %2d  │ %-12s\t│%d\t│%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

void printAllOrderMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("Index │ MenuName\t│Price  │Order\n"); 
		printf("───┼───────┼───┼───\n");
		while (temp != NULL) { 
			if(temp -> sellCount > 0)
				printf("  %2d  │ %-12s\t│%d\t │%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

