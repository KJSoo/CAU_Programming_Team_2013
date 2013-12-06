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
	int k,i=0;
	char YN;
	int PWD;
	printf("������ �̸��� �����ּ���.");
	scanf("%s",name);
	clearBuffer();
	system("cls");
	PWD = getPermission(name);
	while(1){
		printAllChainList();
		if(PWD == 0){
			printf("��û�Ͻðڽ��ϱ�?(Y/N)");
			scanf("%c",&YN);
			if(YN == 'Y' || YN == 'y'){
				requestChain(name);
				PWD = 1;
				//��û �Ϸ�
			}
			continue;
		}
		else if(PWD == 1){
			PWD = getPermission(name);
			if(PWD == 0) PWD = 1;
			printf("��û������ : %s\n",name);
			printf("Wait...%d\n",++i);
			system("PAUSE");
			system("cls");
			continue;
		}else if(PWD == 2){
			break;
		}else {
			printf("%d",PWD);
		}

	}
	system("cls");
}

void Order(){

	int index,count;
	char answer;
	int j;
	int k[1000]={0};
	Menu *temp;

	while(1){

		printf("\n(%2d)����������<�ֹ�>��������������������\n",i);
		printMenu();
		printf("���������� �ֹ��Ϸ�(0)������������������");
		printf("\n\n��ȣ:");
		scanf("%d",&index);
		if(index==0){
			printf("����Ͻðڽ��ϱ�?(Y/N)");
			clearBuffer();
			scanf("%c",&answer);
			if(answer=='Y'||answer=='y'){
				k[i] = writeChainMenuList("cau.txt");
				i++;
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
		printf("  Index �� MenuName\t��Price ��Order\n"); 
		printf("����������������������������������������\n");
		while (temp != NULL) { 
			printf("    %2d  �� %-12s\t��%d\t��%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

void printOrderMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("  Index �� MenuName\t��Price ��Order\n"); //1count
		printf("����������������������������������������\n");
		while (temp != NULL) { // 1->n
			if(temp -> sellCount > 0)
				printf("    %2d  �� %-12s\t��%d\t��%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

void printAllOrderMenu(){
	Menu *temp = getHeadNode();
	if( temp == NULL) printf("Not menu.\n"); 
	else{
		printf("Index �� MenuName\t��Price  ��Order\n"); 
		printf("��������������������������������������\n");
		while (temp != NULL) { 
			if(temp -> sellCount > 0)
				printf("  %2d  �� %-12s\t��%d\t ��%d\n",temp -> index, temp -> menuName, temp -> price,temp->sellCount);
			temp = temp->next;
		}
	}
}

