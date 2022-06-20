#pragma once
#include<stdio.h>
#include<stdlib.h> 
#define LENGTH 8
struct GOETreeBinary {
	int configuration[LENGTH];
	GOETreeBinary* son[2];
	GOETreeBinary* father;
};
struct StateNode {
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
void getRules(int* a);
GOETreeBinary* initGOENode();
int recordConfiguration(int* configuration, StateNode* head);
GOETreeBinary* createGOERoot(int* rules, StateNode* head);
GOETreeBinary* createGOETree(int* rules, GOETreeBinary* node, StateNode* head, GOEQueue* queue);

GOEQueue* initGOEQueue();
void pushGOEQueue(GOEQueue* queue, GOETreeBinary* elem);
GOETreeBinary* popGOEQueue(GOEQueue* queue);
