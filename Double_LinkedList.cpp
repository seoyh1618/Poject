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
			case 4: printf(" 프로그램을 종료합니다. \n");
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
			default : printf("값이 잘못 입력 되었습니다. 다시 선택해주세요\n");
		}
	}

	return 0;
}
// Menu Print 
int selectOption(void){
	int selectOption;
	printf("\n\t\t메뉴\n");
	printf("1. 삽입  2. 삭제  3. 확인  4. 종료\n");
	printf("메뉴를 선택하세요 : ");
	scanf("%d",&selectOption);
	printf("\n");
	return selectOption;
}
// Node Create
listNode* nodeCreation(void){
	listNode* createNode = (listNode* )malloc(sizeof(listNode));
	element data;
	printf("삽입할 정수를 입력하세요\n");
	printf(" >>");
	scanf("%d",&data);
	createNode->data = data;
	createNode->leftLink=NULL;
	createNode->rightLink=NULL;
	
	printf("정수가 삽입 되었습니다. \n");
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
	 int directValue;
	 if(subHeadNode == NULL){	//NULL 
	 	 createNode->leftLink = createNode;
		 createNode->rightLink = createNode;
		 *headNode = createNode;
		 printf("first insert\n");
		 return;
	 }

	if(subHeadNode->data > createNode->data){	//HEAD CHANGE
			createNode->leftLink=(*headNode)->leftLink;
			subHeadNode->leftLink->rightLink=createNode;
			createNode->rightLink=subHeadNode;
			subHeadNode->leftLink=createNode;
			(*headNode)=createNode;
			if(posNode->startSwitch == 2){//수정 
				if(1==selectPosInset(headNode,posNode,createNode->data));		
			}else{
				posNode->startSwitch++;
			}
			printf("Head Change \n");
			return;
	}

 	if(1==selectPosInset(headNode,posNode,createNode->data)){//right MIDDLE
		do{	
		    if(subHeadNode->data > createNode->data){
		    	createNode->leftLink=subHeadNode->leftLink;
		    	subHeadNode->leftLink->rightLink=createNode;
		    	createNode->rightLink=subHeadNode;
		    	subHeadNode->leftLink=createNode;
		    	return;
			}
			subHeadNode=subHeadNode->rightLink; 	
		}while(subHeadNode != *headNode);
  		
		createNode->leftLink=subHeadNode->leftLink;
 		subHeadNode->leftLink->rightLink=createNode;
  		createNode->rightLink=subHeadNode;
   		subHeadNode->leftLink=createNode;	
   		
	}else{//left 
	    while(1){
	    	subHeadNode=subHeadNode->leftLink;	
	    	
			if(subHeadNode->data < createNode->data){
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

	if( posNode->startSwitch < 2){
		posNode->startSwitch++;
		return 1;
	}
	else if(posNode->targetNode == NULL){
			posNode->targetNode = (*headNode)->rightLink->rightLink;
			printf("Taget setting %d \n",posNode->targetNode->data);
			return 1;
	}
	
	if((posNode->targetNode->data) > compareData){
		posNode->rightBalance++;
		printf("Search to right %d\n",posNode->rightBalance);
	    
	    reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
		
	    if((posNode->leftBalance) < (posNode->rightBalance) && reSetTarget == 2){
			posNode->targetNode = posNode->targetNode->leftLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change right %d\n",posNode->targetNode->data); 
		}
		return 1; 
		
	}else{
        posNode->leftBalance++;
        printf("Search to left : %d \n",posNode->leftBalance);
        
		reSetTarget = abs((posNode->leftBalance)-(posNode->rightBalance));
		
		if((posNode->leftBalance) > (posNode->rightBalance) && reSetTarget == 2){
			posNode->targetNode = posNode->targetNode->rightLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;  
  			printf("Target Change left %d\n",posNode->targetNode->data); 
		}
		return 2; 
    }	
}
// Delete
void nodeDelete(listNode** headNode,positionNode* posNode){
	listNode* subHeadNode = *headNode;
	listNode* removedNode;
	element deleteData;
	
	printf("삭제할 값을 입력하세요\n >> ");
	scanf("%d",&deleteData);
	/*if(deleteData == 0){//Node clear
		(*headNode)=NULL;
		printf("Sucess ALL clear\n");1111
	}*/
			
	if(posNode->targetNode==NULL){ // 3개 이하의 경우  
			
		if((*headNode)==NULL){//NODE is empty 
			printf("리스트가 비어 있습니다. \n"); 
			return;
		}
		else if(subHeadNode->data==deleteData){//HeadNode가 삭제 대상 
			 removedNode=subHeadNode;
			 
			 if(subHeadNode->rightLink==subHeadNode){//HeadNode만 존재할 경우  
				(*headNode)=NULL;
				printf("headNULL RESET\n");
			 }else{//headNode외 다른 리스트또한 존재할 경우  
				(*headNode)=removedNode->rightLink;
				removedNode->leftLink->rightLink=(*headNode);
			    subHeadNode->leftLink=removedNode;
				posNode->startSwitch--; 
			 }
			 free(removedNode);
			 return;
		}
		else{
			do{									//3,2번째 노드삭제
				subHeadNode = subHeadNode->rightLink;
				if(subHeadNode->data==deleteData){ 
					posNode->startSwitch--;
					removedNode = subHeadNode;
					removedNode->leftLink->rightLink = removedNode->rightLink;
					removedNode->rightLink->leftLink=removedNode->leftLink;
					free(removedNode);
					return; 
				}
			}while(subHeadNode != (*headNode));
			printf(" 삭제할 값이 없습니다. \n");	
			posNode->startSwitch++;
		}
	}
	// 4개이상 
	else{
		if((*headNode)->data == deleteData && 1==selectPosDelete(headNode,posNode,deleteData)){//4개이상 첫번째 값 삭제  
			removedNode=(*headNode);
			(*headNode)=removedNode->rightLink;
			removedNode->leftLink->rightLink=(*headNode);
			(*headNode)->leftLink=removedNode;
			free(removedNode);
		
			if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){
					posNode->targetNode=NULL;
					posNode->rightBalance=0;
					posNode->leftBalance=0;
			}			
			
			return;
		}else{
									//4개이상 첫번째 값이 아님  
			if(1==selectPosDelete(headNode,posNode,deleteData)){
				
				do{					
					subHeadNode=subHeadNode->rightLink;
					
					if(subHeadNode->data == deleteData){
						removedNode=subHeadNode;
						removedNode->leftLink->rightLink = removedNode->rightLink;
						removedNode->rightLink->leftLink=removedNode->leftLink;
						if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){
								posNode->targetNode=NULL;
								posNode->rightBalance=0;
								posNode->leftBalance=0;
						}
						return;
					}
				}while(subHeadNode != posNode->targetNode);
					posNode->leftBalance++;	
			}else{
			if(posNode->targetNode->data == deleteData){
					posNode->targetNode = posNode->targetNode->leftLink;	
				}
				do{					
					subHeadNode=subHeadNode->leftLink;
					
					if(subHeadNode->data == deleteData){
						removedNode=subHeadNode;
						removedNode->leftLink->rightLink = removedNode->rightLink;
						removedNode->rightLink->leftLink=removedNode->leftLink;
						if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){
								posNode->targetNode=NULL;
								posNode->rightBalance=0;
								posNode->leftBalance=0;
						}
						return;
					}
				}while(subHeadNode != posNode->targetNode);
					posNode->rightBalance++;			
			}
		} 
	printf("삭제할 값이 없습니다. \n");
	}
}
// setting Position_delete
int selectPosDelete(listNode** headNode, positionNode* posNode, element deleteData){
	
	int reSetTarget;
	
	if((posNode->targetNode->data) >= deleteData){//target 노드를 삭제할 경우 
		if((posNode->targetNode->data)==deleteData){
			posNode->targetNode=posNode->targetNode->rightLink;
			if(posNode->leftBalance==1){
				posNode->leftBalance=0;
			}
		}
		posNode->leftBalance++;
		printf("Search to right %d\n",posNode->rightBalance);
		
		reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
	
	    if((posNode->leftBalance) > (posNode->rightBalance) && reSetTarget == 2){
			posNode->targetNode = posNode->targetNode->rightLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change Left %d\n",posNode->targetNode->data); 
		}
		return 1;
	}else{
        posNode->rightBalance++;
        printf("Search to left : %d \n",posNode->leftBalance);
        
		reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
	
	    if((posNode->leftBalance) < (posNode->rightBalance) && reSetTarget == 2){
			posNode->targetNode = posNode->targetNode->leftLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change Left %d\n",posNode->targetNode->data); 
		}
		return 2;
	}
}
// nodeCheck
void nodeCheck(listNode** headNode){
	listNode* subHeadNode = (*headNode);
	if(subHeadNode==NULL){
		printf("리스트의 값이 존재하지 않습니다.\n");
		return;
	}
	do{
		printf("<- %d ->",subHeadNode->data);
		subHeadNode = subHeadNode->rightLink;
	}while(subHeadNode!= *headNode);
		
	printf("\n");
}
