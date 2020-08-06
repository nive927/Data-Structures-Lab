#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>

#define N 25

// FUNCTION TO IMPLEMENT getch() DUE TO THE ABSENCE OF <conio.h> IN gcc COMPILER

char getch()
{
	char buf=0;

	struct termios old={0};

	fflush(stdout);

	if(tcgetattr(0, &old)<0)
		perror("tcsetattr()");

	old.c_lflag&=~ICANON;
    	old.c_lflag&=~ECHO;
    	old.c_cc[VMIN]=1;
    	old.c_cc[VTIME]=0;

	if(tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");

	if(read(0,&buf,1)<0)
		perror("read()");

	old.c_lflag|=ICANON;
   	old.c_lflag|=ECHO;

	if(tcsetattr(0, TCSADRAIN, &old)<0)
		perror ("tcsetattr ~ICANON");

	return buf;
}

// Node Definition for Binary Search Tree

struct treeNode
{
	char name[N];
	struct treeNode *left;
	struct treeNode *right;
};

typedef struct treeNode* bstNode;

// Function to Create New Node

bstNode newNode(char name[])
{
	bstNode node = (struct treeNode*)malloc(sizeof(struct treeNode));
	strcpy(node->name, name);
	node->left = node->right = NULL;
	return node;
}

// Function to INSERT the New Node in the BST

bstNode insert(bstNode bstTree, char name[])
{
	if(bstTree == NULL)
		return newNode(name);

	else
	{
		if(strcmp(name, bstTree->name) < 0)
			bstTree->left = insert(bstTree->left, name);

		else
			bstTree->right = insert(bstTree->right, name);
	}

	return bstTree;
}

// Function to find the Grandparent of the given node
void findGrandparent(bstNode bstTree, char name[])
{
	if(bstTree->left != NULL)
	{
		if(bstTree->left->left != NULL && strcmp(bstTree->left->left->name, name) == 0)
			printf("\n\tGrandparent: %s", bstTree->name);

		else if(bstTree->left->right != NULL && strcmp(bstTree->left->right->name, name) == 0)
			printf("\n\tGrandparent: %s", bstTree->name);
	}

	if(bstTree->right != NULL)
	{
		if(bstTree->right->left != NULL && strcmp(bstTree->right->left->name, name) == 0)
			printf("\n\tGrandparent: %s", bstTree->name);

		else if(bstTree->right->right != NULL && strcmp(bstTree->right->right->name, name) == 0)
			printf("\n\tGrandparent: %s", bstTree->name);
	}

	if(bstTree->left != NULL && (strcmp(name, bstTree->name) < 0))
		findGrandparent(bstTree->left, name);

	else if(bstTree->right != NULL && strcmp(name, bstTree->name) > 0)
		findGrandparent(bstTree->right, name);

	else
		return;
}

// Function to find grandchildren of the given node

void findGrandchildren(bstNode bstTree, char name[])
{
	bstNode grandparent = bstTree;

	while (grandparent != NULL && (strcmp(grandparent->name, name) != 0))
	{
		if (strcmp(name, grandparent->name) < 0)
			grandparent = grandparent->left;

		else
			grandparent = grandparent->right;
	}

	if (grandparent == NULL)
	{
		printf("CANNOT be found as %s is NOT PRESENT in BST !", name);
		return;
	}

	if(grandparent->left != NULL)
	{
		if(grandparent->left->left != NULL || grandparent->left->right != NULL)
		{
			if(grandparent->left->left != NULL)
				printf("%s ", grandparent->left->left->name);

			if(grandparent->left->right != NULL)
				printf("%s ", grandparent->left->right->name);
		}

		else
			printf("NO LEFT Grandchildren! ");
	}

	else
		printf("NO LEFT Grandchildren! ");

	if(grandparent->right != NULL)
	{
		if(grandparent->right->left != NULL || grandparent->right->right != NULL)
		{
			if(grandparent->right->left != NULL)
				printf("%s ", grandparent->right->left->name);

			if(grandparent->right->right != NULL)
				printf("%s ", grandparent->right->right->name);
		}

		else
			printf("NO RIGHT Grandchildren! ");
	}

	else
		printf("NO RIGHT Grandchildren! ");
}

// Function to find Sibling of the given node

void findSibling(bstNode bstTree, char name[])
{
	bstNode curr = bstTree;

	bstNode parent = NULL;

	while (curr != NULL && (strcmp(curr->name, name) != 0))
	{
		parent = curr;

		if (strcmp(name, curr->name) < 0)
			curr = curr->left;
		else
			curr = curr->right;
	}

	if (curr == NULL)
	{
		printf("\n\t%s Not FOUND in BST !", name);
		return;
	}

	if(parent == NULL)
	{
		printf("\n\t%s is the Root Node of the BST", name);
		return;
	}

	if(strcmp(name, parent->name) < 0 && parent->right != NULL)
		printf("\n\tRight Sibling: %s", parent->right->name);

	else if(strcmp(name, parent->name) > 0 && parent->left != NULL)
		printf("\n\tLeft Sibling: %s", parent->left->name);

	else
		printf("\n\tNo Sibling !");
}

// Function to find the Min value in the subtree

bstNode minValueNode(bstNode bstTree)
{
    bstNode current = bstTree;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function to Delete the node

bstNode deleteNode(bstNode bstTree, char name[])
{
    if (bstTree == NULL)
    	return bstTree;

    if (strcmp(name, bstTree->name) < 0)
        bstTree->left = deleteNode(bstTree->left, name);

    else if (strcmp(name, bstTree->name) > 0)
        bstTree->right = deleteNode(bstTree->right, name);

    else
    {
        if (bstTree->left == NULL)
        {
            bstNode temp = bstTree->right;
            free(bstTree);
            return temp;
        }
        else if (bstTree->right == NULL)
        {
            bstNode temp = bstTree->left;
            free(bstTree);
            return temp;
        }

        bstNode temp = minValueNode(bstTree->right);

        strcpy(bstTree->name, temp->name);

        bstTree->right = deleteNode(bstTree->right, temp->name);
    }

    return bstTree;
}

// Displaying in Alphabetical Order

void inorder(bstNode bstTree)
{
    if (bstTree != NULL)
    {
        inorder(bstTree->left);
        printf("%s ", bstTree->name);
        inorder(bstTree->right);
    }
}

void preorder(bstNode bstTree)
{
	if(bstTree != NULL)
	{
		printf("%s ", bstTree->name);
		preorder(bstTree->left);
		preorder(bstTree->right);
	}
}

void postorder(bstNode bstTree)
{
	if(bstTree != NULL)
	{
		postorder(bstTree->left);
		postorder(bstTree->right);
		printf("%s ", bstTree->name);
	}
}

// MAIN PROGRAM

int main()
{
	char name[N], choice;
	int n;
	bstNode bstTree = NULL;

	/*system("clear");
	printf("\n\tEnter root name: ");
	scanf("%s", name);
	bstTree = insert(bstTree, name);*/

	do
		{
			system("clear");

			printf("\n\n\t+----------------------------+\n");
			printf("\tMENU FOR BINARY SEARCH TREE\n");
			printf("\t+----------------------------+\n\n");

			printf("\t1. INSERT New Node\n\n");
			printf("\t2. DISPLAY Tree in Alphabetical Order\n\n");
			printf("\t3. FIND Grandparent of given Node\n\n");
			printf("\t4. FIND Grandchildren of given Node\n\n");
			printf("\t5. FIND Sibling of given Node\n\n");
			printf("\t6. DELETE given Node and DISPLAY New Tree\n\n");
			printf("\t7. EXIT\n\n");

			printf("\n\n\tENTER choice: ");
			scanf(" %c", &choice);

			switch(choice)
			{
				case '1':	printf("\n\n\tENTER number of new nodes: ");
							scanf("%d", &n);

							for(int i=0; i<n; i++)
							{
								printf("\n\tEnter name: ");
								scanf("%s", name);
								bstTree = insert(bstTree, name);
							}

							getch();
							break;

				case '2':	if(bstTree != NULL)
							{
								printf("\n\n\tAlphabetical Order: ");
								inorder(bstTree);
								printf("\n");
							}

							else
								printf("\n\tBST is EMPTY !");
							getch();
							break;

				case '3':	printf("\n\tEnter name to find its Grandparent: ");
							scanf("%s", name);

							if(bstTree != NULL)
								findGrandparent(bstTree, name);

							else
								printf("\n\tBST is EMPTY !");

							getch();
							break;

				case '4':	printf("\n\tEnter name to find Grandchildren in the BST: ");
							scanf("%s", name);

							printf("\n\tGrandchildren: ");
							findGrandchildren(bstTree, name);
							getch();
							break;

				case '5':	printf("\n\tEnter name to find Sibling in the BST: ");
							scanf("%s", name);

							findSibling(bstTree, name);
							getch();
							break;

				case '6':	printf("\n\tEnter name to be deleted from the BST: ");
							scanf("%s", name);

							if(bstTree != NULL)
							{
								bstTree = deleteNode(bstTree, name);

								printf("\n\n\tPreOrder: ");
								preorder(bstTree);
								printf("\n");

								printf("\n\n\tInOrder: ");
								inorder(bstTree);
								printf("\n");

								printf("\n\n\tPostOrder: ");
								postorder(bstTree);
								printf("\n");
							}

							else
								printf("\n\tBST is EMPTY !");
							getch();
							break;

				case '7':	system("clear");
							return 0;

				default:	printf("\n\tINVALID OPTION .....!!!!!\n\n");

			}
		}while(choice!=7);
}