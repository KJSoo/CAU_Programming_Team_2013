#include<stdio.h>
#include<stdlib.h>
#include "BaseFunction.h"
#include "MenuStruct.h"

void Permission();
void Order();
void OrderState();
void allSell();
void printMenu();
char name[_NAME_MAX_];

int main(){
	int a;

	Permission();
	printf("�ȳ��ϼ���.  Ŀ�Ǵ� %s���Դϴ�.\n",name);
	printf("	������������������\n");
	printf("	��  1.�ֹ�      ��\n");
	printf("	��  2.�ֹ�����  ��\n");
	printf("	��  3.����      ��\n");
	printf("	��  4.����      ��\n");
	printf("	������������������\n");
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

	int index,count[100];
	int i=0,j;
	Menu *temp = getHeadNode();

	printf("\n������������<�ֹ�>��������������������\n");
	initMenuStrut(_DEFAULT_MENU_FILE_);
	printMenu();
	while(1){
		i++;
		printf("\n��ȣ:");
		scanf("%d",temp->index);
		printf("\n����:");
		scanf("%d",temp->sellCount);
		temp = temp->next;
		system("cls");
		for(j=0;j<=i;j++){
			initMenuStrut(_DEFAULT_MENU_FILE_);
			printMenu();
		
		}
		printf("�ֹ��Ϸ�(0)\n\n\n\n");
		if(index==0)
			break;
		//������� ���� ����Ѵ�.
		printf("����Ͻðڽ��ϱ�?");	
		system("cls");
	}
}

void OrderState(){
	int index, state;

	printf("�ٲٰ����ϴ� ��ǰ�� �����Ͻʽÿ�.");
	scanf("%d",index);
	printf("1.���� 2.��ǰ�غ���");
	switch (state){
	case 1:
		printf("��ǰ�غ����Դϴ�.");
		break;
	case 2:
		printf("���Ǿ����ϴ�.");
		break;

	}
}

void allSell(){
	//���� �Ǹ��� �޴� 
	//����
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
