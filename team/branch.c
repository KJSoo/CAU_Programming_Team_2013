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
int getAmountMoney();
char name[_NAME_MAX_];

int main(){
	int a=1;
	initMenuStrut(_DEFAULT_MENU_FILE_);
	Permission();
	while(a){
		printf("�ȳ��ϼ���.  Ŀ�Ǵ� %s���Դϴ�.\n",name);
		printf("	������������������\n");
		printf("	��  1.�ֹ�      ��\n");
		printf("	��  2.�Ѹ���    ��\n");
		printf("	��  3.����      ��\n");
		printf("	������������������\n");
		scanf("%d",&a);
		system("cls");
		switch(a){
		case 1 : 
			Order();
			system("PAUSE");
			system("cls");
			break;
			
		case 2:
			OrderState();
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
	int k,i=0;
	char YN;
	int PWD;
	printf("������ �̸��� �����ּ���.");
	scanf("%s",name);
	system("cls");
	//PWD = getPermission(name);
	PWD = 2;
	while(1){
		if(PWD == 0){
			printf("���ο�û�Ͻðڽ��ϱ�?(Y/N)");
			scanf("%c",&YN);
			if(YN == 'Y' || YN == 'y'){
				//requestChain(name);
				PWD = 1;
				//��û �Ϸ�
			}
			continue;
		}
		else if(PWD == 1){
			//PWD = getPermission(name);
			//if(PWD == 0) PWD = 1;CAU
			printf("��û������ : %s\n",name);
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
	char answer;
	int i=0,j;
	int k=0;
	Menu *temp;

	while(1){
		printf("\n������������<�ֹ�>����������������������\n");
		printMenu();
		printf("���������� �ֹ��Ϸ�(0)������������������");
		printf("\n\n��ȣ:");
		scanf("%d",&index);
		if(index==0){
			printf("����Ͻðڽ��ϱ�?");
			clearBuffer();
			scanf("%c",&answer);
			if(answer=='Y'||answer=='y'){
				k = writeChainMenuList("cau.txt");
				printf("%d�� �Դϴ�.",k);
			}
			else{
				printf("Goodbye See you later.");	
			}
			break;
		}
		printf("\n����:");
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
void OrderState(){}

void allSell(){

	getAmountMoney();
}

void printMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("Index �� MenuName\t��Price ��Order\n"); //1count
		printf("����������������������������������������\n");
		while (temp != NULL) { // 1->n
			printf("  %2d  �� %-12s\t��%d\t��%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

void printOrderMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("Index �� MenuName\t��Price ��Order\n"); //1count
		printf("����������������������������������������\n");
		while (temp != NULL) { // 1->n
			if(temp -> sellCount > 0)
				printf("  %2d  �� %-12s\t��%d\t��%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}
int getAmountMoney(){
	int amount = 0;
    Menu *temp = getHeadNode();
    while (temp != NULL) {
		amount += (temp->price * temp->allSellCount);
		if(temp -> next == NULL) break;
        temp = temp->next;
    }
	return amount;
}