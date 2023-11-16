// Include the standard input/output and standard library header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define DEPARTMENT  1
#define TITLE  2
#define AUTHOR  3
#define PUBLISHER 4
#define NUMBEROFPAGES 5
#define NUMBEROFBOOKS 6
#define NUMBEROFAVAILABEBOOKS 7
#define NUMBEROFBORROWEDBOOKS 8
#define PRICE  9

#define STOP   0
// Define a constant array of characters to store the password
const char Password[6] = {'1', '2', '3', '4', '5', '6'};

// Define a structure to store the information of a book
struct book {
    int ID; // The unique identifier of the book
    char Department[30]; // The department that the book belongs to
    char title[30]; // The title of the book
    char author[30]; // The author of the book
    char publisher[30]; // The publisher of the book
    int numberOfPages; // The number of pages in the book
    int numberOfBooks; // The total number of copies of the book
    int numberOfAvailableBooks; // The number of available copies of the book
    int numberOfBorrowedBooks; // The number of borrowed copies of the book
    int price; // The price of the book
};

// Define a structure to store a node in a linked list
struct Node {
    struct book b; // The book data stored in the node
    struct book *book_ptr; // A pointer to the next node in the list
};

// Define a structure to store the information of a book
typedef struct student
{
	char name[30];		
	char issuedBookTitle[30]; // The unique identifier of the student
    int ID;
	int issuedBookID;

}student_t;

typedef struct Student_Node
{
    student_t s;// The student data stored in the node
    student_t *student_ptr; // A pointer to the next  student node in the list
}Student_Node_t;


// Declare a function to display the main menu
void MainMenu();

// Declare a global variable to store the head of the linked list
struct Node *head = NULL;
Student_Node_t *student_head = NULL;

// Define a function to add a new book to the linked list in ascending order of ID
void Add_Book(struct Node **Head, struct book new_book) {
    // Allocate memory for a new node and assign the new book data to it
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->b = new_book;
    new_node->book_ptr = NULL;

    // If the list is empty, make the new node as the head and return
    if (*Head == NULL) {
        *Head = new_node;
        return;
    }

    //4 5 7 10 11

    // Initialize two pointers to traverse the list and find the correct position for the new node
    struct Node *current = *Head;
    struct Node *previous = NULL;

    // Loop until the end of the list or until a node with larger or equal ID is found
    while (current != NULL && current->b.ID < new_book.ID) {
        previous = current; // Update the previous pointer to point to the current node
        current = (struct Node *) current->book_ptr; // Move the current pointer to the next node
    }

    // If the previous pointer is NULL, it means that the new node should be inserted at the beginning of the list
    if (previous == NULL) {
        new_node->book_ptr = (struct book *) *Head; // Make the new node point to the current head
        *Head = new_node; // Make the new node as the new head
    } else { // Otherwise, insert the new node between the previous and current nodes
        new_node->book_ptr = (struct book *) current; // Make the new node point to the current node
        previous->book_ptr = (struct book *) new_node; // Make the previous node point to the new node
    }

}

// Define a function to delete a book from the linked list by its ID
int Delete_Book(struct Node **Head, int Book_ID) {

    // If the list is empty, return 0 to indicate failure
    if (*Head == NULL) {
        return 0;
    }

    // Initialize two pointers to traverse the list and find the node with the given ID
    struct Node *current = *Head;
    struct Node *previous = NULL;

    // Loop until the end of the list or until a node with matching ID is found
    while (current != NULL && current->b.ID != Book_ID) {
        previous = current; // Update the previous pointer to point to the current node
        current = (struct Node *) current->book_ptr; // Move the current pointer to the next node
    }

    // If the current pointer is NULL, it means that no node with matching ID was found, so return 0 to indicate failure
    if (current == NULL) {
        return 0;
    }

    // If the previous pointer is NULL, it means that the node to be deleted is at the head of the list
    if (previous == NULL) {
        *Head = (struct Node *) current->book_ptr; // Make the head point to the next node in the list
    } else { // Otherwise, delete the node by skipping it from the list
        previous->book_ptr = current->book_ptr; // Make the previous node point to the next node after the current node
    }

    // Free the memory allocated for the current node
    free(current);

    // Return 1 to indicate success
    return 1;
}


// Define a function to return to the main menu
void Return() {
    char Ret = 1;
    while (Ret == 1) {
        Ret = 0;
        scanf("%d", &Ret);
    }
    system("cls"); // Clear the screen
    MainMenu(); // Call the main menu function
}



// This is a duplicate of the Add_Book function defined above, so it can be deleted or commented out
void view_books(struct Node **Head) {

    // Initialize a pointer to traverse the list and display the book data
    struct Node *p = (struct Node *) Head;

    // Loop until the end of the list
    while (p != NULL) {

        // Print the book information
        printf("ID: %d\n", p->b.ID);
        printf("Department: %s\n", p->b.Department);
        printf("Title: %s\n", p->b.title);
        printf("Author: %s\n", p->b.author);
        printf("Publisher: %s\n", p->b.publisher);
        printf("Number of pages: %d\n", p->b.numberOfPages);
        printf("Number of books: %d\n", p->b.numberOfBooks);
        printf("Number of available books: %d\n", p->b.numberOfAvailableBooks);
        printf("Number of borrowed books: %d\n", p->b.numberOfBorrowedBooks);
        printf("Price: %d\n", p->b.price);
        printf("\n");

        // Move the pointer to the next node in the list
        p = (struct Node *) p->book_ptr;

    }

    // Print a message to return to the main menu
    printf("\t\t\t\t\t\t\t\t0)Return: ");

    // Call the return function
    Return();

}

// Define a function to get the data of a book by its ID and display it
void GetData(struct Node **Head) {
    char Flag = 0; // A flag variable to indicate whether the book is found or not
    int id; // A variable to store the input ID
    printf("\n\t\tPlease Enter Book ID: "); // Prompt the user to enter the book ID
    scanf("%d", &id); // Read the input ID
    struct Node *p = (struct Node *) Head; // Initialize a pointer to traverse the list and search for the book
    while (p != NULL && Flag == 0) { // Loop until the end of the list or until the book is found

        if (p->b.ID == id) { // If the book ID matches the input ID
            system("cls"); // Clear the screen
            Flag = 1; // Set the flag to 1 to indicate that the book is found
            printf("ID: %d\n", p->b.ID); // Print the book information
            printf("Department: %s\n", p->b.Department);
            printf("Title: %s\n", p->b.title);
            printf("Author: %s\n", p->b.author);
            printf("Publisher: %s\n", p->b.publisher);
            printf("Number of pages: %d\n", p->b.numberOfPages);
            printf("Number of books: %d\n", p->b.numberOfBooks);
            printf("Number of available books: %d\n", p->b.numberOfAvailableBooks);
            printf("Number of borrowed books: %d\n", p->b.numberOfBorrowedBooks);
            printf("Price: %d\n", p->b.price);
            printf("\t\t\t\t\t\t\t\t0)Return: "); // Print a message to return to the main menu
        }
        p = (struct Node *) p->book_ptr; // Move the pointer to the next node in the list
    }
    if (Flag == 0) { // If the flag is still 0, it means that no book with matching ID was found
        system("cls"); // Clear the screen
        printf("\n\t\t\t\tBook ID No: %d is not Found\n\t\t\t\t\t\t\t\t0) Return: ", id); // Print a message to inform the user that the book is not found

    } else {//Do Nothing
    }
    Return(); // Call the return function
}

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// Define a function to search for a book by different criteria and display it
void SearchBook(struct Node **Head) {
    char ret = 0; // A variable to store the return value
    struct book c1; // A variable to store the criteria for search
    char Criteria_for_search = 0; // A variable to store the input choice for search
    while (Criteria_for_search != 6) { // Loop until the user confirms the search
        printf("\t\tSelect Criteria(s) for search\n**************************************************\n1) Department\n2) Title\n3) Author\n4) Publisher\n5) Price\n\t\t\t\t\t\t\6) Confirm Search\nYour entry No. is:"); // Print a menu for selecting criteria for search
        scanf("%d", &Criteria_for_search); // Read the input choice
        printf("\nYour entry :");
        switch (Criteria_for_search) { // Switch on the input choice
            case 1: // If the user chooses department
                scanf("%s", &c1.Department); // Read the input department
                break;
            case 2: // If the user chooses title
                scanf("%s", &c1.title); // Read the input title
                break;
            case 3: // If the user chooses author
                scanf("%s", &c1.author); // Read the input author
                break;
            case 4: // If the user chooses publisher
                scanf("%s", &c1.publisher); // Read the input publisher
                break;
            case 5: // If the user chooses price
                scanf("%d", &c1.price); // Read the input price
                break;
        }
        system("cls"); // Clear the screen
    }

    struct Node *p = (struct Node *) Head; // Initialize a pointer to traverse the list and search for the book
    system("cls"); // Clear the screen
    while (p != NULL) { // Loop until the end of the list

        if (!strcmp(c1.Department, p->b.Department) || !strcmp(c1.title, p->b.title) || !strcmp(c1.author, p->b.author) || !strcmp(c1.publisher, p->b.publisher) || (c1.price == p->b.price)) { // If any of the criteria matches the book data
            printf("ID: %d\n", p->b.ID); // Print the book information
            printf("Department: %s\n", p->b.Department);
            printf("Title: %s\n", p->b.title);
            printf("Author: %s\n", p->b.author);
            printf("Publisher: %s\n", p->b.publisher);
            printf("Number of pages: %d\n", p->b.numberOfPages);
            printf("Number of books: %d\n", p->b.numberOfBooks);
            printf("Number of available books: %d\n", p->b.numberOfAvailableBooks);
            printf("Number of borrowed books: %d\n", p->b.numberOfBorrowedBooks);
            printf("Price: %d\n", p->b.price);
        }
        p = (struct Node *) p->book_ptr; // Move the pointer to the next node in the list
    }
    printf("\t\t\t\t\t\t\t\t\t0)Return"); // Print a message to return to the main menu
    Return(); // Call the return function
}


void What_to_edit(struct Node **Book) {

    while (1) {
        printf("choose your thing to be edited\n");
        printf("1) DEPARTMENT\n2) TITLE\n3) AUTHOR\n4) PUBLISHER\n5) NUMBER OF PAGES\n6) NUMBER OF BOOKS\n7) NUMBER OF AVAILABE BOOKS\n8) NUMBER OF BORROWEDBOOKS \n9) PRICE \n0) STOP\n");

        int choice;
        scanf("%d", &choice);

        if (choice == DEPARTMENT) {
            printf("enter the department\n");
            scanf("%s", (*Book)->b.Department);
        } else if (choice == TITLE) {
            printf("enter the title\n");
            scanf("%s", (*Book)->b.title);
        } else if (choice == AUTHOR) {
            printf("enter the author\n");
            scanf("%s", (*Book)->b.author);
        } else if (choice == PUBLISHER) {
            printf("enter the publisher\n");
            scanf("%s", (*Book)->b.publisher);
        } else if (choice == NUMBEROFPAGES) {
            printf("enter the number of pages\n");
            scanf("%d", &(*Book)->b.numberOfPages);
        } else if (choice == NUMBEROFBOOKS) {
            printf("enter the number of books\n");
            scanf("%d", &(*Book)->b.numberOfBooks);
        } else if (choice == NUMBEROFAVAILABEBOOKS) {
            printf("enter the number of available books\n");
            scanf("%d", &(*Book)->b.numberOfAvailableBooks);
        } else if (choice == NUMBEROFBORROWEDBOOKS) {
            printf("enter the number of borrowed books\n");
            scanf("%d", &(*Book)->b.numberOfBorrowedBooks);
        } else if (choice == PRICE) {
            printf("enter the price\n");
            scanf("%d", &(*Book)->b.price);
        } else if (choice == STOP) {
            break;
        } else {
            printf("invalid choice\n");
        }
    }
}


int Edit_Book(struct Node **head, int Book_ID) {
/*
    int choice ;
    scanf("%d",&choice);
*/
    if (*head == NULL) {
        return 0;
    }

    struct Node *current = *head;
    struct Node *previous = NULL;

    while (current != NULL && current->b.ID != Book_ID) {
        previous = current;
        current = current->book_ptr;
    }

    if (current == NULL) {
        return 0;
    }


    What_to_edit(&current);


    return 1;
}
// Define a function to check the password and access the main menu
void PassWord() {

    char Flag = 0; // A flag variable to indicate whether the password is correct or not
    char No_of_tries = 0; // A variable to count the number of tries
    char *MainPassword = (char *) &Password; // A pointer to the constant array that stores the password
    char Password_Entry[20] = {'0'}; // An array to store the input password


    while (No_of_tries <= 2) { // Loop until the user exceeds the maximum number of tries
        if (Flag == 1) { // If the flag is 1, it means that the previous password entry was wrong
            system("cls"); // Clear the screen
            printf("\t\t\t\t    Wrong Password\n\t\t\t\tTrails Remaining = %d\n", (3 - No_of_tries)); // Print a message to inform the user about the remaining tries
        }
        printf("\n\t\t\tPlease Enter 6-Digit Password: "); // Prompt the user to enter the password
        scanf("%s", &Password_Entry); // Read the input password
        for (int i = 0; i < 6; i++) { // Loop through each character of the password
            Flag = 0; // Reset the flag to 0
            if (Password_Entry[i] != *MainPassword) { // If the input character does not match the corresponding character in the password
                Flag = 1; // Set the flag to 1 to indicate that the password is wrong
                No_of_tries++; // Increment the number of tries
                break; // Break out of the loop


            } else {
                NULL; // Do nothing
            }
            MainPassword++; // Move the pointer to point to the next character in the password
        }
        if (Flag == 0) {			// If the flag is still 0, it means that the password is correct
            system("cls");
			MainMenu(); // Call the main menu function
        } else {
            MainPassword = (char *) &Password; // Reset the pointer to point to the beginning of the password
        }
    }
    exit(0); // Exit from the program
}

void Add_Student(Student_Node_t **student_head, student_t new_student) {
    Student_Node_t *new_node = (Student_Node_t *) malloc(sizeof(Student_Node_t));
    new_node->s = new_student;
    new_node->student_ptr = NULL;
    if (*student_head == NULL) {
        *student_head = new_node;
        return;
    }

    //4 5 7 10 11
    Student_Node_t *current = *student_head;
    Student_Node_t *previous = NULL;

    while (current != NULL && current->s.ID < new_student.ID) {
        previous = current;
        current = current->student_ptr;
    }
    if (previous == NULL) {
        new_node->student_ptr = *student_head;
        *student_head = new_node;
    } else {
        new_node->student_ptr = current;
        previous->student_ptr = new_node;
    }
}


void issueBook(struct Node** head,Student_Node_t **student_head)
{
	student_t new_student;
    char ret = 0;
    struct book c1;
	student_t s1;
    char Criteria_for_search =0;
	char Criteria_for_search2 = 0;
    while (Criteria_for_search != 3){
        printf("\t\tSelect Criteria(s) for search\n**************************************************\n1) ID\n2) Title\t\t\t\t\t\t\ 3) Confirm Search\n Your entry No. is:");
		scanf("%d",&Criteria_for_search);		
        switch(Criteria_for_search){
            case 1: printf("Enter book ID :");scanf("%d",&c1.ID);break;
            case 2: printf("Enter book title :");scanf("%s",c1.title);break;
        }
        system("cls");
    }
    struct Node* p = head;
	Student_Node_t *st =student_head;
    system("cls");
    while (p != NULL)
    {
        if( (c1.ID == p->b.ID) || !strcmp(c1.title , p->b.title))
        {
			if((p->b.numberOfBooks) > (p->b.numberOfBorrowedBooks))
			{
				p->b.numberOfAvailableBooks = (p->b.numberOfBooks) - (p->b.numberOfBorrowedBooks);
				printf("\t*********************************\t Book is Available \t*********************************\n");
				printf("\t*********************************\t Assigning to student \t*********************************\n");
				while (Criteria_for_search2 != 3){
				printf("\t\tSelect Criteria for search for registered student\n**************************************************\n1) ID\n2) Name\t\t\t\t\t\t\6) Confirm Search\n Your entry No. is:");
					scanf("%d",&Criteria_for_search2);		
					switch(Criteria_for_search2){
						case 1:printf("Enter student ID :");scanf("%d",&s1.ID);break;
						case 2:printf("Enter student name :");scanf("%s",s1.name);break;
						}
				}						
				/*scanf("%d",&Criteria_for_search2);
				switch(Criteria_for_search2)
				{
					case 1:printf("Enter student ID :");scanf("%d",s1.ID);break;
					case 2:printf("Enter student name :");scanf("%s",&s1.name);break;
				}*/
			   while (st != NULL)
			   {
				    if( (s1.ID == st->s.ID) || !strcmp(s1.name , st->s.name))
					{
						if(st->s.issuedBookID == 0)
						{
							p->b.numberOfBorrowedBooks +=1;
							st->s.issuedBookID = p->b.ID;
							memcpy(st->s.issuedBookTitle , p->b.title,30);
							printf("\n****************\t\t Issue completed \t\t****************");
							ret = 3;
							break;
						}
						else
						{
							ret = 5;
							printf("\n****************\t\t %s Already have a book issued can't issue book \t\t****************\n",st->s.name);
							break;
						}
					}
					st = st->student_ptr;
					printf("test1");
			    }
				if(ret = 0) 
				{
					printf("****************\t\ Student is not registered \t****************\n\n");	
					printf("\t\t\t\t\t\t\t\t\t0)Return");
					Return(); 
				
				}				
			}
			else
			{
				ret = 2;
			}
        }
		else
		{
			ret = 1;
		}
        p = p->book_ptr;
    }
	if(ret == 1)
	{
		printf("****************\t\t book not found  \t\t****************\n");
		delay(10000);
	}
	else if(ret == 2)
	{
		printf("****************\t\t all books with this title is issued no available copies  \t\t****************\n");
	}
	else
	{
		printf("\t\t\t\t\t\t\t\t\t1)Return");
		Return();
	}
;
	
}	

void viewIssueBooks (struct Node** head)
{
	char ret = 0;
	char Flag = 0;
    char department[30];
    printf("\n\t\tPlease Enter The Department: ");
    scanf("%s", &department);
    struct Node *p = head;
	system("cls");
    while (p != NULL) {

        if ( (!strcmp(department , p->b.Department)) ) 
		{
			if( (p->b.numberOfBorrowedBooks != 0) )
			{
				Flag = 1;
				printf("ID: %d\n", p->b.ID);
				printf("Department: %s\n", p->b.Department);
				printf("Title: %s\n", p->b.title);
				printf("Author: %s\n", p->b.author);
				printf("Publisher: %s\n", p->b.publisher);
				printf("Number of pages: %d\n", p->b.numberOfPages);
				printf("Number of books: %d\n", p->b.numberOfBooks);
				printf("Number of available books: %d\n", p->b.numberOfAvailableBooks);
				printf("Number of borrowed books: %d\n", p->b.numberOfBorrowedBooks);
				printf("Price: %d\n", p->b.price);
				printf("\t\t\t********************************************\t\t\t\n\n");				
			}
			else
			{
				/*Do Nothing*/
			}
        }
		else
		{
			/*Do nothing*/
		}
        p = p->book_ptr;
    }
    if (Flag == 0) {
        system("cls");
        printf("\n\t\t\t\tNO Issued Books in %s department",department);
		delay(10000);
    }
	else 
	{
		printf("\t\t\t\t\t\t\t\t\t1)Return");	
        Return();
    }
}
	
void studentissuerecord (Student_Node_t** student_head)
{
	char delete = 0;
	char Flag = 0;
    char studentName[30];
    printf("\n\t\tPlease Enter The Student name: ");
    scanf("%s", &studentName);
    Student_Node_t *p = student_head;
	system("cls");
    while (p != NULL) {

        if ( (!strcmp(studentName , p->s.name)) ) 
		{
			if( (p->s.issuedBookID != 0) )
			{
				Flag = 1;
				printf("Student name: %s\n", p->s.name);
				printf("Student ID: %d\n", p->s.ID);
				printf("Issued Book Title: %s\n", p->s.issuedBookTitle);
				printf("Issued Book ID: %d\n", p->s.issuedBookID);
				printf("\n\t\t\t********************************************\t\t\t\n");							
			}
			else
			{
				Flag = 0;
			}
        }
		else
		{
			/*Do nothing*/
		}
        p = p->student_ptr;
    }
    if (Flag == 0) {
        system("cls");
        printf("\n\t\t\t\tNO Issued books for %s",studentName);
		delay(10000);
    }
	else {
		printf("\t\t\t\t\t\t\t\t\t1)Return");	
        Return();
    }
}



// Define the main function of the program
void main(void) {

    // Create some book objects and initialize them with some data
    struct book b1 = {10, "Computer Science", "The C Programming Language", "Brian Kernighan and Dennis Ritchie",
                      "Prentice Hall", 272, 10, 8, 2, 125};
    struct book b2 = {15, "Mathematics", "Calculus", "Michael Spivak", "Cambridge University Press", 670, 5, 3, 2, 200};
    struct book b3 = {8, "Physics", "The Feynman Lectures on Physics",
                      "Richard Feynman, Robert Leighton and Matthew Sands", "Addison-Wesley", 1552, 3, 1, 2, 500};
    struct book b4 = {1, "Literature", "Nineteen Eighty-Four", "George Orwell", "Secker & Warburg", 328, 9, 7, 1, 150};
    struct book b5 = {110, "History", "The Silk Roads: A New History of the World", "Peter Frankopan",
                      "Bloomsbury Publishing", 656, 8, 6, 1, 250};


    struct book b6 = {17, "Biography", "Becoming", "Michelle Obama", "Crown Publishing Group", 448, 9, 8, 2, 300};
    struct book b7 = {2, "Biography", "Dune", "Frank Herbert", "Chilton Books", 412, 10, 9, 3, 200};
    struct book b8 = {140, "Thriller", "The Girl on the Train", "Paula Hawkins", "Riverhead Books", 336, 7, 5, 2, 150};
    struct book b9 = {19, "Fantasy", "The Name of the Wind", "Patrick Rothfuss", "DAW Books", 662, 9, 7, 2, 175};

    // Add the books to the list using the Add_Book function
    Add_Book(&head, b1);
    Add_Book(&head, b2);
    Add_Book(&head, b3);
    Add_Book(&head, b4);
    Add_Book(&head, b5);

    /* view_books(head); // This is a function call to view the books in the list
     Delete_Book(&head, 1); // This is a function call to delete a book from the list by its ID */

    // These two lines are commented out by using /* and */, so they will not be executed

    Add_Book(&head, b6);
    Add_Book(&head, b7);
    Add_Book(&head, b8);
    Add_Book(&head, b9);
	
	student_t mo = {"moamen","Dune",5,2};
	Add_Student(&student_head,mo);

    system("cls"); // Clear the screen
    PassWord(); // Call the PassWord function to check the password and access the main menu
}


// Define a function to display the main menu and handle the user input
void MainMenu() {
    system("cls"); // Clear the screen
    while (1) { // Loop indefinitely until the user exits from the program

        char Choice = 0; // A variable to store the user choice
        printf("\t\t\t\tMain Menu\n*****************************************************************************\n"); // Print a header for the main menu
        printf("1) Add Book\n2) Delete Book\n3) Search Book\n4) Get Data\n5) View Books\n6) Issue Book\n7) View Issued Books\n8) Student Issue Record\n9) Add Student \n10) Edit book\n");
        scanf("%d", &Choice); // Read the user input
        switch (Choice) { // Switch on the user choice
            case 1: // If the user chooses to add a book
                system("cls"); // Clear the screen
                struct book new_book; // Create a new book object
                printf("Enter the ID of the new book: "); // Prompt the user to enter the details of the new book
                scanf("%d", &new_book.ID);

                printf("Enter the department of the new book: ");
                scanf("%s", new_book.Department);

                printf("Enter the title of the new book: ");
                scanf("%s", new_book.title);

                printf("Enter the author of the new book: ");
                scanf("%s", new_book.author);

                printf("Enter the publisher of the new book: ");
                scanf("%s", new_book.publisher);

                printf("Enter the number of pages in the new book: ");
                scanf("%d", &new_book.numberOfPages);

                printf("Enter the number of books of the new book: ");
                scanf("%d", &new_book.numberOfBooks);

                printf("Enter the number of available books of the new book: ");
                scanf("%d", &new_book.numberOfAvailableBooks);

                printf("Enter the number of borrowed books of the new book: ");
                scanf("%d", &new_book.numberOfBorrowedBooks);

                printf("Enter the price of the new book: ");
                scanf("%d", &new_book.price);

                // Copy the user input to the new_book struct
                Add_Book(&head, new_book); // Call the Add_Book function to add the new book to the list
                printf("\n\t\t\t\t\t\t\t\t\t0)Return: "); // Print a message to return to the main menu
                Return(); // Call the Return function
                system("cls"); // Clear the screen
                break;
            case 2: // If the user chooses to delete a book
                system("cls"); // Clear the screen
                int Book_ID; // A variable to store the input ID
                int Local_Error_State = 0; // A variable to store the return value of the Delete_Book function
                printf("Enter ID of book to Delete : \n"); // Prompt the user to enter the ID of the book to delete
                scanf("%d", &Book_ID); // Read the input ID
                Local_Error_State = Delete_Book(&head, Book_ID); // Call the Delete_Book function and store its return value
                if (Local_Error_State == 0) { // If the return value is 0, it means that the book was not found or deleted
                    printf("Book Not Found to Delete \n"); // Print a message to inform the user that the book was not deleted

                } else { // If the return value is 1, it means that the book was successfully deleted
                  printf("Book is Deleted\n"); // Print a message to inform the user that the book was deleted

                }

                break;
            case 3: // If the user chooses to search for a book
                system("cls"); // Clear the screen
                SearchBook((struct Node **) head); // Call the SearchBook function and pass the head of the list as an argument
                break;
            case 4: // If the user chooses to get the data of a book by its ID
                system("cls"); // Clear the screen
                GetData((struct Node **) head); // Call the GetData function and pass the head of the list as an argument
                system("cls"); // Clear the screen
                break;
            case 5: // If the user chooses to view all the books in the list
                system("cls"); // Clear the screen
                view_books((struct Node **) head); // Call the view_books function and pass the head of the list as an argument
                break;
            case 6:
                system("cls");
                issueBook(head,student_head);
                break;
            case 7:
                system("cls");
                viewIssueBooks(head);
                break;
            case 8:
                system("cls");
                studentissuerecord(student_head);
                break;
			case 9:
				system("cls");
				student_t new_student;
				
                printf("Enter the name of the new student: ");
                scanf("%s", new_student.name);		

				
                printf("Enter the ID of the new student: ");
                scanf("%d", &new_student.ID);


                printf("Enter the Issued Book Title of the new student: ");
                scanf("%s", new_student.issuedBookTitle);

                printf("Enter the Issued Book ID of the new student: ");
                scanf("%d", &new_student.issuedBookID);
				
                Add_Student(&student_head, new_student);
                break;				
			case 10:
			    system("cls");
                int Book_ID1;
                int Local_Error_State1 = 0;
                printf("Enter ID of book to Edit : \n");
                scanf("%d", &Book_ID1);
                Local_Error_State1 = Edit_Book(&head, Book_ID1);
                if (Local_Error_State1 == 0) {
                    printf("Book Not Found to Edit \n");

                } else {
                    printf("Book is Edited\n");
					delay(10000);
			    system("cls");
                }
                break;
            default: // If the user enters an invalid choice
                system("cls"); // Clear the screen
                printf("\t\t\t***********************\n\t\t\t*Wrong Entry Try Again*\n\t\t\t***********************\n"); // Print a message to ask the user to try again
        }
    }
}

