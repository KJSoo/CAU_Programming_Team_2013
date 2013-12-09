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
	char *backnum=0;
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
		printf("	│  0.종료          │\n");
		printf("	└─────────┘\n");
		scanf("%d",&a);
		system("cls");
		switch(a){
           case 1 ://주문
                allcost += Order();
                system("PAUSE");
                system("cls");
                break;
                
			case 2://주문확인
                system("PAUSE");
                system("cls");
                break;
                
            case 3://회원정보 확인
				printf("찾고자하시는 회원의 전화번호 뒷자리를 적으시오. :");
				scanf("%s",&backnum);
				findUser(backnum,0);
				system("PAUSE");
                system("cls");
                break;
				
			case 4://회원가입
				printAllUser();
				createNewUser();
				refreshUserInformation();
                system("PAUSE");
                system("cls");
                break;
            
            
			case 5://총매출
				printAllOrderMenu();
                printf("\n총매출: %d",allcost);
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
    
	int index,count,way=0,INDEX;
	char answer,*backnum=0;
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
			case 1:// 가격을 보여준다음에 회원의 번호를 입력하여 포인트 적립해준다.만약 회원정보가 없을경우 0을 눌러주면 빠져나간다.
				k = writeChainMenuList(name);
				printf("%d원 입니다.",k);
				printf("찾고자하시는 회원의 전화번호 뒷자리를 적으시오. :");
				scanf("%s", &backnum);
				if(backnum==0)
					break;
				findUser(backnum,0);
				editUserPoint('+',INDEX,k*0.05);
				break;
		
			case 2://회원번호를 입력하여 회원을 찾은다음에 포인트에서 깍는다.
				printf("찾고자하시는 회원의 전화번호 뒷자리를 적으시오. :");
				scanf("%s", &backnum);
				findUser(backnum,0);
				printf("적립하고자하시는 Index를 적으세요");
				scanf("%d",INDEX);
				k = writeChainMenuList(name);
				printf("%d원 입니다.",k);
				if(editUserPoint('-',INDEX,k) == 0)printf("\n fail");
				break;
			}
			p++;
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
	printf("────┴───────┴───┴───\n");
	}
}