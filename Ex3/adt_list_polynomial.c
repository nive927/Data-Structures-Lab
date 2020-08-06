//HEADER FILES

#include<stdio.h>
#include<stdlib.h>

//HEADER FILES REQUIRED FOR getch() DUE TO ABSENCE OF <conio.h> IN gcc COMPILER

#include<unistd.h>
#include<termios.h>

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

//NODE DEFINITION WITH POWER AND CO-EFFICIENT FIELDS

struct Node
{
    int coeff;
    int pow;
    struct Node *next;
};

//FUNCTION TO ADD A NEW NODE AT THE END OF THE LIST

struct Node *addnode(struct Node *start, int coeff, int pow)
{
    // Create a new node
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->coeff = coeff;
    newnode->pow = pow;
    newnode->next = NULL;

    // If linked list is empty
    if (start == NULL)
        return newnode;

    // If linked list has nodes
    struct Node *ptr = start;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = newnode;

    return start;
}

//FUNCTION TO CREATE A NEW POLYNOMIAL

void create_poly(struct Node *node)
{
	char choice = 'y';

    do
    {
    	printf("\n\t\tEnter co-efficient: ");
    	scanf("%d", &node->coeff);

    	printf("\t\tEnter power: ");
    	scanf("%d", &node->pow);

    	node->next = (struct Node *)malloc(sizeof(struct Node));
    	node = node->next;
    	node->next = NULL;

    	printf("\n\t\tCONTINUE? YES:Y NO:N\n");
    	printf("\t\tEnter choice: ");
    	scanf(" %c", &choice);

    }while((choice == 'y')||(choice == 'Y'));
}

//FUNCTION FOR ADDITION OF THE POLYNOMIALS

void add_poly(struct Node *poly1, struct Node *poly2, struct Node *poly)
{
	while(poly1->next && poly2->next)
    {
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is
        // and move its pointer
        if(poly1->pow > poly2->pow)
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }

        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is
        // and move its pointer
        else if(poly1->pow < poly2->pow)
        {
            poly->pow = poly2->pow;
            poly->coeff = poly2->coeff;
            poly2 = poly2->next;
        }

        // If power of both polynomial numbers is same then add their coefficients
        else
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff+poly2->coeff;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }

        // Dynamically create new node
        poly->next = (struct Node *)malloc(sizeof(struct Node));
        poly = poly->next;
        poly->next = NULL;
    }

	while(poly1->next || poly2->next)
    {
        if(poly1->next)
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }

        if(poly2->next)
        {
            poly->pow = poly2->pow;
            poly->coeff = poly2->coeff;
            poly2 = poly2->next;
        }

        poly->next = (struct Node *)malloc(sizeof(struct Node));
        poly = poly->next;
        poly->next = NULL;
    }
}

//FUNCTION TO REMOVE DUPLICTAES

void removeDuplicates(struct Node *start)
{

    struct Node *ptr1, *ptr2, *dup;

    ptr1 = start;

    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;

        // Compare the picked element
        // with rest of the elements
        while (ptr2->next != NULL)
        {

            // If powerer of two elements are same
            if (ptr1->pow == ptr2->next->pow)
            {

                // Add their coefficients and put it in 1st element
                ptr1->coeff = ptr1->coeff + ptr2->next->coeff;
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;

                // remove the 2nd element
                free (dup);
            }

            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

//FUNCTION TO MULTIPLY TWO POLYNOMIALS

struct Node *multiply_poly(struct Node *poly1, struct Node *poly2, struct Node *poly3)
{

    // Create two pointer and store the
    // address of 1st and 2nd polynomials
    struct Node *ptr1, *ptr2;
    ptr1 = poly1;
    ptr2 = poly2;
    while (ptr1 != NULL) {
        while (ptr2 != NULL) {
            int coeff, pow;

            // Multiply the coefficient of both
            // polynomials and store it in coeff
            coeff = ptr1->coeff * ptr2->coeff;

            // Add the powerer of both polynomials
            // and store it in power
            pow = ptr1->pow + ptr2->pow;

            // Invoke addnode function to create
            // a newnode by passing three parameters
            poly3 = addnode(poly3, coeff, pow);

            // move the pointer of 2nd polynomial
            // two get its next term
            ptr2 = ptr2->next;
        }

        // Move the 2nd pointer to the
        // starting point of 2nd polynomial
        ptr2 = poly2;

        // move the pointer of 1st polynomial
        ptr1 = ptr1->next;
    }

    // this function will be invoke to add
    // the coefficient of the elements
    // having same powerer from the resultant linked list
    removeDuplicates(poly3);

    return poly3;

    }

//FUNCTION TO DISPLAY THE POLYNOMIAL

void show_poly(struct Node *node)
{

	while(node->next != NULL)
    {
        if(node->coeff!=0)
        {	if(node->pow!=0)
        		printf("(%dx^%d)+", node->coeff, node->pow);

			else
				printf("(%d)+", node->coeff);

		}
        node = node->next;

        if(node->next == NULL)
        printf("\b ");
    }

    printf("\n");
}

//MENU

void menu_display()
{
    printf("\n\n\t\t+---------------------------------+\n");
    printf("\t\t MENU FOR POLYNOMIAL MANIPULATION\n");
    printf("\t\t+---------------------------------+\n\n");
    printf("\n\n\t\t1. CREATE list for Polynomials");
    printf("\n\n\t\t2. ADD Polynomials");
    printf("\n\n\t\t3. MULTIPLY Polynomials");
    printf("\n\n\t\t4. DISPLAY Polynomials");
    printf("\n\n\t\t5. EXIT\n\n");

}

//DRIVER PROGRAM

int main()
{
    struct Node *poly1 = NULL, *poly2 = NULL, *poly = NULL, *poly3 = NULL;
    int choice;

    poly1 = (struct Node *)malloc(sizeof(struct Node));
    poly2 = (struct Node *)malloc(sizeof(struct Node));

    //SUM
    poly = (struct Node *)malloc(sizeof(struct Node));

    //PRODUCT
    //poly3 = (struct Node *)malloc(sizeof(struct Node));

    do
    {
        system("clear");

        menu_display();

        printf("\n\n\tEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: //FIRST POLYNOMIAL
                    printf("\n\tEnter POLYNOMIAL 1\n");
                    create_poly(poly1);

                    //SECOND POLYNOMIAL
                    printf("\n\tEnter POLYNOMIAL 2\n");
                    create_poly(poly2);

                    getch();
                    break;

            case 2: //ADDING BOTH POLYNOMIALS
                    add_poly(poly1, poly2, poly);

                    //SUM OF THE POLYNOMIALS
                    printf("\n\tSUM of the polynomials: ");
                    show_poly(poly);

                    getch();
                    break;

            case 3: //MULTIPLYING BOTH POLYNOMIALS
                    poly3 = multiply_poly(poly1, poly2, poly3);

                    //PRODUCT OF BOTH POLYNOMIALS
                    printf("\n\tPRODUCT of the polynomials: ");
                    show_poly(poly3);

                    getch();
                    break;

            case 4: printf("\n\t1st POLYNOMIAL: ");
                    show_poly(poly1);

                    printf("\n\t2nd POLYNOMIAL: ");
                    show_poly(poly2);

                    //SUM OF THE POLYNOMIALS
                    printf("\n\tSUM of the polynomials: ");
                    show_poly(poly);

                    printf("\n\tPRODUCT of the polynomials: ");
                    show_poly(poly3);

                    getch();
                    break;

            case 5: system("clear");
                    free(poly1);
                    free(poly2);
                    free(poly3);
                    free(poly);

                    return 0;
                    break;

            default:    printf("\n\t\tINVALID choice!! Re-enter Valid Choice");
                        getch();
        }

    }while(choice!=5);

}
