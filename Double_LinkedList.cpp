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

	 if(subHeadNode == NULL){					//첫 번째 삽입 
	 	 createNode->leftLink = createNode;
		 createNode->rightLink = createNode;
		 *headNode = createNode;
		 printf("First Insert\n");
		 return;
	 }
  
	if(subHeadNode->data > createNode->data){	//헤드노드 보다 작은값 삽입 : 헤드노드 변경 
			createNode->leftLink=(*headNode)->leftLink;	//작은값 삽입 및 헤드노드 변경  
			subHeadNode->leftLink->rightLink=createNode;
			createNode->rightLink=subHeadNode;
			subHeadNode->leftLink=createNode;
			(*headNode)=createNode;
			if(posNode->startSwitch == 2){								 
				if(1==selectPosInset(headNode,posNode,createNode->data));//headNode보다 작은값 삽입시 우측으로 이동 함수가 integer 타입을 반환하기때문에 써줌, right 값 증가 및 2이나 타켓 노드 지정이 필요한경우  
			}else{
				posNode->startSwitch++;		
			}
			printf("Head Change \n");
			return;
	}

 	if(1==selectPosInset(headNode,posNode,createNode->data)){	//N 번째 노드 헤드노드 기준 우측 탐색  삽입  
		do{	
		    if(subHeadNode->data > createNode->data){			//타켓지정될시 항상 중간에 삽입 되기때문에 지정전 : 중간의 삽입코드 지정후 : 해당 코드로만 삽입 
		    	createNode->leftLink=subHeadNode->leftLink;		
		    	subHeadNode->leftLink->rightLink=createNode;
		    	createNode->rightLink=subHeadNode;
		    	subHeadNode->leftLink=createNode;
		    	return;
			}
			subHeadNode=subHeadNode->rightLink; 	
		}while(subHeadNode != *headNode);
  		 
		createNode->leftLink=subHeadNode->leftLink;				//타켓 노드 지정전 마지막노드 삽입 불가하여 마지막 노드삽입하게하는 코드 
 		subHeadNode->leftLink->rightLink=createNode;
  		createNode->rightLink=subHeadNode;
   		subHeadNode->leftLink=createNode;	
	}else{														//N 번째 노드 헤드노드 기준 좌측 탐색  삽입 , 타켓지정전에는 사용 x 마지막 노드 삽입 코드 x  
	    while(1){												//무조건적 삽입 되기때문에 무한루프 가능 
	    	subHeadNode=subHeadNode->leftLink;					
	    	
			if(subHeadNode->data < createNode->data){			//중간 삽입하는 코드 
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

	if( posNode->startSwitch < 2){										// startSwitch 2가 아닐경우 증가 및 우측 탐색 삽입 
		posNode->startSwitch++;
		return 1;
	}
	else if(posNode->targetNode == NULL){								// node개수가 현재 3개이며 return시 삽입이 진행됨으로 target노드 지정 
			posNode->targetNode = (*headNode)->rightLink->rightLink;
			printf("Taget setting %d \n",posNode->targetNode->data);
			return 1;
	}
	
	if((posNode->targetNode->data) > compareData){						// tartget 노드보다 삽입될 데이터가 작을경우 우측 탐색 및 밸런스 증가  
		posNode->rightBalance++;
		printf("Search to right %d\n",posNode->rightBalance);
	    
	    reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
		
	    if((posNode->leftBalance) < (posNode->rightBalance) && reSetTarget == 2){	//밸런스가 깨졌을 경우 왼쪽으로 이동하여 타켓노드 재정의 및 초기화 
			posNode->targetNode = posNode->targetNode->leftLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change right %d\n",posNode->targetNode->data); 
		}
		return 1; 														// 우측 탐색 할 수 있도록 값 리턴  
		
	}else{																//tartget 노드보다 삽입될 데이터가 클경우 좌측 탐색 및 밸런스 증가  
        posNode->leftBalance++;
        printf("Search to left : %d \n",posNode->leftBalance);
        
		reSetTarget = abs((posNode->leftBalance)-(posNode->rightBalance));
		
		if((posNode->leftBalance) > (posNode->rightBalance) && reSetTarget == 2){ //밸런스가 깨졌을 경우 우측으로 이동하여 타켓노드 재정의 및 초기화 
			posNode->targetNode = posNode->targetNode->rightLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;  
  			printf("Target Change left %d\n",posNode->targetNode->data); 
		}
		return 2; 														//좌측 탐색 할 수 있도록 값 리턴 
    }	
}
// Delete
void nodeDelete(listNode** headNode,positionNode* posNode){
	listNode* subHeadNode = *headNode;			
	listNode* removedNode;
	element deleteData;
	
	printf("삭제할 값을 입력하세요\n >> ");
	scanf("%d",&deleteData);
	
	if(deleteData == 999){				//999입력시 전체노드 폭파  
		(*headNode)=NULL;
		printf("Sucess ALL clear\n");
	}
										 
	if(posNode->targetNode==NULL){ 				// node가 3개 이하, 타켓 노드 미지정시 삭제 
			
		if((*headNode)==NULL){							// NODE is empty 
			printf("리스트가 비어 있습니다. \n"); 
			return;
		}
		else if(subHeadNode->data==deleteData){ 		// HeadNode가 삭제 대상 
			 removedNode=subHeadNode;
			 
			 if(subHeadNode->rightLink==subHeadNode){		//HeadNode만 존재할 경우  
				(*headNode)=NULL;
				printf("headNULL RESET\n");
			 }else{											//노드가 2 , 3 개의 헤드노드 삭제시 
				(*headNode)=removedNode->rightLink;		
				removedNode->leftLink->rightLink=(*headNode);
			    subHeadNode->leftLink=removedNode;
				posNode->startSwitch--; 					//노드가 4번째 삽입시 target노드가 지정 될 수 있도록 2 , 3개의 경우 스위치 감소  
			 }
			 free(removedNode);
			 return;
		}
		else{											// 2번 , 3번 노드가 삭제될 경우   
			do{											
				subHeadNode = subHeadNode->rightLink;
				if(subHeadNode->data==deleteData){ 
					posNode->startSwitch--;				//노드가 4번째 삽입시 target노드가 지정 될 수 있도록 2 , 3개의 경우 스위치 감소  
					removedNode = subHeadNode;
					removedNode->leftLink->rightLink = removedNode->rightLink;
					removedNode->rightLink->leftLink=removedNode->leftLink;
					free(removedNode);
					return; 
				}
			}while(subHeadNode != (*headNode));
			printf(" 삭제할 값이 없습니다. \n");	
			posNode->startSwitch++;						//삭제를 진행하지 못하면 스위치 원래상태로 복구 
		}
	}
	
	else{										// node가 4개 이상, 타켓 노드 지정시 삭제 
		if((*headNode)->data == deleteData && 1==selectPosDelete(headNode,posNode,deleteData)){//headNode가 삭제대상 , leftbalance 증가, 삭제시 타켓 재설정 위해 함수 호출
			removedNode=(*headNode);
			(*headNode)=removedNode->rightLink;
			removedNode->leftLink->rightLink=(*headNode);
			(*headNode)->leftLink=removedNode;
			free(removedNode);
		
			if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){                      //삭제를 진행후 노드가 3개일경우 타켓노드, 밸런스값 초기화  
					posNode->targetNode=NULL;
					posNode->rightBalance=0;
					posNode->leftBalance=0;
			}			
			
			return;
		}else{																					//4개이상 N번째 노드가 삭제대상 
			if(1==selectPosDelete(headNode,posNode,deleteData)){								//deleteData 값이 타켓 데이터보다 작으면 오른쪽 탐색 
				do{					
					subHeadNode=subHeadNode->rightLink;
					
					if(subHeadNode->data == deleteData){
						removedNode=subHeadNode;
						removedNode->leftLink->rightLink = removedNode->rightLink;
						removedNode->rightLink->leftLink=removedNode->leftLink;
						if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){		//삭제를 진행후 노드가 3개일경우 타켓노드, 밸런스값 초기화
								posNode->targetNode=NULL;
								posNode->rightBalance=0;
								posNode->leftBalance=0;
						}
						return;
					}
				}while(subHeadNode != posNode->targetNode);
				posNode->leftBalance++;														//삭제노드 찾지 못하면 원래대로 leftbalance 복구 
			}else{																			//deleteData 값이 크거나 같으면 왼쪽 탐색
				if(posNode->targetNode->data == deleteData){								//타켓노드가 삭제 되야할 경우  
						posNode->targetNode = posNode->targetNode->leftLink;				//타켓노드보다 큰값이 들어있는 left로 한칸이동 > 그래야 targetNode까지 비교하기때문에 그래야 삭제됨  
				   }
				do{																			//왼쪽으로 삭제노드 탐색 
					subHeadNode=subHeadNode->leftLink;
						
					if(subHeadNode->data == deleteData){									// 일치하면삭제 
						removedNode=subHeadNode;
						removedNode->leftLink->rightLink = removedNode->rightLink;
						removedNode->rightLink->leftLink=removedNode->leftLink;
						if((*headNode)->rightLink->rightLink->rightLink==(*headNode)){		//삭제를 진행후 노드가 3개일경우 타켓노드, 밸런스값 초기화
								posNode->targetNode=NULL;
								posNode->rightBalance=0;
								posNode->leftBalance=0;
						}
						return;
					}
				}while(subHeadNode != posNode->targetNode);
				posNode->rightBalance++;													//찾지 못하면 오른쪽값 복구  
			}
		} 
	printf("삭제할 값이 없습니다. \n");														//문구출력 
	}
}
// setting Position_delete
int selectPosDelete(listNode** headNode, positionNode* posNode, element deleteData){
	
	int reSetTarget;											//타켓을 재설정할 조건을 비교할 변수  
	
	if((posNode->targetNode->data) >= deleteData){ 				
		if((posNode->targetNode->data)==deleteData){			//타켓이 삭제 대상이 될경우  
			posNode->targetNode=posNode->targetNode->rightLink;   
			if(posNode->leftBalance==1){						//left 값이 증가되고 오른쪽 탐색을 해야함 ... 
				posNode->leftBalance=0;
			}
		}
		posNode->leftBalance++;									// 오른쪽 노드가 삭제될 예정이니 미리 왼쪽 노드의 값을 증가  
		printf("Search to right %d\n",posNode->rightBalance);	
		
		reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));	//차이값 저장  
	
	    if((posNode->leftBalance) > (posNode->rightBalance) && reSetTarget == 2){	//밸런스의 차이가 2가 될 경우 타켓 및 밸런스값 초기화 
			posNode->targetNode = posNode->targetNode->rightLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change Left %d\n",posNode->targetNode->data); 
		}	
		return 1;																	//오른쪽 탐색할 수 있도록 값 리턴 
	}else{
        posNode->rightBalance++;								// 왼쪽 노드가 삭제될 예정이니 미리 오른쪽 노드의 값을 증가
        printf("Search to left : %d \n",posNode->leftBalance);
        
		reSetTarget = abs((posNode->rightBalance)-(posNode->leftBalance));
	
	    if((posNode->leftBalance) < (posNode->rightBalance) && reSetTarget == 2){	//밸런스의 차이가 2가 될 경우 타켓 및 밸런스값 초기화 
			posNode->targetNode = posNode->targetNode->leftLink;
  			posNode->rightBalance = 0;
  			posNode->leftBalance = 0;
			printf("Target Change Left %d\n",posNode->targetNode->data); 
		}
		return 2;																	//왼쪽 탐색할 수 있도록 값 리턴 
	}						
}
// nodeCheck
void nodeCheck(listNode** headNode){
	listNode* subHeadNode = (*headNode);
	if(subHeadNode==NULL){									//없으면 없다는 문구 출력 
		printf("리스트의 값이 존재하지 않습니다.\n");
		return;
	}
	do{														//모든 노드 출력 
		printf("<- %d ->",subHeadNode->data);
		subHeadNode = subHeadNode->rightLink;
	}while(subHeadNode!= *headNode);
		
	printf("\n");
}

