#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
	int Regno;
	char Name[30];
	float Marks[5];
};

struct list
{
	int capacity;
	int size;
	struct student *s;
};

typedef struct list *ptrToNode;
typedef ptrToNode LIST;
typedef int POSITION;

struct student add_student()
{
	struct student s;

	printf("\nNEW STUDENT RECORD\n");

	printf("Enter Register Number: ");
	scanf(" %d", &s.Regno);

	printf("Enter Name: ");
	scanf(" %s", s.Name);

	printf("\nMarks Obtained\n");
	for(int i=0; i<5; i++)
	{
		printf("Enter Mark %d: ", i+1);
		scanf(" %f", &s.Marks[i]);
	}

	return s;

}

void display_student(struct student s, int i)
{
	printf("\nStudent Record %d\n", i+1);
	printf("Register Number: %d\n", s.Regno);
	printf("Name: %s\n", s.Name);
	printf("Marks Obtained: %.2f %.2f %.2f %.2f %.2f\n", s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4]);
}

int IsEmpty(LIST L)
{
	return L->size==0;
}

int IsFull(LIST L)
{
	return L->size==L->capacity;
}

void MakeEmpty(LIST L)
{
	if(IsEmpty(L))
		printf("\nList is already empty\n");

	else
	{
		L->size=0;

		printf("\nList has been made empty\n");
	}
}

LIST CreateList(int max)
{
	LIST L;

	L=(struct list*)malloc(sizeof(struct list));

	if(L==NULL)
		printf("\nFatal Error\n");

	else
	{
		L->capacity=max;
		L->s=(struct student*)malloc(sizeof(struct student)*max);

		if(L->s==NULL)
			printf("\nFatal Error\n");

		else
		{
			L->size=0;
			printf("\nList was created Successfully\n");
		}

	}

	return L;
}

void InsertInList(LIST L, POSITION pos)
{
	if(IsFull(L))
		printf("\nList is Full\n");

	else
	{
		if(IsEmpty(L))
			L->s[0]=add_student();

		else
		{
			for(int i=L->size-1; i>=pos-1; i--)
				L->s[i+1]=L->s[i];

			L->s[pos-1]=add_student();
		}

		L->size++;
		printf(" %d\n", L->size);
	}
}

POSITION FindRegno(int rno, LIST L)
{
	POSITION pos=-1;

	for(int i=0; i<L->size; i++)
		if(L->s[i].Regno==rno)
			pos=i+1;

	return pos;
}

POSITION FindName(char name[], LIST L)
{
	POSITION pos=-1;

		for(int i=0; i<L->size; i++)
			if(strcmp(L->s[i].Name, name)==0)
				pos=i;

	return pos;
}

void DeleteFromList(int RecNo, LIST L)
{
	for(int i=RecNo-1; i<L->size; i++)
		L->s[i]=L->s[i+1];

	L->size--;

}

LIST DeleteList(LIST L)
{
	MakeEmpty(L);

	free(L);

	L=NULL;

	return L;
}

void DisplayList(LIST L)
{
	for(int i=0; i<L->size; i++)
		display_student(L->s[i], i);

}

void menu_display()
{
	printf("\n\n\tMENU");
	printf("\n\n\t\t1. INSERT Record at the Front");
	printf("\n\n\t\t2. INSERT Record at the End");
	printf("\n\n\t\t3. INSERT Record after the Given Regno");
	printf("\n\n\t\t4. SEARCH Record using Name");
	printf("\n\n\t\t5. DELETE particular Record");
	printf("\n\n\t\t6. DISPLAY all the Records");
	printf("\n\n\t\t7. DISPLAY Records Before and After particular Record");
	printf("\n\n\t\t8. EXIT");
}

int main()
{
	LIST L=NULL;
	int max, choice, pos, rno;
	char name[30];

	printf("Enter the total number of Student Records: ");
	scanf("%d", &max);

	L=CreateList(max);

	do
	{
		menu_display();

		printf("\n\nEnter choice: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: pos=1;
					InsertInList(L, pos);
					break;

			case 2:	pos=L->size;
					InsertInList(L, pos+1);
					break;

			case 3:	if(IsEmpty(L))
						printf("List is Empty!!!!!");

					else if(IsFull(L))
						printf("List is Full!!!!!");

					else
					{
						printf("\nEnter the Register Number after which the new record is to be inserted: ");
						scanf(" %d", &rno);
						pos=FindRegno(rno, L)+1;
						if(pos!=-1)
							InsertInList(L, pos);
						else
							printf("Register Number NOT FOUND...!!!!!");
					}
					break;

			case 4: if(!IsEmpty(L))
					{
						printf("\nEnter the Student Name to view the related record: ");
						scanf(" %s", name);
						pos=FindName(name, L);
						if(pos!=-1)
							display_student(L->s[pos], pos);
						else
							printf("Name NOT FOUND...!!!!!");
					}
					else
						printf("List is Empty!!!!");
					break;

			case 5:	if(!IsEmpty(L))
					{
						printf("\nEnter the Record Number to be deleted: ");
						scanf(" %d", &pos);

						if((pos>L->size)||(pos<0))
							printf("\nRecord Number doesn't Exist!!!!!\n");

						else
						{
							DeleteFromList(pos, L);
							printf("\nStudent Record %d SUCCESSFULLY deleted!!!!!\n", pos);
						}
					}
					else
						printf("List is Empty!!!!");

					break;

			case 6: if(!IsEmpty(L))
						DisplayList(L);
					else
						printf("List is Empty!!!!");
					break;

			case 7:	if(!IsEmpty(L))
					{
						printf("\nEnter the Reference Record Number: ");
						scanf(" %d", &pos);

						if((pos>L->size)||(pos<0))
							printf("\nRecord Number doesn't Exist!!!!!\n");

						else if(pos==1)
						{
							printf("\nPREVIOUS Record doesn't exist\n");
							printf("\nNEXT Record:\n");
							display_student(L->s[pos], pos);
						}

						else if(pos==L->size)
						{
							printf("\nPREVIOUS Record:\n");
							display_student(L->s[pos-2], pos-2);
							printf("\nNEXT Record doesn't exist\n");
						}
						else
						{
							printf("\nPREVIOUS Record:\n");
							display_student(L->s[pos-2], pos-2);
							printf("\nNEXT Record:\n");
							display_student(L->s[pos], pos);
						}
					}
					else
						printf("List is Empty!!!!");
					break;

			case 8: DeleteList(L); return 0; break;

			default: printf("INVALID choice!! Re-enter Valid Choice");
		}

	}while(choice!=8);

}