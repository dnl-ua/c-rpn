#pragma once

typedef enum { false, true } bool;

typedef struct {
	int *array;
	int size;
	unsigned capacity;
} Stack;

Stack *init_stack(unsigned);
void free_stack(Stack**);
bool is_empty(Stack*);
void push(Stack*, int);
int pop(Stack*);
int top(Stack*);
