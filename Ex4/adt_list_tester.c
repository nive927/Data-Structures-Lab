//HEADER FILES REQUIRED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//HEADER FILES REQUIRED FOR getch() DUE TO ABSENCE OF <conio.h> IN gcc COMPILER
#include<unistd.h>
#include<termios.h>

#define N 30

//NODE STRUCTURE FOR DOUBLY LINKED LIST
struct Node
{
    char stu_name[N];
    struct Node *next;
    struct Node *prev;
};

//FUNCTION TO IMPLEMENT getch() DUE TO THE ABSENCE OF <conio.h> IN gcc COMPILER
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

//FUNCTION TO CREATE DOUBLY LINKED LIST
struct Node* createList()
{
	struct Node* head, *tail;

	head = (struct Node*)malloc(sizeof(struct Node));
	tail = (struct Node*)malloc(sizeof(struct Node));

	head->next = tail;
	tail->prev = head;

	return head;
}

//FUNCTION TO INSERT AT THE FRONT OF THE LIST
void insertFront(struct Node *head, char name[])
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));

    strcpy(new_node->stu_name, name);

    new_node->next = head->next;
    new_node->prev = head;

    head->next->prev = new_node;
    head->next = new_node;
}

//FUNCTION TO INSERT NODE AFTER A GIVEN NODE
void insertAfter(struct Node *head, char name[])
{
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	int flag = 0;
	char sname[N];

	node = head;

	while(node != NULL)
	{
		if(strcmp(node->stu_name, name)==0)
		{
			flag=1;
			break;
		}

		else
			node = node->next;

	}

	if(flag == 1)
	{
		struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));

		printf("\n\n\t\tEnter Student Name: ");
		scanf(" %[^\n]", sname);

	    strcpy(new_node->stu_name, sname);

	    new_node->next = node->next;

	    node->next = new_node;

	    new_node->prev = node;

	    if (new_node->next != NULL)
	        new_node->next->prev = new_node;
	}

	else
		printf("\n\n\t\tStudent Name NOT FOUND");
}

//FUNCTION TO INSERT NODE AT THE END OF THE LIST
void insertRear(struct Node *tail, char name[])
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));

    strcpy(new_node->stu_name, name);

    new_node->next = tail;
    new_node->prev = tail->prev;

    tail->prev->next = new_node;
    tail->prev = new_node;

}


//FUNCTION TO SEARCH FOR A NODE IN THE LIST
void searchList(struct Node *head, char name[])
{
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	int flag=0, pos=1;

	node = head->next;

	while(node != NULL)
	{
		if(strcmp(node->stu_name, name)==0)
		{
			printf("\n\n\t\tStudent Name FOUND in List at position %d", pos);
			flag=1;
			break;
		}

		else
		{
			pos++;
			node = node->next;
		}	

	}

	if(flag == 0)
		printf("\n\n\t\tStudent Name NOT FOUND in List");
}

void deleteNode(struct Node *head, char name[])
{
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	int flag = 0;

	node = head;

	while(node != NULL)
	{
		if(strcmp(node->stu_name, name)==0)
		{
			flag=1;
			break;
		}

		else
			node = node->next;

	}

	if(flag == 1)
	{
		if (head == NULL || node == NULL)
		        return;

		if (head == node)
		        head = node->next;

	    if (node->next != NULL)
		        node->next->prev = node->prev;

		if (node->prev != NULL)
		        node->prev->next = node->next;

		free(node);
	}

	else
		printf("\n\n\t\tStudent Name NOT FOUND");

}

// FUNCTION TO SORT LIST
void sortList(struct Node *h, struct Node *t)
{
int i=0,j,s=0;
char names[20][30];
char tname[30];

struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    
    temp = h;

    while (temp != NULL)
    {
		strcpy(names[s],temp->stu_name);
		++s;
        temp = temp->next;
    }


for(i=0;i<s;i++)
      for(j=0;j<s;j++){
         if(strcmp(names[i],names[j])<0){
            strcpy(tname,names[i]);
            strcpy(names[i],names[j]);
            strcpy(names[j],tname);
         }
      }
	printf("\n\t\tAFTER SORT: ");

      for(i=0;i<s;i++)
      {
      printf("%s ",names[i]);

      }

      printf("\n");

}

//FUNCTION TO PRINT NODES OF THE LIST STARTING FORM THE GIVEN NODE
void printList(struct Node *head, struct Node *tail)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    
    node = head;

    printf("\n\n\t\tFROM FRONT: ");
    while (node != NULL)
    {
		printf("%s ", node->stu_name);
        node = node->next;
    }

    printf("\n");
}

//MENU FOR LIST OPERATIONS
void menu_display()
{
    printf("\n\n\t\t+-------------------------------+\n");
    printf("\t\t MENU FOR DOUBLY LINKED LIST\n");
    printf("\t\t+-------------------------------+\n\n");
    printf("\n\n\t\t1. INSERT Student Name at the FRONT of the list");
    printf("\n\n\t\t2. INSERT Student Name at the END of the list");
    printf("\n\n\t\t3. INSERT Student Name AFTER the given Student Name");
    printf("\n\n\t\t4. SEARCH the given Student Name in the list");
    printf("\n\n\t\t5. DELETE the given Student Name from the list");
    printf("\n\n\t\t6. DISPLAY ALL Student Names");
    printf("\n\n\t\t7. DISPLAY ALL Student Names in ALPHABETICAL Order");
    printf("\n\n\t\t8. EXIT\n\n");

}

//DRIVER PROGRAM
int main()
{
    struct Node *head = NULL, *tail=NULL, *sortedh = NULL, *sortedt = NULL;

    head = createList();
    tail = head->next;

	int choice;
	char name[N];

	do
		{
			system("clear");

			menu_display();

			printf("\n\n\t\tEnter choice: ");
			scanf("%d", &choice);

			switch(choice)
			{
				case 1: printf("\n\n\t\tEnter Student Name: ");
						scanf(" %[^\n]", name);
						insertFront(head, name);
						getch();
						break;

				case 2:	printf("\n\n\t\tEnter Student Name: ");
						scanf(" %[^\n]", name);
						insertRear(tail, name);
						getch();
						break;

				case 3:	printf("\n\n\t\tEnter Student Name after which new Student is to be inserted: ");
						scanf(" %[^\n]", name);
						insertAfter(head, name);
						getch();
						break;

				case 4: printf("\n\n\t\tEnter Student Name to be searched: ");
						scanf(" %[^\n]", name);
						searchList(head, name);
						getch();
						break;

				case 5:	printf("\n\n\t\tEnter Student Name to be deleted: ");
						scanf(" %[^\n]", name);
						deleteNode(head, name);
						getch();
						break;

				case 6:	printList(head, tail);
						getch();
						break;

				case 7:	sortList(head, tail);
						printList(head, tail);
						getch();
						break;

				case 8: free(head);
						free(tail);
						free(sortedh);
						free(sortedt);
						system("clear");
						return 0;
						break;

				default: printf("INVALID choice!! Re-enter Valid Choice");
			}

		}while(choice!=8);



}