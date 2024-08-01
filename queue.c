#include<stdlib.h>

struct queue {
	double val;
	char op;
	struct queue *next;
};

int enqueue(struct queue **queue, double num, char op) {
	struct queue *new_queue = malloc(sizeof(struct queue));
	if(new_queue == NULL) {
		return -1;
	}
	new_queue->val = num;
	new_queue->op = op;
	new_queue->next = NULL;
	if(*queue == NULL) {
		*queue = new_queue;
	} else {
		struct queue *temp;
		temp = *queue;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_queue;
	}
	return 0;
}

int dequeue(struct queue **queue) {
	if(*queue == NULL) {
		return -1;
	}
	struct queue *temp;
	temp = (*queue)->next;
	free(*queue);
	*queue = temp;
	return 0;
}

int free_queue(struct queue **queue) {
	struct queue *temp;
	while(*queue != NULL) {
		temp = (*queue)->next;
		free(*queue);
		*queue = temp;
	}
	*queue = NULL;
	return 0;
}
