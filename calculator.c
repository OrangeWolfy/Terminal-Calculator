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
		case ')':
			operator_val = 0;
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
	int precedence, parentheses_flag = 0;

	for(int i = 0; arg[i] != '\0'; i++) {
		if(((int)arg[i] >= 48 && (int)arg[i] <= 57) || arg[i] == '(') {
			if(arg[i] != '(') {
				num += arg[i] - 48;
				num *= 10;
			} else {
				push_char(&operator_stack, arg[i]);
			}
		} else if ((precedence = operator_precedence(arg[i])) != -1) {
			num /= 10;
			if(enqueue(&output_queue, num, '\0') == -1) {
				printf("Fail to enque output in line %d\n", __LINE__);
				goto cleanup;
			}
			num = 0;

			char c;
			if(arg[i] != ')') {
				while(operator_stack != NULL && precedence <= operator_precedence(operator_stack->op)) {
					c = pop_char(&operator_stack);
					if(c == '\0') {
						printf("Operator stack empty in line %d\n", __LINE__);
						goto cleanup;
					}
					if(enqueue(&output_queue, -1, c) == -1)	{
						printf("Fail to enque output in line %d\n", __LINE__);
						goto cleanup;
					}
				}
			} else {
				while(operator_stack != NULL) {
					c = pop_char(&operator_stack);
					if(c == '(') {
						break;
					}
					if(enqueue(&output_queue, -1, c) == -1)	{
						printf("Fail to enque output in line %d\n", __LINE__);
						goto cleanup;
					}
				}
				if(c == '\0') {
					printf("No open parentheses before closed parentheses in the operation\n");
					goto cleanup;
				}
				i++;
			}
			if(push_char(&operator_stack, arg[i]) == -1) {
				printf("Fail to push operator in line %d\n", __LINE__);
				goto cleanup;
			}
		} else {
			printf("Invalid \'%c\' operator.\nType \'calc --help\' for more information\n", arg[i]);
			goto cleanup;
		}
	}

	num /= 10;
	if(enqueue(&output_queue, num, '\0') == -1) {
		printf("Fail to enque output in line %d\n", __LINE__);
		goto cleanup;
	}
	num = 0;

	while(operator_stack != NULL) {
		char op = pop_char(&operator_stack);
		if(enqueue(&output_queue, -1, op) == -1) {
			printf("Fail to enque output in line %d\n", __LINE__);
			goto cleanup;
		}
	}

	return output_queue;

cleanup:
	free_stack_char(&operator_stack);
	free_queue(&output_queue);
	return NULL;
}

long double evaluate_postfix(struct queue **output_queue) {
	struct stack_longdouble *solve_stack = NULL;
	long double num1, num2;

	while(*output_queue != NULL) {
		if((*output_queue)->op == '\0') {
			if (push_longdouble(&solve_stack, (*output_queue)->val) == -1) {
				printf("Fail to push number in line %d\n", __LINE__);
				goto cleanup;
			}
		} else {
			num2 = pop_longdouble(&solve_stack); 
			if(num2 == -1) {
				printf("Fail to pop, number stack empty in line %d\n", __LINE__);
				goto cleanup;
			}
				
			num1 = pop_longdouble(&solve_stack);
			if(num1 == -1) {
				printf("Fail to pop, number stack empty in line %d\n", __LINE__);
				goto cleanup;
			}

			switch((*output_queue)->op) {
				case '+':
					if (push_longdouble(&solve_stack, num1 + num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '-':
					if (push_longdouble(&solve_stack, num1 - num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '*':
				case 'x':
					if (push_longdouble(&solve_stack, num1 * num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '/':
					if (push_longdouble(&solve_stack, num1 / num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '%':
					if (push_longdouble(&solve_stack, (long double)((long long)num1 % (long long)num2)) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				default:
					printf("Invalid stack in line %d", __LINE__);
					goto cleanup;
					break;
			}
		}
		dequeue(output_queue);
		
	}

	return solve_stack->val;

cleanup:
	free_stack_longdouble(&solve_stack);
	free_queue(output_queue);
	return -1;
}

void print_output_queue(struct queue *output_queue) {
	while(output_queue != NULL) {
		if(output_queue->val != -1)
			printf("%.3Lf ", output_queue->val);
		else printf("%c ", output_queue->op);
		output_queue = output_queue->next;
	}
	printf("\n");
}

int main(int argc, char* argv[]){
	if(argc < 2) {
		return -1;
	}
	if(strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("Usage: calc [OPERATION]\naddition, subtraction, multiplication, division and or modulus.\n");
        printf("Solve the [OPERATION] given.\n");
        printf("The [OPERATION] given must only contain:\n");
        printf("\t-numbers\n\t-addition symbol +\n\t-subtraction symbol -\n\t-multiplication symbol * or x\n\t-division symbol /\n\t-modulus symbol %%\n\t-open and closed parentheses ( )\n");
        printf("\nFor more information: <https://github.com/OrangeWolfy/Terminal-Calculator>\n");
		return 0;
	}

	struct queue *output_queue;
	output_queue = infix_to_postfix(argv[1]);
	if(output_queue == NULL) {
		return -1;
	}
	
	print_output_queue(output_queue);

	printf("%.3Lf\n", evaluate_postfix(&output_queue));

    return 0;
}
