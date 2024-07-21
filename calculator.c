#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"stack.c"
#include"queue.c"

// Terminal calculator as alias command
// Execute this file and create an alias to use anywhere

int operator_precedence(char arg) {
	int operator_val;
	switch(arg) {
		case '+':
		case '-':
			operator_val = 1;
			break;
		case '*':
		case '/':
		case '%':
			operator_val = 2;
			break;
		default:
			operator_val = -1;
			break;
	}
	return operator_val;
}

struct queue *infix_to_postfix(char arg[]) {
	struct queue *output_queue = NULL;
	struct stack_char *operator_stack = NULL;
	long double num = 0;
	int precedence;

	for(int i = 0; arg[i] != '\0'; i++) {
		if((int)arg[i] >= 48 && (int)arg[i] <= 57) {
			num += arg[i] - 48;
			num *= 10;
		}
		else {
			num /= 10;
			if(enqueue(&output_queue, num, '\0') == -1)
				return NULL;
			num = 0;

			precedence = operator_precedence(arg[i]);
			if(precedence == -1)
				return NULL;
			if(operator_stack != NULL) {
				if(precedence > operator_precedence(operator_stack->op)) {
					if(push_char(&operator_stack, arg[i]) == -1)
						return NULL;
				} else {
					while(operator_stack != NULL) {
						char op = pop_char(&operator_stack);
						if(enqueue(&output_queue, -1, op) == -1)
							return NULL;
					}
					if(push_char(&operator_stack, arg[i]) == -1)
						return NULL;
				}
			} else {
				if(push_char(&operator_stack, arg[i]) == -1)
					return NULL;
			}
		}
	}
	num /= 10;
	if(enqueue(&output_queue, num, '\0') == -1)
		return NULL;
	num = 0;
	while(operator_stack != NULL) {
		char op = pop_char(&operator_stack);
		if(enqueue(&output_queue, -1, op) == -1)
			return NULL;
	}

	while(output_queue != NULL) {
		if(output_queue->val != -1)
			printf("%.1Lf ", output_queue->val);
		else printf("%c ", output_queue->op);
		dequeue(&output_queue);
	}
	printf("\n");

	return output_queue;
}

void evaluate_postfix(char eval[]) {

}

int main(int argc, char* argv[]){
	if(argc < 2) {
		return -1;
	}
	struct queue *success;
	success = infix_to_postfix(argv[1]);
	if(success == NULL) {
		//printf("error\n");
		//return -1;
	}
    return 0;
}
