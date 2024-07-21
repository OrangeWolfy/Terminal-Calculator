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
		case 'x':
		case '/':
		case '%':
			operator_val = 2;
			break;
		case '(':
			operator_val = 10;
			break;
		case ')':
			operator_val = 11;
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
		else if ((precedence = operator_precedence(arg[i])) != -1){
			num /= 10;
			if(enqueue(&output_queue, num, '\0') == -1) {
				printf("Fail to enque output in line %d\n", __LINE__);
				free_stack_char(&operator_stack);
				free_queue(&output_queue);
				return NULL;
			}
			num = 0;

			while(operator_stack != NULL && precedence <= operator_precedence(operator_stack->op)) {
				char c = pop_char(&operator_stack);
				if(enqueue(&output_queue, -1, c) == -1)	{
					printf("Fail to enque output in line %d\n", __LINE__);
					free_stack_char(&operator_stack);
					free_queue(&output_queue);
					return NULL;
				}
			}
			if(push_char(&operator_stack, arg[i]) == -1) {
				printf("Fail to push operator in line %d\n", __LINE__);
				free_stack_char(&operator_stack);
				free_queue(&output_queue);
				return NULL;
			}
		} else {
			printf("Invalid operator = \'%c\', type \'calc --help\' to check valid operators\n", arg[i]);
			free_stack_char(&operator_stack);
			free_queue(&output_queue);
			return NULL;
		}
	}
	num /= 10;
	if(enqueue(&output_queue, num, '\0') == -1) {
		printf("Fail to enque output in line %d\n", __LINE__);
		free_stack_char(&operator_stack);
		free_queue(&output_queue);
		return NULL;
	}
	num = 0;
	while(operator_stack != NULL) {
		char op = pop_char(&operator_stack);
		if(enqueue(&output_queue, -1, op) == -1) {
			printf("Fail to enque output in line %d\n", __LINE__);
			free_stack_char(&operator_stack);
			free_queue(&output_queue);
			return NULL;
		}
	}

	return output_queue;
}

void evaluate_postfix(char eval[]) {

}

int main(int argc, char* argv[]){
	if(argc < 2) {
		return -1;
	}
	if(strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("Usage: calc [OPERATION]\naddition, subtraction, multiplication, division and or modulus.\n");
        printf("Solve the [OPERATION] given.\n");
        printf("The [OPERATION] given must only contain:\n");
        printf("\t-numbers\n\t-addition symbol +\n\t-subtraction symbol -\n\t-multiplication symbol * or x\n\t-division symbol /\n\t-modulus symbol %%\n\t-open and closed parentheses ()\n");
        printf("\nFor more information: <https://github.com/OrangeWolfy/Terminal-Calculator>\n");
		return 0;
	}
	struct queue *output_queue;
	output_queue = infix_to_postfix(argv[1]);
	if(output_queue == NULL) {
		return -1;
	}

	while(output_queue != NULL) {
		if(output_queue->val != -1)
			printf("%.1Lf ", output_queue->val);
		else printf("%c ", output_queue->op);
		dequeue(&output_queue);
	}
	printf("\n");

    return 0;
}
