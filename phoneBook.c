#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 20
#define PHONE_NUMBER_SIZE 14
#define EMAIL_ADDRESS_SIZE 60
#define MAX_CONTACTS 100
#define TRUE 1
#define FALSE 0

// define contact structure
typedef struct{
    char name[NAME_SIZE];
    char phoneNumber[PHONE_NUMBER_SIZE];
    char emailAddress[EMAIL_ADDRESS_SIZE];
} Contact;

// validate inputs
void collectInput(char* var, char prompt[], int limit){
    // until the correct input is entered, keep prompting.
    while(TRUE){
        printf("%s\n", prompt);
        scanf("%s", var);
        if(strlen(var) <= limit){
            break;
        }
        else{
            printf("Please stick to the character limit of %d characters.\n", limit);
        }
    }
}

void createContact(int* position, Contact* address){
    // define our variables for struct.
    char name[NAME_SIZE];
    char phoneNumber[PHONE_NUMBER_SIZE];
    char emailAddress[EMAIL_ADDRESS_SIZE];
    // assign an integer to the current value of int pointer.
    int val = *position;
    printf("Contacts: %d\n", val);
    // get details for our contact.
    collectInput(&name, "Enter name of contact:", NAME_SIZE);
    collectInput(&phoneNumber, "Enter phone number of contact", PHONE_NUMBER_SIZE);
    collectInput(&emailAddress, "Enter email address of contact:", EMAIL_ADDRESS_SIZE);
    // create object of contact structure
    Contact contact;
    // assign our input to our contact
    strcpy(contact.name, name);
    strcpy(contact.phoneNumber, phoneNumber);
    strcpy(contact.emailAddress, emailAddress);
    // check if the current value is less than max number of contacts
    if(val <= MAX_CONTACTS){
        // assign our contact to the contacts pointer.
        *(address+val) = contact;
    }
    else{
        // if we are overflowing, try and get more memory for our pointer.
        address = (Contact *) realloc(address, sizeof(Contact) * val);
        // if it fails, print error message and return.
        if(address == NULL){
            printf("Could not create contact!\n");
            return;
        }
        else{
            // otherwise store the new contact in our new pointer.
            *(address+val) = contact;
        }
    }
    // increment our position by 1.
    *position = val + 1;
}

void viewContacts(Contact *contacts, int numberofContacts){
    // check if there are contacts.
    if(numberofContacts == 0){
        // if no contacts then display message to the user.
        printf("No contacts found.\n");
        return;
    }
    // otherwise print out all stored contacts.
    for(int i = 0; i < numberofContacts; i++){
        Contact contact = *(contacts+i);
        printf("Name: %s\nPhone Number: %s\nEmail Address: %s\n\n", contact.name, contact.phoneNumber, contact.emailAddress);
    }
}

void quitProgram(Contact* contacts){
    // free our contacts pointer.
    free(contacts);
    // display message when successful.
    printf("Successfully exitted program and freeded memory!\n");
}

int main(){
    // define our position tracker.
    int position = 0;
    // create our contacts pointer.
    Contact *contacts = (Contact*) malloc(sizeof(Contact)*MAX_CONTACTS);
    // create an integer for our input.
    int option;
    while(TRUE){
        // display all options
        printf("\t\t Menu\n1. Create a new contact\n2. View all contacts\n3. Quit program\n");
        scanf("%d",&option);
        if(option == 1){
            // create a new contact
            createContact(&position, contacts);
        }
        else if(option == 2){
            // view all contacts
            viewContacts(contacts, position);
        }
        else if (option == 3){
            // leave program
            printf("Leaving program\n");
            break;
        }
        else{
            // tell user to enter a number in the range.
            printf("Please enter a number between 1 and 3!\n");
        }
        
    }
    // quit program
    quitProgram(contacts);
    return 0;
}