#include<stdio.h>
#include<stdlib.h>
#include "BaseFunction.h"
#include "MenuStruct.h"
#include "ChainManage.h"
#include "UserInformation.h"

void Permission();
int Order();
void OrderState();
void printMenu();
void printOrderMenu();
void printAllOrderMenu();
int getAmountMoney();
char name[_NAME_MAX_];
static int p=1;


int main(){
	int a=1;
	int allcost=0;
	init();
	Permission();
	
	while(a){
		printf("안녕하세요.  커피니 %s점입니다.\n",name);
		printf("	┌─────────┐\n");
		printf("	│  1.주문          │\n");
		printf("	│  2.주문 확인     │\n");
		printf("	│  3.포인트 확인   │\n");
		printf("	│  4.회원가입      │\n");
		printf("	│  5.총매출        │\n");
		printf("	│  6.종료          │\n");
		printf("	└─────────┘\n");
		scanf("%d",&a);
		system("cls");
		switch(a){
            case 1 :
                allcost += Order();
                system("PAUSE");
                system("cls");
                break;
                
            case 2:
				createNewUser();
				//refreshUserInformation();
                //주문확인
                system("PAUSE");
                system("cls");
                break;
                
            case 3:
				//findUser("3333",0);
				printAllUser();
				if(editUserPoint('-',3,6000) == 0)printf("fail");

                system("PAUSE");
                system("cls");
                break;
            case 5:
				printAllOrderMenu();
                printf("지금까지의 매출 : %d원",allcost);
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

int Order(){
    
	int index,count,way=0;
	char answer;
	int k=0;
	Menu *temp;
    
	while(1){
        
		printf("\n(%2d)──┬──<주문>──┬───┬───\n",p);
		printMenu();
		printf("────┴ 주문완료(0)─┴───┴───");
		printf("\n\n번호:");
		scanf("%d",&index);
		if(index==0){
			printf("계산하시겠습니까?(Y/N)");
			clearBuffer();
			scanf("%c",&answer);
			if(answer=='Y'||answer=='y'){
			printf("1.현금/카드\n2.포인트\n");
			scanf("%d",&way);
			}
			else{
				printf("Goodbye See you later.");
			break;
			}
			
		
			switch(way){
			case 1:
				k = writeChainMenuList("cau");
				p++;
				printf("%d원 입니다.",k);
				break;
		
			case 2:
				k = writeChainMenuList(name);
				p++;
				printf("%d원 입니다.",k);
				
				//포인트 검색
				//포인트 차감
				break;
			}
			break;
		}
		printf("\n갯수:");
		scanf("%d",&count);
		temp = getIndexOfNode(index);
		if(temp == NULL){
        printf("NULL");
		}   
		addSellCountByIndex(index,count);
		system("cls");
		printOrderMenu();
        
		system("cls");
	
	}
	return k;
}
/*
 void OrderState(){
	 int i,j;
 for(j=0;j<i;j++){
	
 }
 printf("");

 }
 */
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
		printf("  Index │ MenuName\t│Price │Order\n");
		printf("────┼───────┼───┼───\n");
		while (temp != NULL) {
			printf("    %2d  │ %-12s\t│%d\t│%d\n",temp -> index, temp -> menuName, temp -> price,temp->allSellCount);
			temp = temp->next;
		}
	printf("────┼───────┼───┼───\n");
	}
}