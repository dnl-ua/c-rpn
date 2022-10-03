#include "rpn.h"
#include "c-stack/Stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int
check_priority( char c ) 
{
	int result;

	switch (c) {
		case ')':
			result = -1;
			break;
		case '(':
			result = 0;
			break;
		case '+':
		case '-':
			result = 1;
			break;
		case '*':
		case '/':
			result = 2;
			break;
		default:
			result -2;
			break;
	}

	return result;
}

static int
execute_operation(char operation, double n1, double n2) {
	int result; // ``single exit`` or whatever

	switch (operation) {
		case '+':
			result = n2 + n1;
			break;
		case '-':
			result = n2 - n1;
			break;
		case '*':
			result = n2 * n1;
			break;
		case '/':
			if (n1 != 0) result = n2 / n1;
			else exit(EXIT_FAILURE);
			break;
		default:
			break;
	}

	return result;
}

static void
stack_to_string(Stack *stack, char **str)
{
	while (!is_empty(stack)) {
		sprintf(*str, "%s %c", *str, pop(stack));
	}
}

char*
parse(char* s)
{
	Stack *operators = init_stack(strlen(s));
	char *output = (char*)malloc( strlen(s) * sizeof(char) );

	if (output == NULL) {
		exit(EXIT_FAILURE);
	}

	int i = -1;
	while (s[++i]) {
		if (s[i] != ' ') {
			if (isdigit(s[i])) {
				sprintf(output, "%s%c", output, s[i]);
			} else {
				sprintf(output, "%s ", output);

				if (s[i] == ')') {
					while (top(operators) != '(') {
						sprintf(output, "%s %c", output, pop(operators));
					}
					pop(operators);
				}
				else if (check_priority(s[i]) <= check_priority(top(operators)) &&
					 check_priority(s[i]) != 0) {
					stack_to_string(operators, &output);
					push(operators, s[i]);
				}
				else {
					push(operators, s[i]);
				}
			}
		}
	}

	stack_to_string(operators, &output);

	free_stack(&operators);

	return output;
}

int
calculate(char* s) 
{
	int result = 0;

	if (s == "") exit(EXIT_FAILURE);

	Stack *numbers = init_stack( strlen(s) );
	char *str_number = (char*) malloc ( sizeof(s) * sizeof(s) );

	if (str_number == NULL) {
		exit(EXIT_FAILURE);
	}

	int i = -1;
	while (s[++i]) {
		if (s[i] != ' ') {
			if (isdigit(s[i]) || s[i] == '.') {
				sprintf(str_number, "%s%c", str_number, s[i]);
			} else {
				int n1 = pop(numbers);
				int n2 = pop(numbers);

				push(numbers, execute_operation(s[i], n1, n2));
			}
		} else {
			push(numbers, strtol(str_number, NULL, 10));
			memset(str_number, 0, sizeof(str_number));
		}
	}

	free(str_number);
	result = top(numbers);
	free_stack(&numbers);

	return result;
}
