#include<stdlib.h>

// Stack of numbers

struct stack_longdouble {
	long double val;
	struct stack_longdouble *next;
};

int push_longdouble(struct stack_longdouble **top, long double num) {
	struct stack_longdouble *new_stack = malloc(sizeof(struct stack_longdouble ));
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

long double pop_longdouble(struct stack_longdouble **top) {
	if(*top == NULL) {
		return -1;
	}
	struct stack_longdouble *temp = (*top)->next;
	long double num = (*top)->val;
	free(*top);
	*top = temp;
	return num;
}

int free_double(struct stack_longdouble **top) {
	struct stack_longdouble *temp;
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

int free_char(struct stack_char **top) {
	struct stack_char *temp;
	while(*top != NULL) {
		temp = (*top)->next;
		free(*top);
		*top = temp;
	}
	*top = NULL;
	return 0;
}

