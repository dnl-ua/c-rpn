#include <stack/stack.h> // https://github.com/dnl-ua/c-stack

#include <stdlib.h>
#include <limits.h>

Stack *init_stack(unsigned capacity) 
{
	Stack *stack = (Stack*) malloc(sizeof(Stack));

	if (stack == NULL) {
		exit(EXIT_FAILURE);
	}

	stack->size = 0;
	stack->capacity = capacity;

	stack->array = (int*) malloc(capacity * sizeof(int));

	if (stack->array == NULL) {
		exit(EXIT_FAILURE);
	}

	return stack;
}

void free_stack(Stack **stack) 
{
	free((*stack)->array);
	free(*stack);
}

bool is_empty(Stack* stack) 
{
	if (stack != NULL)
		return !( stack->size );
	return 1;
}

void push(Stack* stack, int value) 
{
	if (stack->size == stack->capacity) {
		stack->array = realloc( stack->array, stack->size+1 );

		if (stack->array == NULL) {
			exit(EXIT_FAILURE);
		}

		stack->capacity++;
	}
	stack->array[ stack->size ] = value;
	stack->size++;
}

int pop(Stack* stack) 
{
	if (!(is_empty(stack))) {
		stack->size--;
		return stack->array[ stack->size ];
	} else return INT_MIN;
}

int top(Stack* stack) 
{
	if (!(is_empty(stack))) {
		return stack->array[ stack->size-1 ];
	} else return INT_MIN;
}
