#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
	char data;
	struct tree *left;
	struct tree *right;
}*expTree;

expTree stack[30];
int top=-1;

expTree newnode(char b)
{
	expTree temp;
	temp=(struct tree*)malloc(sizeof(struct tree));
	temp->data=b;
	temp->left=NULL;
	temp->right=NULL;
	return(temp);
}

void push(expTree temp)
{
	stack[++top]=temp;
}

expTree pop()
{
	expTree p;
	p=stack[top--];
	return(p);
}

void inorder(expTree t)
{
	if(t!=NULL)
	{
		inorder(t->left);
		printf("%c",t->data);
		inorder(t->right);
	}
}

void preorder(expTree t)
{
	if(t!=NULL)
	{
		printf("%c",t->data);
		preorder(t->left);
		preorder(t->right);
	}
}

void postorder(expTree t)
{
	if(t!=NULL)
	{
		postorder(t->left);
		postorder(t->right);
		printf("%c",t->data);
	}
}