
//Header files
#include<stdio.h>
#include<stdlib.h>

//Decalaration of different functions used within the program
void AddData();
void insertAtEnd(char[], char[], char[]);
void print_list();
void loadRecords();
void displayStatements();
void removeSpecificRecord(char[]);
void searchSpecificRecord(char name[]);
void writingRecordsToFile();

//Declaration of Sturcture named node
struct node  
{
	//Data members of the structure
	char fname[50]; //For First Name
	char lname[50]; // For Last Name
	char phone[50]; // For Phone Number

	struct node *next;
};

//Declaring poniter head of structure node type and initializing it with NULL value
struct node *head=NULL;
struct node *newNode;  //Linked List

//Main of the program
int main() {
	printf("\n******************PHONE BOOK APPLICATION*******************\n");
	loadRecords(); //Calling load functions to load records stored in the file when program starts
	displayStatements();
	return 0;
}
//End of the main

//Function to give different options to the user to perform
void displayStatements() {
	int userAns;
	char name[50];
	do {
		printf("\nEnter below numbers to perform different functions:\n");
		printf("1. Add\n");
		printf("2. Delete\n");
		printf("3. Load\n");
		printf("4. Save\n");
		printf("5. Search\n");
		printf("6. Exit\n");
		scanf("\n%d", &userAns);
		printf("You entered : %d\n", userAns);
		
		// Switch statement to perform different functions according to the user's choice	
		switch(userAns) {
			case 1: {
				AddData(); // Calling function to add data to the text file
				break;
			}

			case 2: {
				print_list();
				printf("Enter the first name of the person you want to remove: ");
				scanf("%s", &name);
				removeSpecificRecord(name); // Calling function to remove record from the data structure(Linked List) 
										    //	on the basis of the first name entered by the user
				print_list();	// Function to print the data stored in the linked list
				break;
			}

			case 3: {
				loadRecords();	// Function to load records from the text file
				break;
			}

			case 4: {
				writingRecordsToFile(); // Function to write/save data from the file
				break;
			}

			case 5: {
				printf("Enter the first name of the person you want to search: ");
				scanf("%s", &name);
				searchSpecificRecord(name);	// Function to search specific record from the text file on the basis of 
										// the first name entered by the user
				break;
			}

			case 6: {
				exit(0);
				break;
			}
		}
	}
	while(userAns <= 5);
}

//Function to load records from the text file and display it to the screen
void loadRecords() {
	FILE *fp; // File Pointer
	char c;

	fp = fopen("Records.txt", "r"); // Opening text file in reading mode
	printf("\nRecords retrieved from the Phone Book are :");
	printf("\nLast Name\tFirst Name\tPhone\n");
	if(fp == NULL) {
		printf("Error in opening the file");
	}
	else {
		do {
			c=getc(fp); // Getting data from the file and saving it in c variable
			putchar(c);
		}
		while(c!=EOF);
		fclose(fp); // Closing the file
	}
}

//Function to display printf statements to enter data and store them corresponding data members
void AddData() {
	char firstName[100];
	char lastName[100];
	char phoneNo[150];

	printf("Enter the last name: ");
	scanf("%s", &lastName);

	printf("Enter the first name: ");
	scanf("%s", &firstName);

	printf("Enter the phone number in XXX-XXX-XXXX format: ");
	scanf("%s", &phoneNo);

	insertAtEnd(lastName, firstName, phoneNo); //Calling function to insert data to the linked list
}

//Function with to logic to add data into the linked list att the end
void insertAtEnd(char fn[100], char ln[100], char ph[150]) {	 
	struct node *newNode, *temp;

    	newNode = (struct node *)malloc(sizeof(struct node)); //Dynamically allocating memory
	
	//Storing data to the linked list
	strcpy(newNode->fname, fn);  
	strcpy(newNode->lname, ln); 
	strcpy(newNode->phone, ph); 

   	if(head == NULL) {
		newNode->next = NULL;
        	head = newNode;
    	}
    	else {
	 	temp = head;
       	//Traverse to the last node of the linked list
        	while(temp->next != NULL)
            		temp = temp->next;

        temp->next = newNode; 
    	}
}

//Function to print data stored in the linked list
void print_list(void)  
{   
	if(head == NULL)	 // Condition to check if the linked list is empty 
  	{
     		printf("\nList is Empty\n");
  	}
  	else
   	{      
		struct node *temp = head; 
      		while(temp->next != NULL)
      		{	
	 		printf("%s\t%s\t%s\n", temp->fname, temp->lname, temp->phone);
	 		temp = temp->next;	
     		}
		printf("%s\t%s\t%s\n", temp->fname, temp->lname, temp->phone);
   	}
}

//Function to remove records from the linked list(data structure) based on the name entered by the user
void removeSpecificRecord(char name[]) {
	struct node *temp1 = head; //temp1 for current node
	struct node *temp2 = NULL; //temp2 for previous node
		if (strcmp(temp1->fname, name) != 0) { //If the item is in the start node
			struct node *temp3 = head;
			head = head->next;
			free(temp3);
		}
		else {
			while(strcmp(temp1->fname, name) != 0) { 
				if(temp1->next == NULL) { // If the record is not found in the linked list
					printf("\Given record not found in the list!!!");
					exit(1);
				}
			temp2 = temp1;
			temp1 = temp1->next;
			}
			temp2->next = temp1->next; //Removing the node
			free(temp1);
			free(temp2);
			printf("\nOne Record deleted!!!!\n");
		}
}

//Function to search specific record on the basis of first name entered by the user in the text file
void searchSpecificRecord(char name[]) {
	FILE *fp; // File Pointer
	char c[150];

	fp = fopen("Records.txt", "r"); //Opening file in the read mode
	
	if(fp == NULL) { // If file doesn't exist
		printf("Error in opening the file");
	}
	else {
		while(fp && fgets(c, sizeof(c), fp)) {  //Store the data of the text file in 'c'
        		if (strstr(c, name)) {// Compare the value entered by the user with data in the text file
            			printf("%s", c); // Printing the value if data is found
			}
    		}
	}
	fclose(fp); // Closing the file
}

//Function to write/save data from the linked list to the text file
void writingRecordsToFile() {
    FILE * fp; //File pointer
    fp = fopen("Records.txt", "a"); //Opening the file in append mode to write data into it
    struct node *temp = head; 

    if(fp == NULL) // If file doesn't exist
    {
        printf("Something went wrong!!!\n");
    }
    else // Else block to read data from the linked list and stored it into the text file
    {
        while(temp != NULL)
        {
            fprintf(fp, "%s\t\t%s\t\t%s\n", temp->fname, temp->lname, temp->phone);
            temp= temp->next;
        }
	 printf("Record is successfully saved to the file!!!\n");
    }
    fclose(fp); //Closing the file
}



