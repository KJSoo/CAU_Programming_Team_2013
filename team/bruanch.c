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
		printf("�ȳ��ϼ���.  Ŀ�Ǵ� %s���Դϴ�.\n",name);
		printf("	����������������������\n");
		printf("	��  1.�ֹ�          ��\n");
		printf("	��  2.�ֹ� Ȯ��     ��\n");
		printf("	��  3.����Ʈ Ȯ��   ��\n");
		printf("	��  4.ȸ������      ��\n");
		printf("	��  5.�Ѹ���        ��\n");
		printf("	��  0.����          ��\n");
		printf("	����������������������\n");
		scanf("%d",&a);
		system("cls");
		switch(a){
           case 1 ://�ֹ�
                allcost += Order();
                system("PAUSE");
                system("cls");
                break;
                
			case 2://�ֹ�Ȯ��
                system("PAUSE");
                system("cls");
                break;
                
            case 3://ȸ������ Ȯ��
				printf("ã�����Ͻô� ȸ���� ��ȭ��ȣ ���ڸ��� �����ÿ�. :");
				scanf("%s",&backnum);
				findUser(backnum,0);
				system("PAUSE");
                system("cls");
                break;
				
			case 4://ȸ������
				printAllUser();
				createNewUser();
				refreshUserInformation();
                system("PAUSE");
                system("cls");
                break;
            
            
			case 5://�Ѹ���
				printAllOrderMenu();
                printf("\n�Ѹ���: %d",allcost);
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
    
	int index,count,way=0,INDEX;
	char answer,*backnum=0;
	int k=0;
	Menu *temp;
    
	while(1){
        
		printf("\n(%2d)����������<�ֹ�>��������������������\n",p);
		printMenu();
		printf("���������� �ֹ��Ϸ�(0)������������������");
		printf("\n\n��ȣ:");
		scanf("%d",&index);
		if(index==0){
			printf("����Ͻðڽ��ϱ�?(Y/N)");
			clearBuffer();
			scanf("%c",&answer);
			if(answer=='Y'||answer=='y'){
			printf("1.����/ī��\n2.����Ʈ\n");
			scanf("%d",&way);
			}
			else{
				printf("Goodbye See you later.");
			break;
			}
			
			switch(way){
			case 1:// ������ �����ش����� ȸ���� ��ȣ�� �Է��Ͽ� ����Ʈ �������ش�.���� ȸ�������� ������� 0�� �����ָ� ����������.
				k = writeChainMenuList(name);
				printf("%d�� �Դϴ�.",k);
				printf("ã�����Ͻô� ȸ���� ��ȭ��ȣ ���ڸ��� �����ÿ�. :");
				scanf("%s", &backnum);
				if(backnum==0)
					break;
				findUser(backnum,0);
				editUserPoint('+',INDEX,k*0.05);
				break;
		
			case 2://ȸ����ȣ�� �Է��Ͽ� ȸ���� ã�������� ����Ʈ���� ��´�.
				printf("ã�����Ͻô� ȸ���� ��ȭ��ȣ ���ڸ��� �����ÿ�. :");
				scanf("%s", &backnum);
				findUser(backnum,0);
				printf("�����ϰ����Ͻô� Index�� ��������");
				scanf("%d",INDEX);
				k = writeChainMenuList(name);
				printf("%d�� �Դϴ�.",k);
				if(editUserPoint('-',INDEX,k) == 0)printf("\n fail");
				break;
			}
			p++;
			break;
		}
		printf("\n����:");
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
		printf("  Index �� MenuName\t��Price ��Order\n");
		printf("����������������������������������������\n");
		while (temp != NULL) {
			printf("    %2d  �� %-12s\t��%d\t��%d\n",temp -> index, temp -> menuName, temp -> price,temp->allSellCount);
			temp = temp->next;
		}
	printf("����������������������������������������\n");
	}
}