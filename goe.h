#pragma once
#include<stdio.h>
#include<stdlib.h> 
#include<stack>
#define LENGTH 8
struct GOETreeBinary{
	int configuration[LENGTH];
	GOETreeBinary* son[2];
	GOETreeBinary* father;
};
struct StateNode{
	int configuration[LENGTH];
	StateNode* next;
};

struct GOEQueueNode {
	GOETreeBinary* element;
	GOEQueueNode* next;
};

struct GOEQueue {
	int size;
	GOEQueueNode* head;
	GOEQueueNode* tail;
};

GOETreeBinary* initGOENode();
int recordConfiguration(int* configuration, StateNode* head);
GOETreeBinary* createGOERoot(int* rules, StateNode* head);
GOETreeBinary* createGOETree(int* rules, GOETreeBinary* node, StateNode* head, GOEQueue* stack);

GOEQueue* initGOEQueue(GOETreeBinary* elem)
{
	GOEQueue* queue = (GOEQueue*)malloc(sizeof(GOEQueue));
	GOEQueueNode* node = (GOEQueueNode*)malloc(sizeof(GOEQueueNode));
	node->next = NULL;
	node->element = elem;
	//队头有元素
	queue->head = node;
	//队尾为空
	queue->tail = node->next;
	return queue;
}

void pushGOEQueue(GOEQueue* queue, GOETreeBinary* elem)
{
	GOEQueueNode* node = (GOEQueueNode*)malloc(sizeof(GOEQueueNode));
	node->element = elem;
	queue->tail = node;
	queue->tail = node->next;
	
}

GOETreeBinary* popGOEQueue(GOEQueue* queue)
{
	//头节点不为空则队列不为空
	if (queue->head)
	{
		GOEQueueNode* temp = queue->head;
		queue->head = queue->head->next;
		return temp->element;
	}
	else
	{
		return nullptr;
	}

}