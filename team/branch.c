#include<stdio.h>
#include<stdlib.h>
#include "BaseFunction.h"
#include "MenuStruct.h"

void Permission();
void Order();
void OrderState();
void allSell();
void printMenu();
void printOrderMenu();
char name[_NAME_MAX_];

int main(){
	int a;
	initMenuStrut(_DEFAULT_MENU_FILE_);
	Permission();
	printf("안녕하세요.  커피니 %s점입니다.\n",name);
	printf("	┌───────┐\n");
	printf("	│  1.주문      │\n");
	printf("	│  2.주문상태  │\n");
	printf("	│  3.매출      │\n");
	printf("	│  4.종료      │\n");
	printf("	└───────┘\n");
	scanf("%d",&a);
	system("cls");
	switch(a){
	case 1 : 
		Order();
		break;
		system("PAUSE");
		system("cls");
	case 2:
		OrderState();
		break;
		system("PAUSE");
		system("cls");
	case 3:
		allSell();
		break;
		system("PAUSE");
		system("cls");
	case 4:
		break;
		system("PAUSE");
		system("cls");

	}

}

void Permission(){
	int k,i=0;
	char YN;
	int PWD;
	printf("지점의 이름을 적어주세요.");
	scanf("%s",name);
	system("cls");
	//PWD = getPermission(name);
	PWD = 2;
	while(1){
		if(PWD == 0){
			printf("승인요청하시겠습니까?(Y/N)");
			scanf("%c",&YN);
			if(YN == 'Y' || YN == 'y'){
				//requestChain(name);
				PWD = 1;
				//신청 완료
			}
			continue;
		}
		else if(PWD == 1){
			//PWD = getPermission(name);
			//if(PWD == 0) PWD = 1;CAU
			printf("신청한지점 : %s\n",name);
			printf("Wait...%d\n",++i);
			system("PAUSE");
			system("cls");
			continue;
		}else if(PWD == 2){
			break;
		}

	}
	system("cls");
}

void Order(){

	int index,count;
	int i=0,j;
	Menu *temp;

	while(1){
		printf("\n───┬──<주문>───┬───┬───\n");
		printMenu();
		printf("\n번호:");
		scanf("%d",&index);
		printf("\n갯수:");
		scanf("%d",&count);
		temp = getIndexOfNode(index);
		if(temp == NULL){
		
		}
		addSellCountByIndex(index,count);
		system("cls");
		printOrderMenu();
		//writeChainMenuList("cau.txt");
		printf("주문완료(0)\n\n\n\n");
		if(index==0)
			break;
		//음료들의 합을 출력한다.
		printf("계산하시겠습니까?");	
		system("cls");
	}
}

void OrderState(){
	int index, state;

	printf("바꾸고자하는 상품을 선택하십시오.");
	scanf("%d",index);
	printf("1.출고됨 2.상품준비중");
	switch (state){
	case 1:
		printf("상품준비중입니다.");
		break;
	case 2:
		printf("출고되었습니다.");
		break;

	}
}

void allSell(){
	//오늘 판매한 메뉴 
	//총합
}

void printMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("Index │ MenuName\t│Price │Order\n"); //1count
		printf("───┼────────┼───┼───\n");
		while (temp != NULL) { // 1->n
			printf("  %2d  │ %-12s\t│%d\t│%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

void printOrderMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("Index │ MenuName\t│Price │Order\n"); //1count
		printf("───┼────────┼───┼───\n");
		while (temp != NULL) { // 1->n
			if(temp -> sellCount > 0)
				printf("  %2d  │ %-12s\t│%d\t│%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}
