
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define L 45

struct Node
{
    char key1[L];
    char key2[L];
    char key3[L];
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node* newNode(char key1[], char key2[], char key3[])
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    strcpy(node->key1, key1);
    strcpy(node->key2, key2);
    strcpy(node->key3, key3);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;

    return(node);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, char key1[], char key2[], char key3[])
{
    if (node == NULL)
        return(newNode(key1, key2, key3));

    if (strcmp(key1, node->key1) < 0)
        node->left  = insert(node->left, key1, key2, key3);
    else if (strcmp(key1, node->key1) > 0)
        node->right = insert(node->right, key1, key2, key3);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(key1, node->left->key1) < 0)
    {
		printf("\nSingle Rotate: Right\n");
		return rightRotate(node);
	}
    if (balance < -1 && strcmp(key1, node->right->key1) > 0)
    {
		printf("\nSingle Rotate: Left\n");
		return leftRotate(node);
	}

    if (balance > 1 && strcmp(key1, node->left->key1) > 0)
    {
		printf("\nDouble Rotate: Left-Right\n");
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(key1, node->right->key1) < 0)
    {
		printf("\nDouble Rotate: Right-Left\n");
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node* search(struct Node* root, char key1[]) 
{  
    if (root == NULL || strcmp(root->key1, key1) == 0) 
       return root; 
      
    if (strcmp(root->key1, key1) < 0) 
       return search(root->right, key1); 
  
    return search(root->left, key1); 
} 

void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%s %s %s\n", root->key1, root->key2, root->key3);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root)
{
    if(root != NULL)
    {
		inOrder(root->left);
        printf("%s\t%s\t%s\n", root->key1, root->key2, root->key3);
        inOrder(root->right);
    }
}

void postOrder(struct Node *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%s %s %s\n", root->key1, root->key2, root->key3);
    }
}

int main()
{
	struct Node *root = NULL, *result = (struct Node*)malloc(sizeof(struct Node*));
	char english[L], tamil[L], hindi[L];
	int n, choice;

    do
    {
        printf("\n-----------------------------------------------");
        printf("\nMENU");
        printf("\n-----------------------------------------------");
        printf("\n1. INSERT into AVL Tree");
        printf("\n2. SEARCH AVL Tree");
        printf("\n3. EXIT");
        printf("\n-----------------------------------------------\n");

        printf("Enter choice: ");
        scanf(" %d", &choice);


        switch(choice)
        {
            case 1: printf("\nEnter the number of nodes to be inserted: ");
                    scanf(" %d", &n);
                    printf("-----------------------------------------------\n");

                    for(int i=0; i<n; i++)
                    {   
                        printf("\nEnter English word: ");
                        scanf(" %[^\n]", english);

                        printf("Enter Tamil Equivalent: ");
                        scanf(" %[^\n]", tamil);

                        printf("Enter Hindi Equivalent: ");
                        scanf(" %[^\n]", hindi);

                        root = insert(root, english, tamil, hindi);

                        printf("\nIN-ORDERED AVL Tree is:\n\n");
                        inOrder(root);
                        printf("\n-----------------------------------------------\n");
                    }

                    break;

            case 2: printf("\nEnter English word: ");
                    scanf(" %[^\n]", english);

                    result = search(root, english);

                    if(result != NULL)
                        printf("\nMulti-Lingual Dictionary: %s %s %s\n", result->key1, result->key2, result->key3);
                    else
                        printf("\nWord NOT FOUND!\nTRY AGAIN !\n");

                    break;
            
            case 3: return 0;

            default: printf("/nINVALID CHOICE!\nRETRY !\n");
        }
    }while(choice != 3);
}
