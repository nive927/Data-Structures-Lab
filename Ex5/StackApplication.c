#include "stack.h"
#include<ctype.h>

#define N 45

// Function to check if the two brackets match
int checkMatch(char ch1, char ch2)
{
	if((ch1 == '(') && (ch2 == ')'))
		return 1;

    else if((ch1 == '{') && (ch2 == '}'))
    	return 1;

    else if((ch1 == '[') && (ch2 == ']'))
    	return 1;

    else
    	return 0;
}

// Function to check if the brackets in the expression are balanced
int checkBalancedBrackets(char exp[])
{
	int i = 0;
	struct fNode *stack = NULL;

	while(exp[i] != '\0')
	{
		if((exp[i] == '{') || (exp[i] == '(') || (exp[i] == '['))
        	fpush(&stack, exp[i]);

        if((exp[i] == '}') || (exp[i] == ')') || (exp[i] == ']'))
        {
			if(stack == NULL)
				return 0;

            else if(!checkMatch(fpop(&stack), exp[i]))
            	return 0;
      	}

      	i++;
   	}

	if(stack == NULL)
		return 1;

  	else
  		return 0;
}

// Function to check if the character is an operand
int isOperand(char ch)
{
    return (isdigit(ch));
}

// Function to assign precedence
int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    }
    return -1;
}


// Function to convert infix to postfix
char* infixToPostfix(char* exp)
{
    int i = 0, k = 0;
    struct fNode *stack = NULL;
    static char newExp[N], ch='(';

    while( exp[i] != '\0')
    {
		if (isOperand(exp[i]))
        	newExp[k++] = exp[i];

        else if (exp[i] == '(')
            fpush(&stack, exp[i]);

        else if (exp[i] == ')')
        {
            while ((stack != NULL) && (stack->c != '('))
                newExp[k++] = fpop(&stack);

            if ((stack != NULL) && (stack->c == '('))
                ch = fpop(&stack);

        }
        else
        {
            while ((stack != NULL) && Prec(exp[i]) <= Prec(stack->c))
                newExp[k++] = fpop(&stack);

            fpush(&stack, exp[i]);
        }

        i++;

    }

    while (stack != NULL)
        newExp[k++] = fpop(&stack);

    newExp[k] = '\0';
    printf( "Postfix: %s\n", newExp );

    return newExp;

}

float evaluatePostfix(char* exp)
{
    struct fNode *stack = NULL;
    int i;

    for (i = 0; exp[i]!='\0'; ++i)
    {
        if (isdigit(exp[i]))
            fpush(&stack, exp[i]-'0');

        else
        {
            float val1 = fpop(&stack);
            float val2 = fpop(&stack);

            switch (exp[i])
            {
            case '+': fpush(&stack, val2 + val1); break;
            case '-': fpush(&stack, val2 - val1); break;
            case '*': fpush(&stack, val2 * val1); break;
            case '/': fpush(&stack, val2/val1); break;
            }
        }
    }
    return fpop(&stack);
}

int main()
{
	char expression[N], *postfix;
	float result;

	printf("Enter the expression: ");
	scanf(" %[^\n]", expression);

	if(checkBalancedBrackets(expression))
	{
		printf("\nBalanced \n");
		postfix = infixToPostfix(expression);
		result = evaluatePostfix(postfix);
		printf("\nResult:%f\n", result);
	}

	else
    	printf("\nNot Balanced \n");

  return 0;
}