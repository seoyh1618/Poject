#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
typedef int element;

typedef struct listNode{
	struct listNode* leftLink;
	element data;
	struct listNode* rightLink;
}listNode;
typedef struct positionNode{
	int rightBalance;
	listNode* targetNode;
	int leftBalance;
	int startSwitch;
}positionNode;

//fuc define
int selectOption(void);
listNode* nodeCreation(void);
void nodeInsertion(listNode** headNode,positionNode* posNode);
void nodeDelete(listNode** headNode,positionNode* posNode);
void nodeCheck(listNode** headNode);
int selectPosInset(listNode** headNode, positionNode* posNode, element compareData);
int selectPosDelete(listNode** headNode, positionNode* posNode, element deleteData);
positionNode* posNodeInit(void);

//main 
int main(void){
	listNode* headNode = NULL;
	positionNode* posNode = posNodeInit();
	
	while(1){
		switch(selectOption()){
			case 1: nodeInsertion(&headNode ,posNode);
				 	break;
			case 2: nodeDelete(&headNode ,posNode);
					break;
			case 3: nodeCheck(&headNode);
		 		 	break;
			case 4: printf(" ���α׷��� �����մϴ�. \n");
	 			 	free(posNode);
	 			 	free(headNode);
					exit(0);		
			case 5: 
					if(posNode->targetNode == NULL){
						printf("tagetNode is not disignated\n");
						printf("Target startSwitch %d\n",posNode->startSwitch);
						printf("Target left %d\n",posNode->leftBalance); 
						printf("Target right %d\n",posNode->rightBalance); 	 
						break;
					}
					printf("target check : %d \n",posNode->targetNode->data); 	
					printf("Target left %d\n",posNode->leftBalance); 
					printf("Target right %d\n",posNode->rightBalance); 	
					printf("Target startSwitch %d\n",posNode->startSwitch); 	
					break;
			default : printf("���� �߸� �Է� �Ǿ����ϴ�. �ٽ� �������ּ���\n");
		}
	}

	return 0;
}
// Menu Print 
int selectOption(void){
	int selectOption;
	printf("\n\t\t�޴�\n");
	printf("1. ����  2. ����  3. Ȯ��  4. ����\n");
	printf("�޴��� �����ϼ��� : ");
	scanf("%d",&selectOption);
	printf("\n");
	return selectOption;
}
// Node Create
listNode* nodeCreation(void){
	listNode* createNode = (listNode* )malloc(sizeof(listNode));
	element data;
	printf("������ ������ �Է��ϼ���\n");
	printf(" >>");
	scanf("%d",&data);
	createNode->data = data;
	createNode->leftLink=NULL;
	createNode->rightLink=NULL;
	
	printf("������ ���� �Ǿ����ϴ�. \n");
	return createNode;
}
// Pos Init 
positionNode* posNodeInit(void){
	positionNode* posNode = (positionNode* )malloc(sizeof(positionNode));
	posNode->leftBalance = 0;
	posNode->rightBalance = 0;
	posNode->targetNode=NULL;
	posNode->startSwitch=0;
	return posNode;
}

// Insertion
void nodeInsertion(listNode** headNode,positionNode* posNode){	
	 listNode* createNode = nodeCreation();
	 listNode* subHeadNode = *headNode;

	 if(subHeadNode == NULL){					//ù ��° ���� 
	 	 createNode->leftLink = createNode;
		 createNode->rightLink = createNode;
		 *headNode = createNode;
		 printf("First Insert\n");
		 return;
	 }
  
	if(subHeadNode->data > createNode->data){	//����� ���� ������ ���� : ����� ���� 
			createNode->leftLink=(*headNode)->leftLink;	//������ ���� �� ����� ����  
			subHeadNode->leftLink->rightLink=createNode;
			createNode->rightLink=subHeadNode;
			subHeadNode->leftLink=createNode;
			(*headNode)=createNode;
			if(posNode->startSwitch == 2){								 
				if(1==selectPosInset(headNode,posNode,createNode->data));//headNode���� ������ ���Խ� �������� �̵� �Լ��� integer Ÿ���� ��ȯ�ϱ⶧���� ����, right �� ���� �� 2�̳� Ÿ�� ��� ������ �ʿ��Ѱ��  
			}else{
				posNode->startSwitch++;		
			}
			printf("Head Change \n");
			return;
	}

 	if(1==selectPosInset(headNode,posNode,createNode->data)){	//N ��° ��� ����� ���� ���� Ž��  ����  
		do{	
		    if(subHeadNode->data > createNode->data){			//Ÿ�������ɽ� �׻� �߰��� ���� �Ǳ⶧���� ������ : �߰��� �����ڵ� ������ : �ش� �ڵ�θ� ���� 
		    	createNode->leftLink=subHeadNode->leftLink;		
		    	subHeadNode->leftLink->rightLink=createNode;
		    	createNode->rightLink=subHeadNode;
		    	subHeadNode->leftLink=createNode;
		    	return;
			}
			subHeadNode=subHeadNode->rightLink; 	
		}while(subHeadNode != *headNode);
  		 
		createNode->leftLink=subHeadNode->leftLink;				//Ÿ�� ��� ������ ��������� ���� �Ұ��Ͽ� ������ �������ϰ��ϴ� �ڵ� 
 		subHeadNode->leftLink->rightLink=createNode;
  		createNode->rightLink=subHeadNode;
   		subHeadNode->leftLink=createNode;	
	}else{														//N ��° ��� ����� ���� ���� Ž��  ���� , Ÿ������������ ��� x ������ ��� ���� �ڵ� x  
	    while(1){												//�������� ���� �Ǳ⶧���� ���ѷ��� ���� 
	    	subHeadNode=subHeadNode->leftLink;					
	    	
			if(subHeadNode->data < createNode->data){			//�߰� �����ϴ� �ڵ� 
		    	createNode->leftLink=subHeadNode;
		    	createNode->rightLink=subHeadNode->rightLink;
				subHeadNode->rightLink->leftLink=createNode;
		    	subHeadNode->rightLink=createNode;
		    	return;
			}
		}	    		
	}
	
}
// setting Position_insert
int selectPosInset(listNode** headNode, positionNode* posNode ,element compareData){
	int reSetTarget; 

	if( posNode->startSwitch < 2){										// startSwitch 2�� �ƴҰ�� ���� �� ���� Ž�� ���� 
		posNode->startSwitch++;
		return 1;
	}
	else if(posNode->targetNode == NULL){								// node������ ���� 3���̸� return�� ������ ��������� target��� ���� 
			posNode->targetNode = (*headNode)->rightLink->rightLink;
			printf("Taget setting %d \n",posNode->targetNode->data);
			return 1;
	}
	
	if((posNode->targetNode->data) > compareData){						// tartget ��庸�� ���Ե� �����Ͱ� ������� ���� Ž�� �� �뷱�� ����  
		posNode->rightBalance++;
		printf("Search to right %d\n",posNode->rightBalance);
	    
	    reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
		
	    if((posNode->leftBalance) < (posNode->rightBalance) && reSetTarget == 2){	//�뷱���� ������ ��� �������� �̵��Ͽ� Ÿ�ϳ�� ������ �� �ʱ�ȭ 
			posNode->targetNode = posNode->targetNode->leftLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change right %d\n",posNode->targetNode->data); 
		}
		return 1; 														// ���� Ž�� �� �� �ֵ��� �� ����  
		
	}else{																//tartget ��庸�� ���Ե� �����Ͱ� Ŭ��� ���� Ž�� �� �뷱�� ����  
        posNode->leftBalance++;
        printf("Search to left : %d \n",posNode->leftBalance);
        
		reSetTarget = abs((posNode->leftBalance)-(posNode->rightBalance));
		
		if((posNode->leftBalance) > (posNode->rightBalance) && reSetTarget == 2){ //�뷱���� ������ ��� �������� �̵��Ͽ� Ÿ�ϳ�� ������ �� �ʱ�ȭ 
			posNode->targetNode = posNode->targetNode->rightLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;  
  			printf("Target Change left %d\n",posNode->targetNode->data); 
		}
		return 2; 														//���� Ž�� �� �� �ֵ��� �� ���� 
    }	
}
// Delete
void nodeDelete(listNode** headNode,positionNode* posNode){
	listNode* subHeadNode = *headNode;			
	listNode* removedNode;
	element deleteData;
	
	printf("������ ���� �Է��ϼ���\n >> ");
	scanf("%d",&deleteData);
	
	if(deleteData == 999){				//999�Է½� ��ü��� ����  
		(*headNode)=NULL;
		printf("Sucess ALL clear\n");
	}
										 
	if(posNode->targetNode==NULL){ 				// node�� 3�� ����, Ÿ�� ��� �������� ���� 
			
		if((*headNode)==NULL){							// NODE is empty 
			printf("����Ʈ�� ��� �ֽ��ϴ�. \n"); 
			return;
		}
		else if(subHeadNode->data==deleteData){ 		// HeadNode�� ���� ��� 
			 removedNode=subHeadNode;
			 
			 if(subHeadNode->rightLink==subHeadNode){		//HeadNode�� ������ ���  
				(*headNode)=NULL;
				printf("headNULL RESET\n");
			 }else{											//��尡 2 , 3 ���� ����� ������ 
				(*headNode)=removedNode->rightLink;		
				removedNode->leftLink->rightLink=(*headNode);
			    subHeadNode->leftLink=removedNode;
				posNode->startSwitch--; 					//��尡 4��° ���Խ� target��尡 ���� �� �� �ֵ��� 2 , 3���� ��� ����ġ ����  
			 }
			 free(removedNode);
			 return;
		}
		else{											// 2�� , 3�� ��尡 ������ ���   
			do{											
				subHeadNode = subHeadNode->rightLink;
				if(subHeadNode->data==deleteData){ 
					posNode->startSwitch--;				//��尡 4��° ���Խ� target��尡 ���� �� �� �ֵ��� 2 , 3���� ��� ����ġ ����  
					removedNode = subHeadNode;
					removedNode->leftLink->rightLink = removedNode->rightLink;
					removedNode->rightLink->leftLink=removedNode->leftLink;
					free(removedNode);
					return; 
				}
			}while(subHeadNode != (*headNode));
			printf(" ������ ���� �����ϴ�. \n");	
			posNode->startSwitch++;						//������ �������� ���ϸ� ����ġ �������·� ���� 
		}
	}
	
	else{										// node�� 4�� �̻�, Ÿ�� ��� ������ ���� 
		if((*headNode)->data == deleteData && 1==selectPosDelete(headNode,posNode,deleteData)){//headNode�� ������� , leftbalance ����, ������ Ÿ�� �缳�� ���� �Լ� ȣ��
			removedNode=(*headNode);
			(*headNode)=removedNode->rightLink;
			removedNode->leftLink->rightLink=(*headNode);
			(*headNode)->leftLink=removedNode;
			free(removedNode);
		
			if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){                      //������ ������ ��尡 3���ϰ�� Ÿ�ϳ��, �뷱���� �ʱ�ȭ  
					posNode->targetNode=NULL;
					posNode->rightBalance=0;
					posNode->leftBalance=0;
			}			
			
			return;
		}else{																					//4���̻� N��° ��尡 ������� 
			if(1==selectPosDelete(headNode,posNode,deleteData)){								//deleteData ���� Ÿ�� �����ͺ��� ������ ������ Ž�� 
				do{					
					subHeadNode=subHeadNode->rightLink;
					
					if(subHeadNode->data == deleteData){
						removedNode=subHeadNode;
						removedNode->leftLink->rightLink = removedNode->rightLink;
						removedNode->rightLink->leftLink=removedNode->leftLink;
						if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){		//������ ������ ��尡 3���ϰ�� Ÿ�ϳ��, �뷱���� �ʱ�ȭ
								posNode->targetNode=NULL;
								posNode->rightBalance=0;
								posNode->leftBalance=0;
						}
						return;
					}
				}while(subHeadNode != posNode->targetNode);
				posNode->leftBalance++;														//������� ã�� ���ϸ� ������� leftbalance ���� 
			}else{																			//deleteData ���� ũ�ų� ������ ���� Ž��
				if(posNode->targetNode->data == deleteData){								//Ÿ�ϳ�尡 ���� �Ǿ��� ���  
						posNode->targetNode = posNode->targetNode->leftLink;				//Ÿ�ϳ�庸�� ū���� ����ִ� left�� ��ĭ�̵� > �׷��� targetNode���� ���ϱ⶧���� �׷��� ������  
				   }
				do{																			//�������� ������� Ž�� 
					subHeadNode=subHeadNode->leftLink;
						
					if(subHeadNode->data == deleteData){									// ��ġ�ϸ���� 
						removedNode=subHeadNode;
						removedNode->leftLink->rightLink = removedNode->rightLink;
						removedNode->rightLink->leftLink=removedNode->leftLink;
						if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){		//������ ������ ��尡 3���ϰ�� Ÿ�ϳ��, �뷱���� �ʱ�ȭ
								posNode->targetNode=NULL;
								posNode->rightBalance=0;
								posNode->leftBalance=0;
						}
						return;
					}
				}while(subHeadNode != posNode->targetNode);
				posNode->rightBalance++;													//ã�� ���ϸ� �����ʰ� ����  
			}
		} 
	printf("������ ���� �����ϴ�. \n");														//������� 
	}
}
// setting Position_delete
int selectPosDelete(listNode** headNode, positionNode* posNode, element deleteData){
	
	int reSetTarget;											//Ÿ���� �缳���� ������ ���� ����  
	
	if((posNode->targetNode->data) >= deleteData){ 				
		if((posNode->targetNode->data)==deleteData){			//Ÿ���� ���� ����� �ɰ��  
			posNode->targetNode=posNode->targetNode->rightLink;   
			if(posNode->leftBalance==1){						//left ���� �����ǰ� ������ Ž���� �ؾ��� ... 
				posNode->leftBalance=0;
			}
		}
		posNode->leftBalance++;									// ������ ��尡 ������ �����̴� �̸� ���� ����� ���� ����  
		printf("Search to right %d\n",posNode->rightBalance);	
		
		reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));	//���̰� ����  
	
	    if((posNode->leftBalance) > (posNode->rightBalance) && reSetTarget == 2){	//�뷱���� ���̰� 2�� �� ��� Ÿ�� �� �뷱���� �ʱ�ȭ 
			posNode->targetNode = posNode->targetNode->rightLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change Left %d\n",posNode->targetNode->data); 
		}	
		return 1;																	//������ Ž���� �� �ֵ��� �� ���� 
	}else{
        posNode->rightBalance++;								// ���� ��尡 ������ �����̴� �̸� ������ ����� ���� ����
        printf("Search to left : %d \n",posNode->leftBalance);
        
		reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
	
	    if((posNode->leftBalance) < (posNode->rightBalance) && reSetTarget == 2){	//�뷱���� ���̰� 2�� �� ��� Ÿ�� �� �뷱���� �ʱ�ȭ 
			posNode->targetNode = posNode->targetNode->leftLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change Left %d\n",posNode->targetNode->data); 
		}
		return 2;																	//���� Ž���� �� �ֵ��� �� ���� 
	}						
}
// nodeCheck
void nodeCheck(listNode** headNode){
	listNode* subHeadNode = (*headNode);
	if(subHeadNode==NULL){									//������ ���ٴ� ���� ��� 
		printf("����Ʈ�� ���� �������� �ʽ��ϴ�.\n");
		return;
	}
	do{														//��� ��� ��� 
		printf("<- %d ->",subHeadNode->data);
		subHeadNode = subHeadNode->rightLink;
	}while(subHeadNode!= *headNode);
		
	printf("\n");
}

