#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <limits.h>
#include"stack.c"
#include"queue.c"

// Terminal calculator as alias command
// Execute this file and create an alias to use anywhere

int operator_precedence(char arg);
struct queue *infix_to_postfix(char arg[]);
double evaluate_postfix(struct queue **output_queue);

int main(int argc, char* argv[]) {
	// Check if no arguments were given
	if(argc < 2) {
		printf("No argument given\n");
		return 1;
	}
	// Print help menu if requested
	if(strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("Usage: calc [OPERATION]\naddition, subtraction, multiplication, division and or modulus.\n");
        printf("Solve the [OPERATION] given.\n");
        printf("The [OPERATION] given must only contain:\n");
        printf("\t-numbers\n\t-addition symbol +\n\t-subtraction symbol -\n\t-multiplication symbol * or x\n\t-division symbol /\n\t-modulus symbol %%\n\t-open and closed parentheses ( )\n");
        printf("\nFor more information: <https://github.com/OrangeWolfy/Terminal-Calculator>\n");
		return 0;
	}


	struct queue *output_queue;
	double res;

	for(int i = 1; i < argc; i++) {
		output_queue = infix_to_postfix(argv[i]);
		if(output_queue == NULL) {
			return 1;
		}

		res = evaluate_postfix(&output_queue);
		if(res == INT_MIN) {
			return 1;
		}
		printf("%s = %.3f\n", argv[i], res);
	}

    return 0;
}

// Return the value of precedence
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
		case '^':
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

// Transform a infix to postfix operation with the shunting yard algorithm and return the transformation in a queue
struct queue *infix_to_postfix(char arg[]) {
	struct queue *output_queue = NULL;
	struct stack_char *operator_stack = NULL;
	double num = 0;
	int precedence;
	char c, *endptr;
	
	// Loop while string is not at the end
	while(*arg != '\0') {
		// Get decimal or hexadecimal number and point to the next non number character
		num = strtod(arg, &arg);
		if(!(num == 0 && *arg != '0')) {
			if(enqueue(&output_queue, num, '\0') == -1) {
				printf("Fail to enque output in line %d\n", __LINE__);
				goto cleanup;
			}
		}
		// Check if string is at the end
		if(*arg == '\0') { 
			break;
		}
		if(*arg == '(') {
		// Push if open parentheses
			if(push_char(&operator_stack, *arg) == -1) {
				printf("Fail to push operator in line %d\n", __LINE__);
				goto cleanup;
			}
		} else if(*arg == ')') {
		// Empty operator stack until an open parentheses is found
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
			if(c != '(') {
				printf("No open parentheses before closed parentheses in the operation\n");
				goto cleanup;
			}
		} else {
		// Check if the argument is a valid operator
			precedence = operator_precedence(*arg);
			if(precedence == -1) {
				printf("Invalid operator \'%c\'\n", *arg);
				goto cleanup;
			}
			// Enqueue a 0 if the operation starts with an operator to evaluate postfix notation correctly
			if(output_queue == NULL) {
				if(enqueue(&output_queue, 0, '\0') == -1) {
					printf("Fail to enque output in line %d\n", __LINE__);
					goto cleanup;
				}
			}
			// Empty operator stack while the current operator has lower or equal precedence to the top of the operator stack
			while(operator_stack != NULL && precedence <= operator_precedence(operator_stack->op)) {
				c = pop_char(&operator_stack);
				if(enqueue(&output_queue, -1, c) == -1)	{
					printf("Fail to enque output in line %d\n", __LINE__);
					goto cleanup;
				}
			}
			if(push_char(&operator_stack, *arg) == -1) {
				printf("Fail to push operator in line %d\n", __LINE__);
				goto cleanup;
			}
		}
		arg++;
	}
	// Empty operator stack to the output queue
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

// Evaluate the postfix operation in queue and return the final answer for the operation
double evaluate_postfix(struct queue **output_queue) {
	struct stack_double *solve_stack = NULL;
	double num1, num2;

	if(output_queue == NULL) {
		return INT_MIN;
	}
	// Loop until output queue is empty or an error occurs
	while(*output_queue != NULL) {
		if((*output_queue)->op == '\0') {
		// Push to the solved stack if it is a number
			if (push_double(&solve_stack, (*output_queue)->val) == -1) {
				printf("Fail to push number in line %d\n", __LINE__);
				goto cleanup;
			}
		} else {
		// If current queue is an operator, pop the first two numbers from the solved stack, evaluate below and push the result
			num2 = pop_double(&solve_stack); 
			num1 = pop_double(&solve_stack);
			if(num1 == INT_MIN || num2 == INT_MIN) {
				printf("Invalid operation\n");
				goto cleanup;
			}
			switch((*output_queue)->op) {
				case '+':
					if (push_double(&solve_stack, num1 + num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '-':
					if (push_double(&solve_stack, num1 - num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '*':
				case 'x':
					if (push_double(&solve_stack, num1 * num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '/':
					if(num2 == 0) {
						printf("Division by 0 undefined\n");
						goto cleanup;
					}
					if (push_double(&solve_stack, num1 / num2) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '%':
					if(num2 == 0) {
						printf("Division by 0 undefined\n");
						goto cleanup;
					}
					if (push_double(&solve_stack, (double)((long long)num1 % (long long)num2)) == -1) {
						printf("Fail to push number in line %d\n", __LINE__);
						goto cleanup;
					}
					break;
				case '^':
					double pow = num1;
					for(int i = 1; i < num2; i++) {
						num1 *= pow;
					}
					if (push_double(&solve_stack, num1) == -1) {
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
	if(solve_stack == NULL) {
		goto cleanup;
	}

	num1 = pop_double(&solve_stack);
	return num1;

cleanup:
	free_stack_double(&solve_stack);
	free_queue(output_queue);
	return INT_MIN;
}

