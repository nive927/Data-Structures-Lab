#include "CharStack.h"
#include "TreeStack.h"
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
	struct cNode *stack = NULL;

	while(exp[i] != '\0')
	{
		if((exp[i] == '{') || (exp[i] == '(') || (exp[i] == '['))
        	cpush(&stack, exp[i]);

        if((exp[i] == '}') || (exp[i] == ')') || (exp[i] == ']'))
        {
			if(stack == NULL)
				return 0;

            else if(!checkMatch(cpop(&stack), exp[i]))
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
    struct cNode *stack = NULL;
    static char newExp[N], ch;

    while( exp[i] != '\0')
    {
		if (isOperand(exp[i]))
        	newExp[k++] = exp[i];

        else if (exp[i] == '(')
            cpush(&stack, exp[i]);

        else if (exp[i] == ')')
        {
            while ((stack != NULL) && (stack->c != '('))
                newExp[k++] = cpop(&stack);

            if ((stack != NULL) && (stack->c == '('))
                ch = cpop(&stack);

        }
        else
        {
            while ((stack != NULL) && Prec(exp[i]) <= Prec(stack->c))
                newExp[k++] = cpop(&stack);

            cpush(&stack, exp[i]);
        }

        i++;

    }

    while (stack != NULL)
        newExp[k++] = cpop(&stack);

    newExp[k] = '\0';

    return newExp;

}

int main()
{
	char expression[N], *postfix;
	int i;

	expTree temp;

	printf("Enter the expression: ");
	scanf(" %[^\n]", expression);

	if(checkBalancedBrackets(expression))
	{
		printf("\nBalanced \n");
		postfix = infixToPostfix(expression);
		printf( "Postfix: %s\n", postfix);

		for(i=0;postfix[i]!='\0';i++)
		{
			if(postfix[i]=='*' || postfix[i]=='/' || postfix[i]=='+' || postfix[i]=='-')
			{

				temp=newnode(postfix[i]);
				temp->right=pop();
				temp->left=pop();
				push(temp);
			}

			else
			{
				temp=newnode(postfix[i]);
				push(temp);
			}
		}

		printf("\nPre-order: ");
		preorder(temp);
		printf("\n");
		printf("\nIn-order: ");
		inorder(temp);
		printf("\n");
		printf("\nPost-order: ");
		postorder(temp);
		printf("\n\n");
	}

	else
    	printf("\nNot Balanced \n");

  return 0;


}
