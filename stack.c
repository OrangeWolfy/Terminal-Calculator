#include<stdlib.h>
#include<limits.h>

// Stack of numbers

struct stack_double {
	double val;
	struct stack_double *next;
};

int push_double(struct stack_double **top, double num) {
	struct stack_double *new_stack = malloc(sizeof(struct stack_double ));
	if(new_stack == NULL) {
		return -1;
	}
	new_stack->val = num;
	new_stack->next = NULL;
	if(*top == NULL) {
		*top = new_stack;
	} else {
		new_stack->next = *top;
		*top = new_stack;
	}
	return 0;
}

double pop_double(struct stack_double **top) {
	if(*top == NULL) {
		return INT_MIN;
	}
	struct stack_double *temp = (*top)->next;
	double num = (*top)->val;
	free(*top);
	*top = temp;
	return num;
}

int free_stack_double(struct stack_double **top) {
	struct stack_double *temp;
	while(*top != NULL) {
		temp = (*top)->next;
		free(*top);
		*top = temp;
	}
	*top = NULL;
	return 0;
}

// Stack of operators characters

struct stack_char {
	char op;
	struct stack_char *next;
};

int push_char(struct stack_char **top, char op) {
	struct stack_char *new_stack = malloc(sizeof(struct stack_char));
	if(new_stack == NULL) {
		return -1;
	}
	new_stack->op = op;
	new_stack->next = NULL;
	if(*top == NULL) {
		*top = new_stack;
	} else {
		new_stack->next = *top;
		*top = new_stack;
	}
	return 0;
}

char pop_char(struct stack_char **top) {
	if(*top == NULL) {
		return '\0';
	}
	struct stack_char *temp = (*top)->next;
	char op = (*top)->op;
	free(*top);
	*top = temp;
	return op;
}

int free_stack_char(struct stack_char **top) {
	struct stack_char *temp;
	while(*top != NULL) {
		temp = (*top)->next;
		free(*top);
		*top = temp;
	}
	*top = NULL;
	return 0;
}

