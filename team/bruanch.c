#include<stdio.h>
#include<stdlib.h>
#include "BaseFunction.h"
#include "MenuStruct.h"
#include "ChainManage.h"

void Permission();
int Order();
void OrderState();
void printMenu();
void printOrderMenu();
int getAmountMoney();
int allsell();
char name[_NAME_MAX_];
static int p=1;


int main(){
	int a=1;
	init();
	Permission();
	while(a){
		printf("�ȳ��ϼ���.  Ŀ�Ǵ� %s���Դϴ�.\n",name);
		printf("	����������������������\n");
		printf("	��  1.�ֹ�          ��\n");
		printf("	��  2.����Ʈ ����   ��\n");
		printf("	��  3.�ֹ� Ȯ��     ��\n");
		printf("	��  4.�Ѹ���        ��\n");
		printf("	��  3.����          ��\n");
		printf("	����������������������\n");
		scanf("%d",&a);
		system("cls");
		switch(a){
            case 1 :
                Order();
                system("PAUSE");
                system("cls");
                break;
                
            case 2:
                
                system("PAUSE");
                system("cls");
                break;
                
            case 4:
                allsell();
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
	printf("������ �̸��� �����ּ���.");
	scanf("%s",name);
	clearBuffer();
	clear();
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
    
	int index,count,way;
	char answer;
	int k=0;
	Menu *temp;
    
	while(1){
        
		printf("\n(%2d)����������<�ֹ�>��������������������\n",p);
		printMenu();
		printf("���������� �ֹ��Ϸ�(0)������������������");
		printf("\n\n��ȣ:");
		scanf("%d",&index);
		if(index==0){
			printf("1.����/ī��");
			printf("����Ʈ");
			scanf("%d",&way);
			printf("����Ͻðڽ��ϱ�?(Y/N)");
			clearBuffer();
			scanf("%c",&answer);
			switch(way){
			case 1:
			if(answer=='Y'||answer=='y'){
				k = writeChainMenuList("cau.txt");
				p++;
				printf("%d�� �Դϴ�.",k);
			return k;	
			}
			else{
				printf("Goodbye See you later.");
			}
			break;
		}
			//case 2:
				//����Ʈ �˻�
				//����Ʈ ����
		}
		printf("\n����:");
		scanf("%d",&count);
		temp = getIndexOfNode(index);
		if(temp == NULL){
            
		}
		addSellCountByIndex(index,count);
		system("cfor()ls");
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
int allsell(){
    int i,allcost;
	printAllOrderMenu();
	for(i=1;i<p+1;i++)
	allcost += Order();
	return allcost;
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