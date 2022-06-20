#include"goe.h"
void getRules(int* a) {
	int i;
	char* rules;
	scanf_s("%s", &rules);
	for (i = LENGTH - 1; i >= 0; i--) {
		a[i] = (int)rules[i];
	}
}

GOETreeBinary* initGOENode() {
	GOETreeBinary* node = (GOETreeBinary*)malloc(sizeof(GOETreeBinary));;
	int i;
	for (i = 0; i < LENGTH; i++) {
		node->configuration[i] = 0;
	}
	node->father = NULL;
	node->son[0] = NULL;
	node->son[1] = NULL;
	return node;
}

int recordConfiguration(int* configuration, StateNode* head) {
	StateNode* p = head;
	int i;
	while (p->next) {
		for (i = 0; i < LENGTH; i++) {
			if (configuration[i] != p->next->configuration[i]) {
				break;
			}
		}
		if (i == LENGTH) {
			//0指该状态已经存在
			return 0;
		}
		else{
			p = p->next;
		}
	}
	//找不到相同状态，记录
	StateNode* newNode = (StateNode*)malloc(sizeof(StateNode));
	for (i = 0; i < LENGTH; i++) {
		newNode->configuration[i] = configuration[i];
	}
	newNode->next = nullptr;
	p->next = newNode;
	//1指状态已经成功记录
	return 1;

}

GOETreeBinary* createGOERoot(int* rules, StateNode* head) {
	GOETreeBinary* root = initGOENode();
	int i;
	for (i = 0; i < LENGTH; i++) {
		//rules[5] = 1指 101 映射到 1
		if (rules[i] == 1) {
			//例：configuration[7] = 1 指该节点中有111这一状态
			//例：configuration[6] = 0 指该节点中无110这一状态
			root->configuration[i] = 0;
			head->configuration[i] = 0;
		}
		else if (rules[i] == 0) {
			root->configuration[i] = 1;
			head->configuration[i] = 1;
		}
	}
	//记录当前状态，该状态为第一个
	//recordConfiguration(root->configuration, head);
	//使用队列实现层序遍历
	GOEQueue* queue = initGOEQueue();
	pushGOEQueue(queue, root);
	//此时队列中有root
	while (queue->head!=queue->tail) {
		GOETreeBinary* temp = popGOEQueue(queue);
		createGOETree(rules, temp, head, queue);
	}

	return root;
}

GOETreeBinary* createGOETree(int* rules, GOETreeBinary* node, StateNode* head, GOEQueue* queue) {
	int i;
	//如果该块为空，则存在GOE
	int judge = 0;
	for (i = 0; i < LENGTH; i++) {
		if (node->configuration[i] == 1) {
			judge = 1;
		}
	}
	if (judge == 0) {
		//空块返回
		//输出路径
		GOETreeBinary* p = node;
		while (p->father) {
			if (p == p->father->son[0]) {
				printf("0");
			}
			else if (p == p->father->son[1]) {
				printf("1");
			}
			p = p->father;
		}
		printf("\n");
		return nullptr;
	}

	//如果与已知状态相同，则不创建树，什么也不做
	//如果该状态不存在，则加入链表并且创建树
	if (recordConfiguration(node->configuration, head) == 1) {
		GOETreeBinary* zero = initGOENode();
		GOETreeBinary* one = initGOENode();
		zero->father = node;
		one->father = node;
		for (i = 0; i < LENGTH; i++) {
			if (node->configuration[i] == 1) {
				int index = (i % (LENGTH / 2)) * 2;
				if (rules[index] == 0) {
					zero->configuration[index] = 1;
				}
				else if (rules[index] == 1) {
					one->configuration[index] = 1;
				}
				index++;
				if (rules[index] == 0) {
					zero->configuration[index] = 1;
				}
				else if (rules[index] == 1) {
					one->configuration[index] = 1;
				}
			}
		}
		node->son[0] = zero;
		node->son[1] = one;
		pushGOEQueue(queue, zero);
		pushGOEQueue(queue, one);
	}
	return node;
}

GOEQueue* initGOEQueue()
{
	GOEQueue* queue = (GOEQueue*)malloc(sizeof(GOEQueue));
	GOEQueueNode* node = (GOEQueueNode*)malloc(sizeof(GOEQueueNode));
	node->next = NULL;
	//队头
	queue->head = node;
	//队尾
	queue->tail = node;
	return queue;
}


void pushGOEQueue(GOEQueue* queue, GOETreeBinary* elem)
{
	GOEQueueNode* node = (GOEQueueNode*)malloc(sizeof(GOEQueueNode));
	node->element = elem;
	queue->tail->next = node;
	queue->tail = node;

}

GOETreeBinary* popGOEQueue(GOEQueue* queue)
{
	if (queue->head->next)
	{
		GOEQueueNode* temp = queue->head->next;
		queue->head = queue->head->next;
		return temp->element;
	}
	else
	{
		return nullptr;
	}

}
